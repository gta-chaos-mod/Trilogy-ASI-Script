#include "util/EffectBase.h"

class DisableHealingEffect : public EffectBase
{
    float lastHealthValue = 0.0f;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        lastHealthValue = player->m_fHealth;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        if (!player->IsAlive ())
        {
            lastHealthValue = player->m_fMaxHealth;
            return;
        }

        lastHealthValue = std::min (lastHealthValue, player->m_fHealth);
        player->m_fHealth = lastHealthValue;
    }
};

DEFINE_EFFECT (DisableHealingEffect, "effect_disable_healing",
               GROUP_HEALTH);