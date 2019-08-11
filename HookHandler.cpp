#include "HookHandler.h"

bool HookHandler::canLoadSave = true;

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
}

void __fastcall HookHandler::HookedProcessMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page) {
	if (page == eMenuPage::MENUPAGE_LOAD_GAME) { // NO LOADING :AngryBongo:
		if (!canLoadSave) {
			return;
		}
		canLoadSave = false;
	}

	if (page == eMenuPage::MENUPAGE_REDEFINE_CONTROLS) {
		if (InvertedControls::isEnabled || LetsTakeABreak::isEnabled || DisableOneMovementKey::isEnabled) {
			return;
		}
	}

	thisManager->SwitchToNewScreen(page);
}
