#include "HighSuspensionDampingEffect.h"

HighSuspensionDampingEffect::HighSuspensionDampingEffect ()
    : EffectBase ("effect_high_suspension_damping")
{
    AddType ("handling");
}

void
HighSuspensionDampingEffect::Enable ()
{
    EffectBase::Enable ();

    for (int i = 0; i < 210; i++)
    {
        origVehicleHandling[i] = gHandlingDataMgr.m_aVehicleHandling[i];
    }

    for (int i = 0; i < 210; i++)
    {
        gHandlingDataMgr.m_aVehicleHandling[i].m_fSuspensionDampingLevel
            = suspension;
    }
}

void
HighSuspensionDampingEffect::Disable ()
{
    for (int i = 0; i < 210; i++)
    {
        gHandlingDataMgr.m_aVehicleHandling[i] = origVehicleHandling[i];
    }

    EffectBase::Disable ();
}

void
HighSuspensionDampingEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    GameUtil::SetVehiclesToRealPhysics ();
}
