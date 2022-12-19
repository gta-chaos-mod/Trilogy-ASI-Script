#include "util/EffectBase.h"
#include "util/GenericUtil.h"
#include "util/Teleportation.h"

class TeleportToLibertyCityEffect : public EffectBase
{
    int     wait          = 5000;
    bool    hasTeleported = false;
    CVector fakeLocation  = {-738.0f, 500.0f, 1373.0f};
    CVector previousLocation;
    int     previousInterior = 0;

    bool     wasInVehicle = false;
    CVector  previousMoveSpeed;
    CVector  previousTurnSpeed;
    RwMatrix previousMatrix;

public:
    bool
    CanActivate () override
    {
        return Teleportation::CanTeleport ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        wait          = inst->Random (1000 * 5, 1000 * 15);
        hasTeleported = false;
        wasInVehicle  = false;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle && wasInVehicle)
        {
            vehicle->m_vecMoveSpeed = previousMoveSpeed;
            vehicle->m_vecTurnSpeed = previousTurnSpeed;
            CallMethod<0x59AD20, CMatrix *, RwMatrix *> (vehicle->GetMatrix (),
                                                         &previousMatrix);
        }

        Teleportation::Teleport (previousLocation, previousInterior);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (hasTeleported)
        {
            wait -= (int) GenericUtil::CalculateTick ();
            if (wait > 0) return;

            inst->Disable ();
            return;
        }

        if (!CanActivate ())
        {
            inst->ResetTimer ();
            return;
        }

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            previousLocation = player->GetPosition ();
            previousInterior = player->m_nAreaCode;

            CVehicle *vehicle = FindPlayerVehicle (-1, false);
            if (vehicle)
            {
                wasInVehicle      = true;
                previousLocation  = vehicle->GetPosition ();
                previousMoveSpeed = vehicle->m_vecMoveSpeed;
                previousTurnSpeed = vehicle->m_vecTurnSpeed;
                vehicle->GetMatrix ()->CopyToRwMatrix (&previousMatrix);
            }

            Teleportation::Teleport (fakeLocation, 1);

            hasTeleported = true;
            inst->SetTimerVisible (false);
        }
    }
};

DEFINE_EFFECT (TeleportToLibertyCityEffect, "effect_teleport_to_liberty_city",
               GROUP_TELEPORT);
