#include "UsainBoltEffect.h"

UsainBoltEffect::UsainBoltEffect () : EffectBase ("effect_usain_bolt") {}

// TODO: Disable fall and maybe also collision damage

void
UsainBoltEffect::Enable ()
{
    EffectBase::Enable ();

    injector::WriteMemory (0x8D2458, 0.25f);
}

void
UsainBoltEffect::Disable ()
{
    injector::WriteMemory (0x8D2458, 5.0f);

    EffectBase::Disable ();
}
