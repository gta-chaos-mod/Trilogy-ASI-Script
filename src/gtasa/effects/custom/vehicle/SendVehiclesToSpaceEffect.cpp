#include "SendVehiclesToSpaceEffect.h"

SendVehiclesToSpaceEffect::SendVehiclesToSpaceEffect ()
    : EffectPlaceholder ("effect_send_vehicles_to_space")
{
}

void
SendVehiclesToSpaceEffect::Enable ()
{
    EffectPlaceholder::Enable ();

    GameUtil::SetVehiclesToRealPhysics ();

    for (CVehicle *vehicle : CPools::ms_pVehiclePool)
    {
        vehicle->m_vecMoveSpeed.x += RandomHelper::Random (-2.5f, 2.5f);
        vehicle->m_vecMoveSpeed.y += RandomHelper::Random (-2.5f, 2.5f);
        vehicle->m_vecMoveSpeed.z += 10.0f;
    }
}
