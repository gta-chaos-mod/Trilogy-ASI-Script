#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <FxSystemBP_c.h>

class InvisibleFireEffect : public EffectBase
{
    static const inline unsigned int invalidHashes[] = {
        2287826537, // fire_bike
        4166829922, // fire_car
        445182679,  // overheat_car
        1046403207  // overheat_car_electric
    };

public:
    void
    OnStart (EffectInstance *inst) override
    {
        // FxSystemBP_c::Render
        HOOK_METHOD_ARGS (inst, Hook_FxSystemBP_c_Render,
                          void (FxSystemBP_c *, RwCamera *, float,
                                unsigned char),
                          0x4AA160);
    }

    static void
    Hook_FxSystemBP_c_Render (auto &&cb, FxSystemBP_c *fx, RwCamera *camera,
                              float arg1, unsigned char arg2)
    {
        for (auto hash : invalidHashes)
        {
            if (hash == fx->m_nNameKey) return;
        }

        cb ();
    }
};

DEFINE_EFFECT (InvisibleFireEffect, "effect_invisible_fire", GROUP_VISION);