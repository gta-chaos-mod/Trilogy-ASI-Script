#include "util/EffectBase.h"
#include "util/Globals.h"

class InfiniteAmmoEffect : public EffectBase
{
    bool *infiniteAmmoCheat = reinterpret_cast<bool *> (0x969178);

public:
    bool
    CanActivate () override
    {
        return !Globals::enabledEffects["one_bullet_magazines"];
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        *this->infiniteAmmoCheat = false;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        *this->infiniteAmmoCheat = true;
    }
};

DEFINE_EFFECT (InfiniteAmmoEffect, "effect_infinite_ammo", 0);