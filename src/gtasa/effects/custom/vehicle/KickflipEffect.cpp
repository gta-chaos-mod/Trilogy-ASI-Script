#include "effects/OneTimeEffect.h"

class KickflipEffect : public OneTimeEffect
{
public:
    bool
    CanActivate () override
    {
        if (!FindPlayerPed ()) return false;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (!vehicle) return false;

        switch (vehicle->m_nVehicleSubClass)
        {
            case VEHICLE_AUTOMOBILE:
            case VEHICLE_MTRUCK:
            case VEHICLE_QUAD: return true;

            default: return false;
        }
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (!vehicle) return;

        vehicle->m_vecMoveSpeed.z = 0.5f;

        CMatrix *matrix = vehicle->GetMatrix ();

        vehicle->m_vecTurnSpeed.x = 0.076f * matrix->up.x;
        vehicle->m_vecTurnSpeed.y = 0.076f * matrix->up.y;
        vehicle->m_vecTurnSpeed.z = 0.076f * matrix->up.z;
    }
};

DEFINE_EFFECT (KickflipEffect, "effect_kickflip", 0);
