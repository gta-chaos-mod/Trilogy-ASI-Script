#include "UsainBoltEffect.h"

UsainBoltEffect::UsainBoltEffect () : EffectBase ("usain_bolt_effect") {}

void
UsainBoltEffect::Enable ()
{
    EffectBase::Enable ();

    *(float*) (0x8D2458) = 0.1f;
    
}

void
UsainBoltEffect::Disable ()
{
    *(float*) (0x8D2458) = 5.0f;

    EffectBase::Disable ();
}
