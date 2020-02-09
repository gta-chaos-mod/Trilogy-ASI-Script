#include "DrunkPlayerEffect.h"

DrunkPlayerEffect::DrunkPlayerEffect () : EffectBase ("effect_drunk_player") {}

void
DrunkPlayerEffect::Disable ()
{
    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        Command<eScriptCommands::COMMAND_SET_PLAYER_DRUNKENNESS> (0, 0);
        player->GetPadFromPlayer ()->SetDrunkInputDelay (0);
    }

    EffectBase::Disable ();
}

void
DrunkPlayerEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        Command<eScriptCommands::COMMAND_SET_PLAYER_DRUNKENNESS> (0, 100);
        player->GetPadFromPlayer ()->SetDrunkInputDelay (5);
    }
}
