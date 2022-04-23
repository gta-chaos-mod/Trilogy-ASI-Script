#include <util/EffectBase.h>

#include <CMenuManager.h>

using namespace plugin;

class TunnelVisionEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        Events::drawHudEvent.before += DrawTunnelVision;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::drawHudEvent.before -= DrawTunnelVision;
    }

    static void
    DrawTunnelVision ()
    {
        if (FrontEndMenuManager.m_bMenuActive) return;

        CRect rect = CRect (0.0f, 0.0f, SCREEN_WIDTH,
                            SCREEN_COORD_CENTER_Y - SCREEN_COORD (200.0f));
        CSprite2d::DrawRect (rect, color::Black);

        rect = CRect (0.0f, SCREEN_COORD_CENTER_Y + SCREEN_COORD (200.0f),
                      SCREEN_WIDTH, SCREEN_HEIGHT);
        CSprite2d::DrawRect (rect, color::Black);

        rect = CRect (0.0f, 0.0f, SCREEN_COORD_CENTER_X - SCREEN_COORD (200.0f),
                      SCREEN_HEIGHT);
        CSprite2d::DrawRect (rect, color::Black);

        rect = CRect (SCREEN_COORD_CENTER_X + SCREEN_COORD (200.0f), 0.0f,
                      SCREEN_WIDTH, SCREEN_HEIGHT);
        CSprite2d::DrawRect (rect, color::Black);
    }
};

DEFINE_EFFECT (TunnelVisionEffect, "effect_tunnel_vision", GROUP_HUD);