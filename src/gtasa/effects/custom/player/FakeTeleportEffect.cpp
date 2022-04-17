#include <util/EffectBase.h>
#include <util/Teleportation.h>

class FakeTeleportEffect : public EffectBase
{
    bool    hasTeleported = false;
    CVector fakeLocation  = {1544.0f, -1353.0f, 332.0f};
    CVector previousLocation;

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
        hasTeleported = false;
        wasInVehicle  = false;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CVehicle *vehicle = FindPlayerVehicle (-1, false);
            if (vehicle && wasInVehicle)
            {
                vehicle->m_vecMoveSpeed = previousMoveSpeed;
                vehicle->m_vecTurnSpeed = previousTurnSpeed;
                CallMethod<0x59AD20, CMatrix *, RwMatrix *> (
                    vehicle->GetMatrix (), &previousMatrix);
            }

            Teleportation::Teleport (previousLocation);
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (hasTeleported)
        {
            return;
        }

        CPlayerPed *player = FindPlayerPed ();
        if (player && CanActivate ())
        {
            previousLocation = player->GetPosition ();

            CVehicle *vehicle = FindPlayerVehicle (-1, false);
            if (vehicle)
            {
                wasInVehicle      = true;
                previousLocation  = vehicle->GetPosition ();
                previousMoveSpeed = vehicle->m_vecMoveSpeed;
                previousTurnSpeed = vehicle->m_vecTurnSpeed;
                vehicle->GetMatrix ()->CopyToRwMatrix (&previousMatrix);
            }

            Teleportation::Teleport (fakeLocation);

            hasTeleported = true;
        }
    }
};

DEFINE_EFFECT (FakeTeleportEffect, "effect_fake_teleport", 0);
