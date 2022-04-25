#include "util/EffectBase.h"

class OneHitKOEffect : public EffectBase
{
    bool *neverHungryCheat = reinterpret_cast<bool *> (0x969174);

public:
    void
    OnStart (EffectInstance *inst) override
    {
        injector::MakeCALL (0x58EE9A, Hooked_CHud_RenderHealthBar);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        // TODO: Unhook

        *this->neverHungryCheat = false;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        bool isLosingHealth = false;

        *neverHungryCheat = true;

        for (CPed *ped : CPools::ms_pPedPool)
        {
            ped->m_fHealth = std::max (0.0f, std::min (ped->m_fHealth, 1.0f));
            ped->m_fArmour = 0.0f;
        }
    }

    static void
    Hooked_CHud_RenderHealthBar (int playerId, signed int x, signed int y)
    {
    }
};

DEFINE_EFFECT (OneHitKOEffect, "effect_one_hit_ko", GROUP_HEALTH);