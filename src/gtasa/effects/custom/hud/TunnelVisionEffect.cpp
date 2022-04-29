#include "util/EffectBase.h"
#include "util/GenericUtil.h"

#include <CMenuManager.h>

using namespace plugin;

class TunnelVisionEffect : public EffectBase
{
    static inline float currentBoxWidth  = 0.0f;
    static inline float currentBoxHeight = 0.0f;
    static inline float boxProgress      = 0.0f;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        currentBoxWidth  = 0.0f;
        currentBoxHeight = 0.0f;
        boxProgress      = 0.0f;

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

        float maxWidth  = SCREEN_WIDTH / 2 - SCREEN_COORD (200.0f);
        float maxHeight = SCREEN_HEIGHT / 2 - SCREEN_COORD (200.0f);

        currentBoxWidth
            = GenericUtil::EaseOutBack (boxProgress, 0.0f, maxWidth);
        currentBoxHeight
            = GenericUtil::EaseOutBack (boxProgress, 0.0f, maxHeight);
    }

    static void
    DrawTunnelVision ()
    {
        if (FrontEndMenuManager.m_bMenuActive) return;

        CRect leftRect  = CRect (0.0f, 0.0f, currentBoxWidth, SCREEN_HEIGHT);
        CRect rightRect = CRect (SCREEN_WIDTH - currentBoxWidth, 0.0f,
                                 SCREEN_WIDTH, SCREEN_HEIGHT);

        CRect topRect    = CRect (0.0f, 0.0f, SCREEN_WIDTH, currentBoxHeight);
        CRect bottomRect = CRect (0.0f, SCREEN_HEIGHT - currentBoxHeight,
                                  SCREEN_WIDTH, SCREEN_HEIGHT);

        CSprite2d::DrawRect (leftRect, color::Black);
        CSprite2d::DrawRect (rightRect, color::Black);
        CSprite2d::DrawRect (topRect, color::Black);
        CSprite2d::DrawRect (bottomRect, color::Black);
    }
};

DEFINE_EFFECT (TunnelVisionEffect, "effect_tunnel_vision", GROUP_HUD);