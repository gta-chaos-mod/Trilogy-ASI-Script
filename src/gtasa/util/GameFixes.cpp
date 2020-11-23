#include "GameFixes.h"

bool GameFixes::didTryLoadAutoSave = false;

void
GameFixes::Initialise ()
{
    // #####################################
    // Load Game Override
    patch::RedirectCall (0x577244, HookedProcessMenuOptions);
    // #####################################

    // #####################################
    // Overwrite CText::Get call to show custom text on "Load Game" option in
    // the menu
    patch::RedirectCall (0x579D73, HookedCTextGet);
    // #####################################

    // #####################################
    // Properly modify sound pitch and speed
    for (int address : {0x4EA03B, 0x4EF446})
    {
        patch::RedirectCall (address, HookedGetIsSlowMotionActive);
    }
    injector::WriteMemory (0x8CBA6C, 1.0f, true);

    patch::RedirectCall (0x4EA258, HookedRadioSetVolume);
    // #####################################

    // #####################################
    // Fix Cesar Vialpando fade-out when it shouldn't happen
    patch::RedirectCall (
        0x47C7C7, HookedCRunningScriptCollectParameters); // OPCODE: 016A, Fade
    // #####################################

    // #####################################
    // Fix certain cheats cancelling each other out
    for (int address : {0x43934E, 0x4394C6, 0x4394F6, 0x439856})
    {
        patch::RedirectCall (address, HookedCheatCancelEachOther);
    }
    // #####################################

    // #####################################
    // Hook "Start New Game" menu
    for (int address : {0x573827, 0x57733B})
    {
        patch::RedirectCall (address,
                             HookedCMenuManagerDoSettingsBeforeStartingAGame);
    }
    // #####################################
    // Fix crash on trying to spawn a train as a boat
    patch::RedirectCall (0x501F3B, HookedProcessTrainTrackSound);
    // #####################################
}

void
GameFixes::TryLoadAutoSave ()
{
    GameUtil::LoadFromFile ("chaos_mod\\chaos_autosave.b");
}

void __fastcall GameFixes::HookedProcessMenuOptions (CMenuManager *thisManager,
                                                     void *edx, eMenuPage page)
{
    if (page == eMenuPage::MENUPAGE_LOAD_GAME)
    {
        if (KeyPressed (VK_CONTROL))
        {
            TryLoadAutoSave ();
            return;
        }
    }
    else if (page == eMenuPage::MENUPAGE_NEW_GAME_ASK)
    {
        if (Config::GetOrDefault ("Chaos.DeleteAutosaveOnNewGame", true)
            || KeyPressed (VK_CONTROL))
        {
            GameUtil::DeleteAutosave ();
        }
    }

    thisManager->SwitchToNewScreen (page);
}

char *__fastcall GameFixes::HookedCTextGet (CText *thisText, void *edx,
                                            char *key)
{
    std::string key_str (key);
    if (key_str == "FES_NGA")
    {
        if (Config::GetOrDefault ("Chaos.DeleteAutosaveOnNewGame", true)
            || KeyPressed (VK_CONTROL))
        {
            return (char *) "(New Game (Delete Autosave))";
        }
    }
    else if (key_str == "FES_LOA")
    {
        if (KeyPressed (VK_CONTROL))
        {
            return (char *) "Load Autosave";
        }
    }
    else if (key_str == "FEP_STG")
    {
        if (!didTryLoadAutoSave)
        {
            didTryLoadAutoSave = true;

            if (Config::GetOrDefault ("Chaos.LoadAutosaveOnGameLoad", true))
            {
                if (!KeyPressed (VK_CONTROL))
                {
                    TryLoadAutoSave ();
                }
            }
        }
    }

    return thisText->Get (key);
}

bool
GameFixes::HookedGetIsSlowMotionActive ()
{
    return true;
}

int __fastcall GameFixes::HookedRadioSetVolume (uint8_t *thisAudioHardware,
                                                void *edx, int a2, int a3,
                                                float volume, int a5)
{
    volume = GameUtil::GetAudioVolumeOrOverride (volume);
    return CallMethodAndReturn<int, 0x4D8870, uint8_t *> (thisAudioHardware, a2,
                                                          a3, volume, a5);
}

__int16 __fastcall GameFixes::HookedCRunningScriptCollectParameters (
    CRunningScript *thisScript, void *edx, unsigned __int16 num)
{
    __int16 result
        = CallMethodAndReturn<__int16, 0x464080, CRunningScript *> (thisScript,
                                                                    num);

    std::string missionName
        = GenericUtil::ToUpper (std::string (thisScript->m_szName));
    if (missionName == "CESAR1")
    {
        if (CTheScripts::ScriptParams[0].iParam == 0
            && CTheScripts::ScriptParams[1].iParam == 0)
        {
            CTheScripts::ScriptParams[1].iParam = 1;
        }
    }

    return result;
}

char
GameFixes::HookedCheatCancelEachOther (int id)
{
    return 0;
}

int __fastcall GameFixes::HookedCMenuManagerDoSettingsBeforeStartingAGame (
    CMenuManager *thisManager)
{
    if (Config::GetOrDefault ("Chaos.DeleteAutosaveOnNewGame", true)
        || KeyPressed (VK_CONTROL))
    {
        GameUtil::DeleteAutosave ();
    }

    if (Config::GetOrDefault ("Chaos.ClearEffectsOnNewGame", true)
        && !Config::GetOrDefault ("CrowdControl.Enabled", false))
    {
        for (EffectBase *effect : EffectDatabase::GetActiveEffects ())
        {
            effect->Clear ();
        }
    }
    return thisManager->DoSettingsBeforeStartingAGame ();
}

void __fastcall GameFixes::HookedProcessTrainTrackSound (
    CAEVehicleAudioEntity *thisEntity, void *, cVehicleParams *params)
{
    if (params->m_nVehicleSubclass == VEHICLE_BOAT)
    {
        switch (params->m_pVehicle->m_nModelIndex)
        {
        case MODEL_FREIGHT:
        case MODEL_FREIFLAT: return;
        }
    }

    CallMethod<0x4FA3F0> (thisEntity, params);
}
