#include "IAmSpeedEffect.h"

IAmSpeedEffect::IAmSpeedEffect () : EffectBase ("effect_i_am_speed") {}

// TODO: Disable fall and maybe also collision damage

void
IAmSpeedEffect::Enable ()
{
    EffectBase::Enable ();

    injector::WriteMemory(0x8D2458, 0.25f);
    
}

void
IAmSpeedEffect::Disable ()
{
    injector::WriteMemory(0x8D2458, 5.0f);

    EffectBase::Disable ();
}
