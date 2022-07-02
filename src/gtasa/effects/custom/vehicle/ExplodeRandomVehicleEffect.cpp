#include "util/EffectBase.h"
#include "util/GameUtil.h"

class ExplodeRandomVehicleEffect : public EffectBase
{
public:
    bool
    CanActivate () override
    {
        return GameUtil::IsPlayerSafe ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (!CanActivate ()) return;

        CPlayerPed *player  = FindPlayerPed ();
        CVehicle   *vehicle = GetRandomVehicle (inst);
        if (!vehicle || !vehicle->CanBeDriven ()
            || vehicle->m_nStatus == STATUS_WRECKED
            || vehicle->m_pDriver == player)
        {
            inst->ResetTimer ();
            return;
        }

        vehicle->m_nPhysicalFlags.bExplosionProof = false;
        vehicle->BlowUpCar (nullptr, false);

        inst->Disable ();
    }

    CVehicle *
    GetRandomVehicle (EffectInstance *inst, int attempts = 0)
    {
        int randomNumber  = inst->Random (0, CPools::ms_pVehiclePool->m_nSize);
        CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt (randomNumber);

        if (IsVehiclePointerValid (vehicle) && vehicle->m_pDriver)
            return vehicle;

        attempts += 1;
        if (attempts > 10) return nullptr;

        return GetRandomVehicle (inst, attempts);
    }
};

DEFINE_EFFECT (ExplodeRandomVehicleEffect, "effect_explode_random_vehicle", 0);