#include "GameFixes.h"

void
GameFixes::Initialise ()
{
    // #####################################
    // Load Game Override
    patch::RedirectCall (0x577244, Hooked_ProcessMenuOptions);
    // #####################################

    // #####################################
    // Overwrite CText::Get call to show custom text on "Load Game" option in
    // the menu
    patch::RedirectCall (0x579D73, Hooked_CText_Get);
    // #####################################

    // #####################################
    // Properly modify sound pitch and speed
    for (int address : {0x4EA03B, 0x4EF446})
    {
        patch::RedirectCall (address, Hooked_GetIsSlowMotionActive);
    }
    injector::WriteMemory (0x8CBA6C, 1.0f, true);
    // #####################################

    // #####################################
    // Fix Cesar Vialpando fade-out when it shouldn't happen
    patch::RedirectCall (
        0x47C7C7,
        Hooked_CRunningScript_CollectParameters); // OPCODE: 016A, Fade
    // #####################################

    // #####################################
    // Fix certain cheats cancelling each other out
    for (int address : {0x43934E, 0x4394C6, 0x4394F6, 0x439856})
    {
        patch::RedirectCall (address, Hooked_CheatCancelEachOther);
    }
    // #####################################

    // #####################################
    // Hook "Start New Game" menu
    for (int address : {0x573827, 0x57733B})
    {
        patch::RedirectCall (address,
                             Hooked_CMenuManager_DoSettingsBeforeStartingAGame);
    }
    // #####################################
    // Fix crash on trying to spawn a train as a boat
    patch::RedirectCall (0x501F3B, Hooked_ProcessTrainTrackSound);
    // #####################################
}

void
GameFixes::TryLoadAutoSave ()
{
    GameUtil::LoadFromFile ("chaos_mod\\chaos_autosave.b");
}

void __fastcall GameFixes::Hooked_ProcessMenuOptions (CMenuManager *thisManager,
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
            GameUtil::DeleteAutoSave ();
        }
    }

    thisManager->SwitchToNewScreen (page);
}

char *__fastcall GameFixes::Hooked_CText_Get (CText *thisText, void *edx,
                                              char *key)
{
    std::string key_str (key);
    if (key_str == "FES_NGA")
    {
        if (Config::GetOrDefault ("Chaos.DeleteAutosaveOnNewGame", true)
            || KeyPressed (VK_CONTROL))
        {
            return (char *) "New Game (Delete Autosave)";
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
GameFixes::Hooked_GetIsSlowMotionActive ()
{
    return true;
}

__int16 __fastcall GameFixes::Hooked_CRunningScript_CollectParameters (
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
GameFixes::Hooked_CheatCancelEachOther (int id)
{
    return 0;
}

int __fastcall GameFixes::Hooked_CMenuManager_DoSettingsBeforeStartingAGame (
    CMenuManager *thisManager)
{
    if (Config::GetOrDefault ("Chaos.DeleteAutosaveOnNewGame", true)
        || KeyPressed (VK_CONTROL))
    {
        GameUtil::DeleteAutoSave ();
    }

    if (Config::GetOrDefault ("Chaos.ClearEffectsOnNewGame", true)
        && !Config::GetOrDefault ("CrowdControl.Enabled", false))
    {
        // TODO: Clear effects
        // for (EffectBase *effect : EffectDatabase::GetActiveEffects ())
        // {
        //     effect->Clear ();
        // }
    }
    return thisManager->DoSettingsBeforeStartingAGame ();
}

void __fastcall GameFixes::Hooked_ProcessTrainTrackSound (
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
