#include "UnflippableVehiclesEffect.h"

UnflippableVehiclesEffect::UnflippableVehiclesEffect ()
    : EffectBase ("effect_little_suspension_damping")
{
    AddType ("handling");
}

void
UnflippableVehiclesEffect::Enable ()
{
    EffectBase::Enable ();

    for (int i = 0; i < 210; i++)
    {
        origVehicleHandling[i] = gHandlingDataMgr.m_aVehicleHandling[i];
    }

    for (int i = 0; i < 210; i++)
    {
        gHandlingDataMgr.m_aVehicleHandling[i].m_vecCentreOfMass.z = -2.5f;
    }
}

void
UnflippableVehiclesEffect::Disable ()
{
    for (int i = 0; i < 210; i++)
    {
        gHandlingDataMgr.m_aVehicleHandling[i] = origVehicleHandling[i];
    }

    EffectBase::Disable ();
}

void
UnflippableVehiclesEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    GameUtil::SetVehiclesToRealPhysics ();
}
