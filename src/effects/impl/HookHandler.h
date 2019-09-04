// Copyright (c) 2019 Lordmau5
#pragma once

#include <filesystem>

#include "DisableOneMovementKey.h"
#include "InvertedControls.h"
#include "LetsTakeABreak.h"

#include "CGame.h"
#include "CMenuManager.h"
#include "extra/CPedDamageResponseCalculator.h"
#include "CText.h"

class HookHandler
{
private:
	static bool canLoadSave;
	static bool didTryLoadAutoSave;
	static char* loadingDisallowedText;

public:
	static void Initialize();

private:
	static void TryLoadAutoSave();

	static void __fastcall HookedProcessMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page);
	static char* __fastcall HookedCTextGet(CText* thisText, void* edx, char* key);
	static bool HookedGetIsSlowMotionActive();
};
