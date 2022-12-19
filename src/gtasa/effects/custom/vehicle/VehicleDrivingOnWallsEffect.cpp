#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CTimer.h>

class VehicleDrivingOnWallsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD (inst, Hooked_IsCarUpsideDown, char (int, int), 0x4655C9,
                     0x4655D6, 0x46564D, 0x46577C, 0x64450F, 0x6451F8, 0x647348,
                     0x651127);

        HOOK_METHOD (inst, Hooked_CVehicle_IsUpsideDown, bool (CVehicle *),
                     0x41DE9F, 0x41E20A, 0x41F2D7, 0x428B55, 0x5182EE, 0x6511D8,
                     0x651A26, 0x661C2D, 0x68D78D, 0x6900C3, 0x69084F,
                     0x6B1A5D);

        HOOK_METHOD (inst, Hooked_CVehicle_IsOnItsSide, bool (CVehicle *),
                     0x5E0901, 0x6511E3, 0x661C40, 0x68D79F, 0x6900D3,
                     0x690861);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        player->m_nPedFlags.CantBeKnockedOffBike = false;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            NegateGravity (vehicle);
            ApplyRelativeGravity (vehicle);
        }

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        player->m_nPedFlags.CantBeKnockedOffBike = true;

        CPlayerInfo *info = player->GetPlayerInfoForThisPlayerPed ();
        if (!info) return;

        info->m_nTimesUpsideDownInARow = 0;
    }

    void
    NegateGravity (CPhysical *physical)
    {
        float gravity = CTimer::ms_fTimeStep * physical->m_fMass * -0.008f;
        physical->ApplyMoveForce ({0, 0, -gravity});
    }

    void
    ApplyRelativeGravity (CPhysical *physical)
    {
        float gravity = CTimer::ms_fTimeStep * physical->m_fMass * -0.008f;

        CMatrixLink *matrix = physical->GetMatrix ();
        physical->ApplyMoveForce ({matrix->at.x * gravity,
                                   matrix->at.y * gravity,
                                   matrix->at.z * gravity});
    }

    static char
    Hooked_IsCarUpsideDown (auto &&cb)
    {
        return false;
    }

    static bool
    Hooked_CVehicle_IsUpsideDown (auto &&cb)
    {
        return false;
    }

    static bool
    Hooked_CVehicle_IsOnItsSide (auto &&cb)
    {
        return false;
    }
};

DEFINE_EFFECT (VehicleDrivingOnWallsEffect, "effect_vehicle_driving_on_walls",
               0);
