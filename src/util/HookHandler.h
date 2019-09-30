// Copyright (c) 2019 Lordmau5
#pragma once

#include "common.h"
#include "plugin.h"

#include <filesystem>

#include "effects/other/Player.h"

#include "util/Config.h"
#include "util/GenericUtil.h"

#include "CGame.h"
#include "CMenuManager.h"
#include "extra/CPedDamageResponseCalculator.h"
#include "CRunningScript.h"
#include "CText.h"
#include "CTheScripts.h"

using namespace plugin;

class HookHandler
{
private:
	static bool didTryLoadAutoSave;
	static char* loadingDisallowedText;

public:
	static void Initialize();

	static void TryLoadAutoSave();

	static void __fastcall HookedProcessMenuOptions(CMenuManager* thisManager, void* edx, eMenuPage page);
	static char* __fastcall HookedCTextGet(CText* thisText, void* edx, char* key);
	static bool HookedGetIsSlowMotionActive();
	static int __fastcall HookedSetFrequencyScalingFactor(DWORD* thisAudioHardware, void* edx, int slot, int offset, float factor);
	static int __fastcall HookedRadioSetVolume(uint8_t* thisAudioHardware, void* edx, int a2, int a3, float volume, int a5);
	static __int16 __fastcall HookedCRunningScriptCollectParameters(CRunningScript* thisScript, void* edx, unsigned __int16 num);
	static char HookedCheatCancelEachOther(int id);
	static void HookHandler::HookedCClothesRebuildPlayer(CPed* ped, char bIgnoreFatAndMuscle);
};
