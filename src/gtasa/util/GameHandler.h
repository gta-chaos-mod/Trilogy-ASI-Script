#pragma once

#include "util/BoneHelper.h"
#include "util/Config.h"
#include "util/GameFixes.h"
#include "util/GameUtil.h"
#include "util/Websocket.h"

#include <CFileMgr.h>
#include <CTheScripts.h>
#include <CTimer.h>

using namespace plugin;

class GameHandler
{
    static inline bool didTryLoadAutoSave = false;

    static inline int lastMissionsPassed = -1;
    static inline int lastSaved          = 0;
    static inline int lastQuickSave      = 0;

public:
    static void
    Initialise ()
    {
        Config::Init ();
        BoneHelper::Initialise ();
        GameFixes::Initialise ();

        // Check if the mod is already loaded / installed once
        if (injector::ReadMemory<bool> (0xBED000, true))
        {
            MessageBox (NULL,
                        "Chaos Mod is already installed - make sure it isn't "
                        "installed multiple times!",
                        "Chaos Mod Error", 0);
            exit (0);
            return;
        }

        // Write to unused memory space so other mods know that the Chaos mod is
        // installed
        injector::WriteMemory<bool> (0xBED000, true, true);

        patch::RedirectCall (0x5D0D66, Hooked_OpenFile);

        // Make sure to disable effects / delete autosave when starting a new
        // game
        patch::RedirectCall (0x5D18F0, Hooked_CTheScripts_Load);

        // Load Game Override
        patch::RedirectCall (0x577244, Hooked_ProcessMenuOptions);

        // Overwrite CText::Get call to show custom text on "Load Game" option
        // in the menu
        patch::RedirectCall (0x579D73, Hooked_CText_Get);

        // Send websocket message for auto-starting
        // Also hook Start New Game menu
        for (int address : {0x573827, 0x57733B})
        {
            patch::RedirectCall (
                address, Hooked_CMenuManager_DoSettingsBeforeStartingAGame);
        }
    }

    static void
    ProcessGame ()
    {
        HandleAutoSave ();
        HandleQuickSave ();

        HandleVehicleToRealPhysics ();
    }

private:
    static void
    HandleAutoSave ()
    {
        if (Config::GetOrDefault ("Chaos.AutosaveAfterMissionPassed", true))
        {
            int missionsPassed = GameUtil::GetRealMissionsPassed ();
            int currentTime    = CTimer::m_snTimeInMilliseconds;

            if (lastMissionsPassed == -1)
            {
                lastMissionsPassed = missionsPassed;
            }
            else if (lastMissionsPassed > missionsPassed)
            {
                lastMissionsPassed = missionsPassed;
            }

            if (missionsPassed > lastMissionsPassed && lastSaved < currentTime
                && !CTheScripts::IsPlayerOnAMission ())
            {
                lastMissionsPassed = missionsPassed;

                nlohmann::json json;

                json["effectID"]                     = "effect_autosave";
                json["duration"]                     = 1000 * 10;
                json["effectData"]["missionsPassed"] = missionsPassed;

                EffectHandler::HandleFunction (json);

                lastSaved = currentTime + 1000;
            }
        }
    }

    static void
    HandleQuickSave ()
    {
        if (Config::GetOrDefault ("Chaos.QuickSave", false))
        {
            int currentTime = CTimer::m_snTimeInMilliseconds;
            if (KeyPressed (VK_F7) && lastQuickSave < currentTime)
            {
                lastQuickSave = currentTime + 10000;

                nlohmann::json json;

                json["effectID"] = "effect_quicksave";
                json["duration"] = 1000 * 10;

                EffectHandler::HandleFunction (json);
            }
        }
    }

    static void
    HandleVehicleToRealPhysics ()
    {
        if (Config::GetOrDefault ("Chaos.SwitchAllVehiclesToRealPhysics", true))
        {
            GameUtil::SetVehiclesToRealPhysics ();
        }
    }

    static void
    TryLoadAutoSave ()
    {
        GameUtil::LoadFromFile ("chaos_mod\\chaos_autosave.b");
    }

    static void __fastcall Hooked_ProcessMenuOptions (CMenuManager *thisManager,
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

    static char *__fastcall Hooked_CText_Get (CText *thisText, void *edx,
                                              char *key)
    {
        std::string key_str (key);
        if (key_str == "FES_NGA")
        {
            if (Config::GetOrDefault ("Chaos.DeleteAutosaveOnNewGame", true)
                || KeyPressed (VK_CONTROL))
                return (char *) "New Game (Delete Autosave)";
        }
        else if (key_str == "FES_LOA")
        {
            if (KeyPressed (VK_CONTROL)) return (char *) "Load Autosave";
        }
        else if (key_str == "FEP_STG")
        {
            if (!didTryLoadAutoSave)
            {
                didTryLoadAutoSave = true;

                if (Config::GetOrDefault ("Chaos.LoadAutosaveOnGameLoad", true))
                {
                    if (!KeyPressed (VK_CONTROL)) TryLoadAutoSave ();
                }
            }
        }

        return thisText->Get (key);
    }

    static int
    Hooked_OpenFile (const char *path, const char *mode)
    {
        std::string s_path (path), save_path = "GTASAsf9.b";

        size_t start_pos = s_path.find (save_path);
        if (start_pos != std::string::npos)
        {
            s_path.replace (start_pos, save_path.length (),
                            GameUtil::GetLoadFileName ().c_str ());
        }

        return CFileMgr::OpenFile (s_path.c_str (), mode);
    }

    static void __fastcall Hooked_CTheScripts_Load ()
    {
        CTheScripts::Load ();

        lastMissionsPassed = -1;
        lastSaved          = 0;
    }

    static signed int __fastcall Hooked_CMenuManager_DoSettingsBeforeStartingAGame (
        CMenuManager *thisManager)
    {
        if (CTimer::m_snTimeInMilliseconds < 1000 * 60)
        {
            nlohmann::json json;
            json["type"]  = "ChaosMod";
            json["state"] = "auto_start";

            Websocket::SendWebsocketMessage (json);
        }

        if (Config::GetOrDefault ("Chaos.DeleteAutosaveOnNewGame", true)
            || KeyPressed (VK_CONTROL))
        {
            GameUtil::DeleteAutoSave ();
        }

        if (Config::GetOrDefault ("Chaos.ClearEffectsOnNewGame", true)
            && !Config::GetOrDefault ("CrowdControl.Enabled", false))
        {
            for (auto &effect : EffectHandler::GetActiveEffects ())
                effect.Disable ();

            EffectHandler::Clear ();
        }

        return thisManager->DoSettingsBeforeStartingAGame ();
    }
};
