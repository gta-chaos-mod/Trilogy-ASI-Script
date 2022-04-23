#include "util/EffectBase.h"
#include "util/GenericUtil.h"

class EverybodyBleedNowEffect : public EffectBase
{
    int   wait             = 0;
    bool *neverHungryCheat = reinterpret_cast<bool *> (0x969174);

public:
    void
    OnEnd (EffectInstance *inst) override
    {
        *this->neverHungryCheat = false;

        for (CPed *ped : CPools::ms_pPedPool)
        {
            ped->m_nPedFlags.bDoBloodyFootprints = false;
            ped->m_nPedFlags.bPedIsBleeding      = false;
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        bool isLosingHealth = false;

        *this->neverHungryCheat = true;

        this->wait -= (int) GenericUtil::CalculateTick ();
        if (this->wait < 0)
        {
            this->wait     = 3000;
            isLosingHealth = true;
        }

        for (CPed *ped : CPools::ms_pPedPool)
        {
            ped->m_nPedFlags.bDoBloodyFootprints = true;
            ped->m_nPedFlags.bPedIsBleeding      = true;

            if (isLosingHealth) ped->m_fHealth -= inst->Random (0.0f, 3.0f);
        }
    }
};

DEFINE_EFFECT (EverybodyBleedNowEffect, "effect_everybody_bleed_now",
               GROUP_HEALTH);