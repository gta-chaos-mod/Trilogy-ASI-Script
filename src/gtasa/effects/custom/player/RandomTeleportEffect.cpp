#include <util/EffectBase.h>
#include <util/RandomHelper.h>
#include <util/Teleportation.h>

#include <extensions/ScriptCommands.h>
#include <CStreaming.h>

using namespace plugin;

class RandomTeleportEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player && Teleportation::CanTeleport ())
        {
            CVector randomPosition
                = CVector (RandomHelper::Random (-3000.0f, 3000.0f),
                           RandomHelper::Random (-3000.0f, 3000.0f), 20.0f);

            Command<eScriptCommands::COMMAND_REQUEST_COLLISION> (
                randomPosition.x, randomPosition.y);
            CStreaming::StreamZoneModels (&randomPosition);
            CStreaming::LoadAllRequestedModels (false);
            CStreaming::LoadScene (&randomPosition);

            randomPosition.z = CWorld::FindGroundZForCoord (randomPosition.x,
                                                            randomPosition.y)
                               + 3.0f;

            float pLevel = 0;
            Call<0x6EB690> (randomPosition.x, randomPosition.y,
                            randomPosition.z, &pLevel, false,
                            nullptr); // CWaterLevel::GetWaterLevel
            if (randomPosition.z < pLevel)
            {
                randomPosition.z = pLevel + 3.0f;
            }

            Teleportation::Teleport (randomPosition);

            inst->Disable ();
        }
    }
};

DEFINE_EFFECT (RandomTeleportEffect, "effect_random_teleport", 0);
