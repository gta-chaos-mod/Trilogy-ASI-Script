#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

class OneHitKOEveryoneEffect : public EffectBase
{
    struct PedInfo
    {
        float previousHealth = 100.0f;
        float previousArmor  = 0.0f;
    };
    static inline std::map<CPed *, PedInfo> pedInfoMap = {};

    bool *neverHungryCheat = reinterpret_cast<bool *> (0x969174);

public:
    void
    OnStart (EffectInstance *inst) override
    {
        pedInfoMap.clear ();

        // CHud::RenderHealthBar
        HOOK (inst, Hooked_Empty, void (int, signed int, signed int), 0x58EE9A);

        plugin::Events::pedCtorEvent += OnPedCreated;
    }

    static void
    OnPedCreated (CPed *ped)
    {
        pedInfoMap[ped] = {.previousHealth = ped->m_fHealth,
                           .previousArmor  = ped->m_fArmour};
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        *this->neverHungryCheat = false;

        for (auto &[ped, pedInfo] : pedInfoMap)
        {
            ped->m_fHealth = pedInfo.previousHealth;
            ped->m_fArmour = pedInfo.previousArmor;
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        bool isLosingHealth = false;

        *neverHungryCheat = true;

        for (CPed *ped : CPools::ms_pPedPool)
        {
            if (!pedInfoMap.contains (ped))
            {
                pedInfoMap[ped] = {.previousHealth = ped->m_fHealth,
                                   .previousArmor  = ped->m_fArmour};
            }

            ped->m_fHealth = std::max (0.0f, std::min (ped->m_fHealth, 1.0f));
            ped->m_fArmour = 0.0f;
        }
    }

    static void
    Hooked_Empty (auto &&cb)
    {
    }
};

DEFINE_EFFECT (OneHitKOEveryoneEffect, "effect_one_hit_ko_everyone",
               GROUP_HEALTH);