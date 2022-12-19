#include "util/EffectBase.h"
#include "util/Teleportation.h"

#include <CStreaming.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class TeleportToZeroEffect : public EffectBase
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
        if (!CanActivate ())
        {
            inst->ResetTimer ();
            return;
        }

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
        if (playerVehicle)
        {
            Command<eScriptCommands::
                        COMMAND_REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION> (
                player, playerVehicle);
        }

        Teleportation::Teleport (CVector (-2245.66f, 128.89f, 35.0f));
        player->m_vecMoveSpeed = CVector (0, 0, 0);
        Command<eScriptCommands::COMMAND_RESTORE_CAMERA_JUMPCUT> ();

        inst->Disable ();
    }
};

DEFINE_EFFECT (TeleportToZeroEffect, "effect_teleport_to_zero", GROUP_TELEPORT);
