#include "RandomTeleportEffect.h"

#include "extensions/ScriptCommands.h"

RandomTeleportEffect::RandomTeleportEffect ()
    : EffectBase ("effect_random_teleport")
{
}

void
RandomTeleportEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    CPlayerPed *player = FindPlayerPed ();
    if (player && Teleportation::CanTeleport ())
    {
        CVector randomPosition
            = CVector (RandomHelper::Random (-3000.0f, 3000.0f),
                       RandomHelper::Random (-3000.0f, 3000.0f), 20.0f);

        Command<eScriptCommands::COMMAND_REQUEST_COLLISION> (randomPosition.x,
                                                             randomPosition.y);
        CStreaming::StreamZoneModels (&randomPosition);
        CStreaming::LoadAllRequestedModels (false);
        CStreaming::LoadScene (&randomPosition);

        randomPosition.z
            = CWorld::FindGroundZForCoord (randomPosition.x, randomPosition.y)
              + 3.0f;

        float pLevel = 0;
        Call<0x6EB690> (randomPosition.x, randomPosition.y, randomPosition.z,
                        &pLevel, false, 1); // CWaterLevel::GetWaterLevel
        if (randomPosition.z < pLevel)
        {
            randomPosition.z = pLevel + 3.0f;
        }

        Teleportation::Teleport (randomPosition);

        Disable ();
    }
}
