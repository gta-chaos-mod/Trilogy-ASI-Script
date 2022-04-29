#include "util/EffectBase.h"
#include "util/GenericUtil.h"

#include <CMenuManager.h>

using namespace plugin;

class PortraitModeEffect : public EffectBase
{
    static inline float currentBoxWidth = 0.0f;
    static inline float boxProgress     = 0.0f;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        currentBoxWidth = 0.0f;
        boxProgress     = 0.0f;

        Events::drawHudEvent.before += DrawTunnelVision;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::drawHudEvent.before -= DrawTunnelVision;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        boxProgress += GenericUtil::CalculateTick (0.001f);
        boxProgress = std::clamp (boxProgress, 0.0f, 1.0f);

        float maxWidth = SCREEN_WIDTH / 2 - SCREEN_COORD (300.0f);

        currentBoxWidth
            = GenericUtil::EaseOutBack (boxProgress, 0.0f, maxWidth);
    }

    static void
    DrawTunnelVision ()
    {
        if (FrontEndMenuManager.m_bMenuActive) return;

        CRect leftRect  = CRect (0.0f, 0.0f, currentBoxWidth, SCREEN_HEIGHT);
        CRect rightRect = CRect (SCREEN_WIDTH - currentBoxWidth, 0.0f,
                                 SCREEN_WIDTH, SCREEN_HEIGHT);

        CSprite2d::DrawRect (leftRect, color::Black);
        CSprite2d::DrawRect (rightRect, color::Black);
    }
};

DEFINE_EFFECT (PortraitModeEffect, "effect_portrait_mode", GROUP_HUD);