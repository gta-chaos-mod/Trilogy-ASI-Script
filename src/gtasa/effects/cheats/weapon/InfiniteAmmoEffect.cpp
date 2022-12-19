#include "util/EffectBase.h"
#include "util/Globals.h"

class InfiniteAmmoEffect : public EffectBase
{
    bool *infiniteAmmoCheat = reinterpret_cast<bool *> (0x969178);

public:
    bool
    CanActivate () override
    {
        return !Globals::isOneBulletMagazinesEffectEnabled;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        Globals::isInfiniteAmmoEffectEnabled = true;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Globals::isInfiniteAmmoEffectEnabled = false;

        *this->infiniteAmmoCheat = false;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        *this->infiniteAmmoCheat = true;
    }
};

DEFINE_EFFECT (InfiniteAmmoEffect, "effect_infinite_ammo", 0);