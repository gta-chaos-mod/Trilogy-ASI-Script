#include "util/EffectBase.h"

using namespace plugin;

class NoWaterPhysicsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK (inst, Hooked_CWaterLevel_GetWaterLevelNoWaves,
              bool (float, float, float, int, __int64), 0x6EB6B4);
    }

    static bool
    Hooked_CWaterLevel_GetWaterLevelNoWaves (auto &&cb)
    {
        return false;
    }
};

DEFINE_EFFECT (NoWaterPhysicsEffect, "effect_no_water_physics", 0);