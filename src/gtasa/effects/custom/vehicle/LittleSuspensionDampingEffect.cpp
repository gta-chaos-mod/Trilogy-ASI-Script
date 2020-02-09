#include "LittleSuspensionDampingEffect.h"

LittleSuspensionDampingEffect::LittleSuspensionDampingEffect ()
    : EffectBase ("effect_high_suspension_damping")
{
    AddType ("handling");
}

void
LittleSuspensionDampingEffect::Enable ()
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
LittleSuspensionDampingEffect::Disable ()
{
    for (int i = 0; i < 210; i++)
    {
        gHandlingDataMgr.m_aVehicleHandling[i] = origVehicleHandling[i];
    }

    EffectBase::Disable ();
}

void
LittleSuspensionDampingEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    GameUtil::SetVehiclesToRealPhysics ();
}
