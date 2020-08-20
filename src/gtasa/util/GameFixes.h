#pragma once

#include "plugin.h"

#include <filesystem>

#include "util/Config.h"
#include "util/EffectDatabase.h"
#include "util/GameUtil.h"
#include "util/GenericUtil.h"
#include "util/CPedDamageResponseCalculator.h"

#include "CGame.h"
#include "CMenuManager.h"
#include "CRunningScript.h"
#include "CText.h"
#include "CTheScripts.h"

using namespace plugin;

class GameFixes
{
private:
    static bool didTryLoadAutoSave;

public:
    static void Initialise ();

    static void TryLoadAutoSave ();

    static void __fastcall HookedProcessMenuOptions (CMenuManager *thisManager,
                                                     void *edx, eMenuPage page);
    static char *__fastcall HookedCTextGet (CText *thisText, void *edx,
                                            char *key);
    static bool HookedGetIsSlowMotionActive ();
    static int __fastcall HookedRadioSetVolume (uint8_t *thisAudioHardware,
                                                void *edx, int a2, int a3,
                                                float volume, int a5);
    static __int16 __fastcall HookedCRunningScriptCollectParameters (
        CRunningScript *thisScript, void *edx, unsigned __int16 num);
    static char HookedCheatCancelEachOther (int id);
    static int __fastcall HookedCMenuManagerDoSettingsBeforeStartingAGame (
        CMenuManager *thisManager);

    static void __fastcall HookedProcessTrainTrackSound (
        CAEVehicleAudioEntity *, void *, cVehicleParams *);
};
