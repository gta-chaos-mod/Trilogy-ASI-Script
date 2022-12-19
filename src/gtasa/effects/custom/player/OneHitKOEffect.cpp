#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

class OneHitKOEffect : public EffectBase
{
    float previousHealth   = 100.0f;
    float previousArmor    = 0.0f;
    bool *neverHungryCheat = reinterpret_cast<bool *> (0x969174);

public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        previousHealth = player->m_fHealth;
        previousArmor  = player->m_fArmour;

        // CHud::RenderHealthBar
        HOOK (inst, Hooked_Empty, void (int, signed int, signed int), 0x58EE9A);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        *this->neverHungryCheat = false;

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        player->m_fHealth = previousHealth;
        player->m_fArmour = previousArmor;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        bool isLosingHealth = false;

        *neverHungryCheat = true;

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        player->m_fHealth = std::max (0.0f, std::min (player->m_fHealth, 1.0f));
        player->m_fArmour = 0.0f;
    }

    static void
    Hooked_Empty (auto &&cb)
    {
    }
};

DEFINE_EFFECT (OneHitKOEffect, "effect_one_hit_ko", GROUP_HEALTH);