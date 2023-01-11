#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CWeather.h>

class VeryStrongWindEffect : public EffectBase
{
    static inline float   windyness = 5.0f;
    static inline CVector windDir   = CVector ();

public:
    void
    OnStart (EffectInstance *inst) override
    {
        windDir = CVector (inst->Random (-1.0f, 1.0f, windyness),
                           inst->Random (-1.0f, 1.0f, windyness),
                           inst->Random (-0.1f, 0.1f, windyness));

        HOOK (inst, Hooked_CWeather__Update, void (), 0x53BFC2);
    }

    static void
    Hooked_CWeather__Update (auto &&cb)
    {
        cb ();

        CWeather::Wind        = windyness;
        CWeather::WindClipped = windyness;

        CWeather::WindDir.x = windDir.x;
        CWeather::WindDir.y = windDir.y;
        CWeather::WindDir.z = windDir.z;
    }
};

DEFINE_EFFECT (VeryStrongWindEffect, "effect_very_strong_wind", 0);