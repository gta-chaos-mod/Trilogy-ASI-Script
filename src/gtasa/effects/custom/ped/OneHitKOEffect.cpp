#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

class OneHitKOEffect : public EffectBase
{
    bool *neverHungryCheat = reinterpret_cast<bool *> (0x969174);

public:
    void
    OnStart (EffectInstance *inst) override
    {
        // CHud::RenderHealthBar
        HOOK (inst, Hooked_Empty, void (int, signed int, signed int), 0x58EE9A);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
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
    Hooked_Empty (auto &&cb)
    {
    }
};

DEFINE_EFFECT (OneHitKOEffect, "effect_one_hit_ko", GROUP_HEALTH);