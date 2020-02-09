#include "ZeroSuspensionDampingEffect.h"

ZeroSuspensionDampingEffect::ZeroSuspensionDampingEffect ()
    : EffectBase ("effect_high_suspension_damping")
{
    AddType ("handling");
}

void
ZeroSuspensionDampingEffect::Enable ()
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
ZeroSuspensionDampingEffect::Disable ()
{
    for (int i = 0; i < 210; i++)
    {
        gHandlingDataMgr.m_aVehicleHandling[i] = origVehicleHandling[i];
    }

    EffectBase::Disable ();
}

void
ZeroSuspensionDampingEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    GameUtil::SetVehiclesToRealPhysics ();
}
