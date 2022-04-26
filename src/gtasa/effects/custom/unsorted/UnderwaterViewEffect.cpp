#include "util/EffectBase.h"

#include <CWeather.h>

using namespace plugin;

class UnderwaterViewEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        injector::MakeCALL (0x53DFA0, Hooked_CClouds_Render);
        injector::MakeCALL (0x53DCA2, Hooked_CClouds_Render);

        injector::MakeCALL (0x53E121, Hooked_CClouds_RenderBottomFromHeight);

        injector::MakeCALL (0x53E1B4, Hooked_CClouds_VolumetricCloudsRender);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        injector::MakeCALL (0x53DFA0, 0x713950);
        injector::MakeCALL (0x53DCA2, 0x713950);

        injector::MakeCALL (0x53E121, 0x7154B0);

        injector::MakeCALL (0x53E1B4, 0x716380);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CWeather::UnderWaterness = 1.0f;
    }

    static void
    Hooked_CClouds_Render ()
    {
    }

    static void
    Hooked_CClouds_RenderBottomFromHeight ()
    {
    }

    static void
    Hooked_CClouds_VolumetricCloudsRender ()
    {
    }
};

DEFINE_EFFECT (UnderwaterViewEffect, "effect_underwater_view", 0);