#include "OneHitKOEffect.h"

OneHitKOEffect::OneHitKOEffect () : EffectBase ("effect_one_hit_ko")
{
    AddType ("health");
}

void
OneHitKOEffect::InitializeHooks ()
{
    // Health
    HookCall (0x558C10, HookedCFontPrintString);
    HookCall (0x558CF4, HookedCFontPrintString);

    // Armor
    HookCall (0x558E80, HookedCFontPrintString);
    HookCall (0x558F64, HookedCFontPrintString);
}

void
OneHitKOEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    for (CPed *ped : CPools::ms_pPedPool)
    {
        ped->m_fHealth = max (0.0f, min (ped->m_fHealth, 2.0f));
        ped->m_fArmour = 0.0f;
    }
}

void
OneHitKOEffect::HookedCFontPrintString (float x, float y, char *text)
{
}
