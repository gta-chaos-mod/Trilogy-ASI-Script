#include "util/EffectBase.h"

#include <CMenuManager.h>

using namespace plugin;

class ScottTheWozEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        Events::drawHudEvent.before += DrawScottTheWozBorder;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::drawHudEvent.before -= DrawScottTheWozBorder;
    }

    static void
    DrawScottTheWozBorder ()
    {
        if (FrontEndMenuManager.m_bMenuActive) return;

        float borderWidth = SCREEN_COORD (15.0f);

        CRect leftRect  = CRect (-1.0f, -1.0f, borderWidth, SCREEN_HEIGHT);
        CRect rightRect = CRect (SCREEN_WIDTH - borderWidth, -1.0f,
                                 SCREEN_WIDTH, SCREEN_HEIGHT);

        CRect topRect    = CRect (-1.0f, -1.0f, SCREEN_WIDTH, borderWidth);
        CRect bottomRect = CRect (-1.0f, SCREEN_HEIGHT - borderWidth,
                                  SCREEN_WIDTH, SCREEN_HEIGHT);

        if (CONFIG ("Drawing.DrawRemainingTimeBar", true))
            topRect.bottom += SCREEN_COORD (30.0f);

        CRGBA borderColor (53, 76, 255);

        CSprite2d::DrawRect (leftRect, borderColor);
        CSprite2d::DrawRect (rightRect, borderColor);
        CSprite2d::DrawRect (topRect, borderColor);
        CSprite2d::DrawRect (bottomRect, borderColor);
    }
};

DEFINE_EFFECT (ScottTheWozEffect, "effect_scott_the_woz", GROUP_HUD);