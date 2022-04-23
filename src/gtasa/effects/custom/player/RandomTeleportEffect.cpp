#include <util/EffectBase.h>
#include <util/Teleportation.h>

#include <CStreaming.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class RandomTeleportEffect : public EffectBase
{
public:
    bool
    CanActivate () override
    {
        return Teleportation::CanTeleport ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player && CanActivate ())
        {
            CVector randomPosition = FindSuitableTeleportPosition (inst);

            Teleportation::Teleport (randomPosition);

            inst->Disable ();
        }
    }

    CVector
    FindSuitableTeleportPosition (EffectInstance *inst)
    {
        CVector randomPosition
            = CVector (inst->Random (-3000.0f, 3000.0f),
                       inst->Random (-3000.0f, 3000.0f), 0.0f);

        Command<eScriptCommands::COMMAND_REQUEST_COLLISION> (randomPosition.x,
                                                             randomPosition.y);
        CStreaming::StreamZoneModels (&randomPosition);
        CStreaming::LoadAllRequestedModels (false);
        CStreaming::LoadScene (&randomPosition);

        bool groundResult = false;
        randomPosition.z
            = CWorld::FindGroundZFor3DCoord (randomPosition.x, randomPosition.y,
                                             randomPosition.z + 250.0f,
                                             &groundResult, 0)
              + 3.0f;

        if (!groundResult) return FindSuitableTeleportPosition (inst);

        float waterLevel = 0.0f;
        Command<eScriptCommands::COMMAND_GET_WATER_HEIGHT_AT_COORDS> (
            randomPosition.x, randomPosition.y, true, &waterLevel);

        if (randomPosition.z <= waterLevel)
            return FindSuitableTeleportPosition (inst);

        return randomPosition;
    }
};

DEFINE_EFFECT (RandomTeleportEffect, "effect_random_teleport", 0);
