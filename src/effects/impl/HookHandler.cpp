// Copyright (c) 2019 Lordmau5
#include "HookHandler.h"

bool HookHandler::canLoadSave = true;
bool HookHandler::didTryLoadAutoSave = false;
char* HookHandler::loadingDisallowedText = "";

void HookHandler::Initialize() {
	// #####################################
	// Inverted Controls / Lets Take A Break / Disable One Movement Key / Disable Loading The Game
	int processMenuOptions[] = {
		0x0576AE9,
		0x0577244,
		0x0577266,
		0x05772C2,
		0x05772E5,
		0x057730F,
		0x0578E26,
		0x0578EA1,
		0x057B73A,
		0x057C4AB,
		0x057C4B3,
		0x057C4BB,
		0x057C4C3,
		0x057D2D9,
		0x057D306,
		0x057D315,
		0x057D335,
		0x057D379,
		0x057D38A,
		0x057D6AB,
		0x057D6BA
	};
	for (int address : processMenuOptions) {
		patch::RedirectCall(address, HookedProcessMenuOptions);
	}
	// #####################################

	// #####################################
	// Overwrite CText::Get call to show custom text on "Load Game" option in the menu
	patch::RedirectCall(0x579D73, HookedCTextGet);
	// #####################################

	// #####################################
	// Properly modify sound pitch and speed
	patch::RedirectJump(0x561AD0, HookedGetIsSlowMotionActive);
	injector::WriteMemory(0x8CBA6C, 1.0f, true);

	for (int address : { 0x4D6E34, 0x4D6E48, 0x4DBF9B, 0x4EA62D, 0x4F0871, 0x4F0A58 }) {
		patch::RedirectCall(address, HookedSetFrequencyScalingFactor);
	}

	for (int address : { 0x4EA258, 0x4EA258 }) {
		patch::RedirectCall(address, HookedRadioSetVolume);
	}
	// #####################################

	// #####################################
	// Fix some issues related to a game crash caused by randomly generated planes
	patch::RedirectCall(0x46E42F, HookedCPlaneIsAlreadyFlying);
	// #####################################
}

void HookHandler::TryLoadAutoSave() {
	if (CTimer::m_snTimeInMilliseconds > 1000 || !canLoadSave) {
		return;
	}

	if (GenericUtil::LoadFromFile("chaos_mod\\chaos_autosave.b")) {
		canLoadSave = false;
	}
}

void __fastcall HookHandler::HookedProcessMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page) {
	if (page == eMenuPage::MENUPAGE_START_GAME) {
		char* randomText[5] = {
			"No Load, Only Play!",
			"Nice Try ;)",
			"Really...?",
			"Nope :)",
			""
		};

		char* randomPick = "";

		do {
			randomPick = randomText[rand() % 5];
		} while (strcmp(randomPick, loadingDisallowedText) == 0);

		loadingDisallowedText = randomPick;
	}

	if (page == eMenuPage::MENUPAGE_LOAD_GAME) {
		if (Config::GetOrDefault("Chaos.DisableLoadGame", true)) {
			TryLoadAutoSave();
			return;
		}
	}

	if (page == eMenuPage::MENUPAGE_REDEFINE_CONTROLS) {
		if (DisableOneMovementKey::isEnabled || InvertedControls::isEnabled || LetsTakeABreak::isEnabled) {
			return;
		}
	}

	thisManager->SwitchToNewScreen(page);
}

char* __fastcall HookHandler::HookedCTextGet(CText* thisText, void* edx, char* key) {
	std::string key_str(key);
	if (key_str == "FES_LOA") {
		if (Config::GetOrDefault("Chaos.DisableLoadGame", true)) {
			return canLoadSave ? "Load Autosave" : loadingDisallowedText;
		}
	}
	else if (key_str == "FEP_STG") {
		if (!didTryLoadAutoSave) {
			didTryLoadAutoSave = true;

			if (Config::GetOrDefault("Chaos.LoadAutosaveOnGameLoad", true)) {
				if (!KeyPressed(VK_CONTROL)) {
					TryLoadAutoSave();
				}
			}
		}
	}

	return thisText->Get(key);
}

bool HookHandler::HookedGetIsSlowMotionActive() {
	return true;
}

int __fastcall HookHandler::HookedSetFrequencyScalingFactor(DWORD* thisAudioHardware, void* edx, int slot, int offset, float factor) {
	float actualFactor = factor;
	if (actualFactor > 0.0f) {
		actualFactor = GenericUtil::GetAudioPitchOrOverride(actualFactor);
	}
	return CallMethodAndReturn<int, 0x4D8960, DWORD*>(thisAudioHardware, slot, offset, actualFactor);
}

int __fastcall HookHandler::HookedRadioSetVolume(uint8_t* thisAudioHardware, void* edx, int a2, int a3, float volume, int a5) {
	volume = GenericUtil::GetAudioVolumeOrOverride(volume);
	return CallMethodAndReturn<int, 0x4D8870, uint8_t*>(thisAudioHardware, a2, a3, volume, a5);
}

int __fastcall HookHandler::HookedCPlaneIsAlreadyFlying(CPlane* thisPlane, void* edx) {
	if (thisPlane) {
		return CallMethodAndReturn<int, 0x6CAB90, CPlane*>(thisPlane);
	}
	return CTimer::m_snTimeInMilliseconds - 20000;
}
