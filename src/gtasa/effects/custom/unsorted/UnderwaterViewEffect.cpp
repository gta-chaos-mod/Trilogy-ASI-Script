#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CWeather.h>

using namespace plugin;

class UnderwaterViewEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        // CClouds::Render
        HOOK (inst, Hooked_Empty, void (), 0x53DFA0, 0x53DCA2);

        // CClouds::RenderBottomFromHeight
        HOOK (inst, Hooked_Empty, void (), 0x53E121);

        // CClouds::VolumetricCloudsRender
        HOOK (inst, Hooked_Empty, void (), 0x53E1B4);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CWeather::UnderWaterness = 1.0f;
    }

    static void
    Hooked_Empty (auto &&cb)
    {
    }
};

DEFINE_EFFECT (UnderwaterViewEffect, "effect_underwater_view", 0);