#include "util/EffectBase.h"
#include "util/EffectHandler.h"
#include "util/GameUtil.h"
#include "util/GenericUtil.h"
#include "util/Teleportation.h"

#include <CGangWars.h>
#include <CTheScripts.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class FakePassCurrentMissionEffect : public EffectBase
{
    bool handledEverything = false;
    bool handledMission    = false;
    bool lastIsOnMission   = false;

    int wait = 500;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        handledEverything = false;
        handledMission    = false;
        lastIsOnMission   = false;

        wait = 500;

        if (!CTheScripts::IsPlayerOnAMission ()) handledEverything = true;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (handledEverything)
        {
            inst->OverrideName (std::string (inst->GetName ()) + "?");
            inst->Disable ();
            return;
        }

        if (!handledMission)
        {
            if (CCutsceneMgr::ms_running)
            {
                inst->ResetTimer ();
                return;
            }

            bool wasOnMission = CTheScripts::IsPlayerOnAMission ();
            if (wasOnMission)
            {
                int randomMoney = 1000 * inst->Random (5, 25);

                Command<Commands::CLEAR_SMALL_PRINTS> ();
                Command<eScriptCommands::COMMAND_PRINT_WITH_NUMBER_BIG> (
                    "M_PASSS", randomMoney, 5000, 1);
                Command<Commands::PLAY_MISSION_PASSED_TUNE> (1);

                CPlayerPed *player = FindPlayerPed ();
                if (player)
                {
                    player->SetWantedLevel (0);
                    player->GetPlayerInfoForThisPlayerPed ()->m_nMoney
                        += randomMoney;
                }

                for (auto i = CTheScripts::pActiveScripts; i; i = i->m_pNext)
                {
                    if (i->m_bIsMission && i->m_bIsActive && !i->m_bIsExternal)
                    {
                        Teleportation::TeleportOutOfMission (
                            GenericUtil::ToUpper (std::string (i->m_szName)));
                        break;
                    }
                }
            }
            Command<Commands::FAIL_CURRENT_MISSION> ();
            CGangWars::EndGangWar (false);

            ClearPlayerStatus ();

            handledMission = true;

            if (wasOnMission)
            {
                nlohmann::json json;

                json["effectID"] = "effect_autosave";
                json["duration"] = 1000 * 10;
                json["effectData"]["missionsPassed"]
                    = GameUtil::GetRealMissionsPassed ();

                EffectHandler::HandleFunction (json);

                inst->SetTimerVisible (false);
            }
        }
        else
        {
            wait -= (int) GenericUtil::CalculateTick ();
            if (wait > 0) return;

            bool isOnMission = CTheScripts::IsPlayerOnAMission ();

            if (isOnMission && !lastIsOnMission && handledMission)
            {
                handledEverything = true;
            }

            lastIsOnMission = isOnMission;
        }
    }

    void
    ClearPlayerStatus ()
    {
        GameUtil::RemovePlayerBalaclava ();

        CPed *player;
        Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR> (0, &player);
        if (player)
        {
            Command<eScriptCommands::COMMAND_SKIP_CUTSCENE_END> ();
            Command<eScriptCommands::COMMAND_CLEAR_CHAR_TASKS> (player);
            Command<eScriptCommands::COMMAND_SET_CAMERA_BEHIND_PLAYER> ();
            Command<eScriptCommands::COMMAND_SWITCH_WIDESCREEN> (0);
            Command<eScriptCommands::COMMAND_SET_PLAYER_CONTROL> (0, 1);
            Command<eScriptCommands::COMMAND_RESTORE_CAMERA_JUMPCUT> ();
            Command<eScriptCommands::COMMAND_DETACH_CHAR_FROM_CAR> (player);
        }
    }
};

DEFINE_EFFECT (FakePassCurrentMissionEffect, "effect_fake_pass_current_mission",
               0);