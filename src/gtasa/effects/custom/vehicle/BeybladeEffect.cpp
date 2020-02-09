#include "BeybladeEffect.h"

BeybladeEffect::BeybladeEffect () : EffectBase ("effect_beyblade") {}

void
BeybladeEffect::Enable ()
{
    EffectBase::Enable ();

    for (CVehicle *vehicle : CPools::ms_pVehiclePool)
    {
        vehicle->m_vecTurnSpeed.z = 1.5f;
    }
}

void
BeybladeEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    GameUtil::SetVehiclesToRealPhysics ();

    for (CVehicle *vehicle : CPools::ms_pVehiclePool)
    {
        if (vehicle->m_pDriver && vehicle->m_pDriver != FindPlayerPed ()
            && vehicle->m_nCreatedBy != 2)
        {
            vehicle->m_vecTurnSpeed.z = 1.5f;
            vehicle->m_fHealth        = 1000.0f;
        }
    }
}
