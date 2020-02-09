#include "WhereIsEverybodyEffect.h"

WhereIsEverybodyEffect::WhereIsEverybodyEffect ()
    : EffectBase ("effect_where_is_everybody")
{
}

void
WhereIsEverybodyEffect::InitializeHooks ()
{
    HookCall (0x5E6900, HookedRenderPedShadow);
}

void
WhereIsEverybodyEffect::Disable ()
{
    for (CPed *ped : CPools::ms_pPedPool)
    {
        ped->m_nPedFlags.bDontRender = false;
    }

    EffectBase::Disable ();
}

void
WhereIsEverybodyEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    for (CPed *ped : CPools::ms_pPedPool)
    {
        ped->m_nPedFlags.bDontRender = true;
    }
}

void
WhereIsEverybodyEffect::HookedRenderPedShadow (CPed *thisPed, float disp_x,
                                               float disp_y, float front_x,
                                               float front_y, float side_x,
                                               float side_y)
{
    if (!thisPed->m_nPedFlags.bDontRender)
    {
        CShadows::StoreShadowForPedObject (thisPed, disp_x, disp_y, front_x,
                                           front_y, side_x, side_y);
    }
}
