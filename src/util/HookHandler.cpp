// Copyright (c) 2019 Lordmau5
#include "HookHandler.h"

bool HookHandler::didTryLoadAutoSave = false;
char* HookHandler::loadingDisallowedText = "";

void HookHandler::Initialize() {
	// #####################################
	// Load Game Override
	patch::RedirectCall(0x577244, HookedProcessMenuOptions);
	// #####################################

	// #####################################
	// Overwrite CText::Get call to show custom text on "Load Game" option in the menu
	patch::RedirectCall(0x579D73, HookedCTextGet);
	// #####################################

	// #####################################
	// Properly modify sound pitch and speed
	for (int address : { 0x4EA03B, 0x4EF446 }) {
		patch::RedirectCall(address, HookedGetIsSlowMotionActive);
	}
	injector::WriteMemory(0x8CBA6C, 1.0f, true);

	for (int address : { 0x4D6E34, 0x4D6E48, 0x4DBF9B, 0x4EA62D, 0x4F0871, 0x4F0A58 }) {
		patch::RedirectCall(address, HookedSetFrequencyScalingFactor);
	}

	patch::RedirectCall(0x4EA258, HookedRadioSetVolume);
	// #####################################

	// #####################################
	// Fix Cesar Vialpando fade-out when it shouldn't happen
	patch::RedirectCall(0x47C7C7, HookedCRunningScriptCollectParameters); // OPCODE: 016A, Fade
	// #####################################

	// #####################################
	// Fix certain cheats cancelling each other out
	for (int address : { 0x43934E, 0x4394C6, 0x4394F6, 0x439856 }) {
		patch::RedirectCall(address, HookedCheatCancelEachOther);
	}
	// #####################################
}

void HookHandler::TryLoadAutoSave() {
	GenericUtil::LoadFromFile("chaos_mod\\chaos_autosave.b");
}

void __fastcall HookHandler::HookedProcessMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page) {
	if (page == eMenuPage::MENUPAGE_LOAD_GAME) {
		if (Config::GetOrDefault("Chaos.DisableLoadGame", true)) {
			TryLoadAutoSave();
			return;
		}
	}

	thisManager->SwitchToNewScreen(page);
}

char* __fastcall HookHandler::HookedCTextGet(CText* thisText, void* edx, char* key) {
	std::string key_str(key);
	if (key_str == "FES_LOA") {
		if (Config::GetOrDefault("Chaos.DisableLoadGame", true)) {
			return "Load Autosave";
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

__int16 __fastcall HookHandler::HookedCRunningScriptCollectParameters(CRunningScript* thisScript, void* edx, unsigned __int16 num) {
	__int16 result = CallMethodAndReturn<__int16, 0x464080, CRunningScript*>(thisScript, num);

	std::string missionName = GenericUtil::ToUpper(std::string(thisScript->m_szName));
	if (missionName == "CESAR1") {
		if (CTheScripts::ScriptParams[0].iParam == 0 && CTheScripts::ScriptParams[1].iParam == 0) {
			CTheScripts::ScriptParams[1].iParam = 1;
		}
	}

	return result;
}

char HookHandler::HookedCheatCancelEachOther(int id) {
	return 0;
}
