#include <util/EffectBase.h>

using namespace plugin;

class NoWaterPhysicsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        // TODO: Only hook relevant water level events so we can still hear
        // weird audio
        injector::MakeCALL (0x6EB6B4, Hooked_CWaterLevel_GetWaterLevelNoWaves);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        // Revert
        injector::MakeCALL (0x6EB6B4,
                            0x6E8580); // CWaterLevel::GetWaterLevelNoWaves
    }

    static bool
    Hooked_CWaterLevel_GetWaterLevelNoWaves (float x, float y, float z, int a4,
                                             __int64 a5)
    {
        return 0;
    }
};

DEFINE_EFFECT (NoWaterPhysicsEffect, "effect_no_water_physics", 0);