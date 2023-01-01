#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/MathHelper.h"
#include "util/hooks/HookMacros.h"

class HonkBoostEffect : public EffectBase
{
    std::map<CVehicle *, bool> wasHornOn;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        wasHornOn.clear ();

        HOOK_METHOD_ARGS (inst, Hooked_ProcessSirensAndHorn,
                          void (CVehicle *, char), 0x6B2B64);
    }

    static void
    Hooked_ProcessSirensAndHorn (auto &&cb, CVehicle *thisVehicle, char horn)
    {
        if (!thisVehicle->m_pDriver || !thisVehicle->m_pDriver->IsPlayer ())
            return;

        CPlayerPed *ped = (CPlayerPed *) thisVehicle->m_pDriver;
        CPad       *pad = ped->GetPadFromPlayer ();
        if (!pad) return;

        if (pad->bHornHistory[pad->iCurrHornHistory])
            thisVehicle->m_nHornCounter = 1;
    }

    void
    OnProcessScripts (EffectInstance *inst) override
    {
        GameUtil::SetVehiclesToRealPhysics ();

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            if (vehicle->m_pDriver && vehicle->m_pDriver->IsPlayer ())
            {
                CPlayerPed *ped = (CPlayerPed *) vehicle->m_pDriver;
                CPad       *pad = ped->GetPadFromPlayer ();
                if (!pad) continue;

                vehicle->m_nHornCounter = pad->GetHorn () ? 1 : 0;
            }

            if (vehicle->m_nHornCounter > 0)
            {
                wasHornOn[vehicle] = true;

                ApplyVehicleSpeed (vehicle, 1.5f, true);
            }
            else if (wasHornOn[vehicle])
            {
                wasHornOn[vehicle] = false;

                ApplyVehicleSpeed (vehicle, 0.75f, false);
            }
        }
    }

    void
    ApplyVehicleSpeed (CVehicle *vehicle, float velocity,
                       bool cantBeKnockedOffBike)
    {
        // Don't apply for empty vehicles or mission ped drivers
        CPed *driver = vehicle->m_pDriver;

        if (!driver) return;
        if (driver->m_nCreatedBy == 2 && driver != FindPlayerPed ()) return;

        CMatrixLink *matrix = vehicle->GetMatrix ();

        vehicle->m_vecMoveSpeed.x = velocity * matrix->up.x;
        vehicle->m_vecMoveSpeed.y = velocity * matrix->up.y;
        vehicle->m_vecMoveSpeed.z = velocity * matrix->up.z;

        vehicle->m_pDriver->m_nPedFlags.CantBeKnockedOffBike
            = cantBeKnockedOffBike;
    }
};

DEFINE_EFFECT (HonkBoostEffect, "effect_honk_boost", 0);