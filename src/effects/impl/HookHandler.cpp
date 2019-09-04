// Copyright (c) 2019 Lordmau5
#include "HookHandler.h"

bool HookHandler::canLoadSave = true;
bool HookHandler::didTryLoadAutoSave = false;
char* HookHandler::loadingDisallowedText = "";

void HookHandler::Initialize() {
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

	// Overwrite CText::Get call to show custom text on "Load Game" option in the menu
	patch::RedirectCall(0x579D73, HookedCTextGet);

	// Properly modify sound pitch and speed
	patch::RedirectJump(0x561AD0, HookedGetIsSlowMotionActive);
	injector::WriteMemory(0x8CBA6C, 1.0f);
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
		TryLoadAutoSave();
		return;
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
		return canLoadSave ? "Load Autosave" : loadingDisallowedText;
	}
	else if (key_str == "FEP_STG") {
		if (!didTryLoadAutoSave) {
			didTryLoadAutoSave = true;

			if (!KeyPressed(VK_CONTROL)) {
				TryLoadAutoSave();
			}
		}
	}

	return thisText->Get(key);
}

bool HookHandler::HookedGetIsSlowMotionActive() {
	return true;
}
