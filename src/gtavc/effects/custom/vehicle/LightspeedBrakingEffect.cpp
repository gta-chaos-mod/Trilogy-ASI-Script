#include "LightspeedBrakingEffect.h"

LightspeedBrakingEffect::LightspeedBrakingEffect ()
    : EffectBase ("effect_lightspeed_braking")
{
    AddType ("handling");
}

void
LightspeedBrakingEffect::Enable ()
{
    EffectBase::Enable ();

    for (int i = 0; i < 106; i++)
    {
        origVehicleHandling[i] = gHandlingDataMgr.m_aVehicleHandling[i];
    }

    for (int i = 0; i < 106; i++)
    {
        gHandlingDataMgr.m_aVehicleHandling[i].fBrakeDeceleration *= -1.0f;
    }
}

void
LightspeedBrakingEffect::Disable ()
{
    for (int i = 0; i < 106; i++)
    {
        gHandlingDataMgr.m_aVehicleHandling[i] = origVehicleHandling[i];
    }

    EffectBase::Disable ();
}

void
LightspeedBrakingEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    GameUtil::SetVehiclesToRealPhysics ();
}
