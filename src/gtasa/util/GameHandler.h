#pragma once

#include "util/BoneHelper.h"
#include "util/Config.h"
#include "util/GameFixes.h"
#include "util/GameUtil.h"
#include "util/GlobalHooksInstance.h"
#include "util/GlobalRenderer.h"
#include "util/Websocket.h"

#include <CAnimManager.h>
#include <CFileMgr.h>
#include <CReferences.h>
#include <CTheScripts.h>
#include <CTimer.h>

using namespace plugin;

class GameHandler
{
    static inline bool initialised = false;

    static inline bool didTryLoadAutoSave = false;

    static inline int lastMissionsPassed = -1;
    static inline int lastSaved          = 0;
    static inline int lastQuickSave      = 0;

public:
    static void
    Initialise ()
    {
        if (initialised) return;

        Config::Init ();
        BoneHelper::Initialise ();
        GlobalRenderer::Initialise ();
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

        // Custom save-file hook for "Slot 9"
        HOOK_ARGS (globalHooksInstance.Get (), Hooked_OpenFile,
                   FILE * (const char *, const char *), 0x5D0D66);

        // Make sure to disable effects / delete autosave when starting a new
        // game
        HOOK (globalHooksInstance.Get (), Hooked_CTheScripts_Load,
              unsigned int (), 0x5D18F0);

        // Load Game Override
        HOOK_METHOD_ARGS (globalHooksInstance.Get (), Hooked_ProcessMenuOptions,
                          void (CMenuManager *, eMenuPage), 0x577244);

        // Overwrite CText::Get call to show custom text on "Load Game" option
        // in the menu
        HOOK_METHOD_ARGS (globalHooksInstance.Get (), Hooked_CText_Get,
                          char *(CText *, char *), 0x579D73);

        // Send websocket message for auto-starting
        // Also hook Start New Game menu
        HOOK_METHOD_ARGS (globalHooksInstance.Get (),
                          Hooked_CMenuManager_DoSettingsBeforeStartingAGame,
                          static int (CMenuManager *), 0x573827, 0x57733B);

        // Broken parachute fix where it plays the animation but CJ can't be
        // controlled mid-air
        HOOK (globalHooksInstance.Get (), Hooked_BrokenParachuteFix, CPed * (),
              0x443082);

        // Can Ped Jump Out Of Car
        HOOK_METHOD_ARGS (globalHooksInstance.Get (), Hooked_CanPedStepOutCar,
                          bool (CVehicle *, CPed *), 0x6D1F30);

        // Fix map crash when trying to load the legend
        HOOK_ARGS (globalHooksInstance.Get (), Hooked_FixMapLegendCrash,
                   void (float, float, char *), 0x582DEE);

        initialised = true;
    }

    static void
    ProcessGame ()
    {
        HandleAutoSave ();
        HandleQuickSave ();

        HandleVehicleToRealPhysics ();
        HandleParachutingWithoutParachuteFix ();
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
    HandleParachutingWithoutParachuteFix ()
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        bool hasParachute
            = player->m_aWeapons[player->m_nActiveWeaponSlot].m_nType
              == WEAPON_PARACHUTE;

        if (hasParachute) return;

        std::vector<std::string> anims = {
            "FALL_SKYDIVE",       "FALL_SKYDIVE_L", "FALL_SKYDIVE_R",
            "FALL_SKYDIVE_ACCEL", "PARA_OPEN",      "PARA_FLOAT",
            "PARA_DECEL",         "PARA_STEERL",    "PARA_STEERR",
        };

        for (std::string anim : anims)
        {
            if (RpAnimBlendClumpGetAssociation (player->m_pRwClump,
                                                anim.c_str ()))
            {
                player->m_pIntelligence->ClearTasks (true, false);
                break;
            }
        }
    }

    static void
    TryLoadAutoSave ()
    {
        GameUtil::LoadFromFile ("chaos_mod\\chaos_autosave.b");
    }

    static FILE *
    Hooked_OpenFile (auto &&cb, const char *&path, const char *mode)
    {
        std::string s_path (path), save_path = "GTASAsf9.b";

        size_t start_pos = s_path.find (save_path);
        if (start_pos != std::string::npos)
        {
            s_path.replace (start_pos, save_path.length (),
                            GameUtil::GetLoadFileName ().c_str ());
        }

        path = s_path.c_str ();

        return cb ();
    }

    static unsigned int
    Hooked_CTheScripts_Load (auto &&cb)
    {
        lastMissionsPassed = -1;
        lastSaved          = 0;

        return cb ();
    }

    static void
    Hooked_ProcessMenuOptions (auto &&cb, CMenuManager *thisManager,
                               eMenuPage page)
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

        cb ();
    }

    static char *
    Hooked_CText_Get (auto &&cb, CText *thisText, char *&key)
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

        return cb ();
    }

    static signed int
    Hooked_CMenuManager_DoSettingsBeforeStartingAGame (
        auto &&cb, CMenuManager *thisManager)
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

        return cb ();
    }

    static CPed *
    Hooked_BrokenParachuteFix (auto &&cb)
    {
        int &parachuteCreationStage = GameUtil::GetGlobalVariable<int> (1497);
        int &freefallStage          = GameUtil::GetGlobalVariable<int> (1513);

        parachuteCreationStage = 0;
        freefallStage          = 0;

        return cb ();
    }

    static bool
    Hooked_CanPedStepOutCar (auto &&cb, CVehicle *vehicle, CPed *ped)
    {
        return !vehicle->CanPedJumpOutCar (ped);
    }

    // Thanks to Parik's Rainbomizer code for this
    // https://github.com/Parik27/SA.Rainbomizer/blob/master/src/blips.cc#L39
    static void
    Hooked_FixMapLegendCrash (auto &&cb, float x, float y, char *&text)
    {
        if (int (text) < 0x2000) text = (char *) "Absolute Legend.";

        cb ();
    }
};
