#include "FailCurrentMissionEffect.h"

FailCurrentMissionEffect::FailCurrentMissionEffect ()
    : EffectPlaceholder ("effect_fail_current_mission")
{
}

void
FailCurrentMissionEffect::Enable ()
{
    EffectPlaceholder::Enable ();

    if (CTheScripts::IsPlayerOnAMission ())
    {
        Command<Commands::CLEAR_SMALL_PRINTS> ();
        Command<Commands::PRINT_BIG_Q> ("M_FAIL", 5000, 1);

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
}

void
FailCurrentMissionEffect::ClearPlayerStatus ()
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
