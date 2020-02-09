#include "EverybodyBleedNowEffect.h"

EverybodyBleedNowEffect::EverybodyBleedNowEffect ()
    : EffectBase ("effect_everybody_bleed_now")
{
    AddType ("health");
}

void
EverybodyBleedNowEffect::Disable ()
{
    *neverHungryCheat = false;

    for (CPed *ped : CPools::ms_pPedPool)
    {
        ped->m_nPedFlags.bDoBloodyFootprints = false;
        ped->m_nPedFlags.bPedIsBleeding      = false;
    }

    EffectBase::Disable ();
}

void
EverybodyBleedNowEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    bool isLosingHealth = false;

    *neverHungryCheat = true;

    wait -= CalculateTick ();
    if (wait < 0)
    {
        wait           = 3000;
        isLosingHealth = true;
    }

    for (CPed *ped : CPools::ms_pPedPool)
    {
        ped->m_nPedFlags.bDoBloodyFootprints = true;
        ped->m_nPedFlags.bPedIsBleeding      = true;

        if (isLosingHealth)
        {
            ped->m_fHealth -= RandomHelper::Random (1.0f, 3.0f);
        }
    }
}
