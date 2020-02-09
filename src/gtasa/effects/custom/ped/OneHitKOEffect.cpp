#include "OneHitKOEffect.h"

OneHitKOEffect::OneHitKOEffect () : EffectBase ("effect_one_hit_ko")
{
    AddType ("health");
}

void
OneHitKOEffect::InitializeHooks ()
{
    HookCall (0x58EE9A, HookedCHudRenderHealthBar);
}

void
OneHitKOEffect::Disable ()
{
    *neverHungryCheat = false;

    EffectBase::Disable ();
}

void
OneHitKOEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    *neverHungryCheat = true;

    for (CPed *ped : CPools::ms_pPedPool)
    {
        ped->m_fHealth = std::max (0.0f, std::min (ped->m_fHealth, 1.0f));
        ped->m_fArmour = 0.0f;
    }
}

void
OneHitKOEffect::HookedCHudRenderHealthBar (int playerId, signed int x,
                                           signed int y)
{
}
