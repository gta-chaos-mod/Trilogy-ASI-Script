#include "util/EffectBase.h"

#include <CMenuManager.h>

using namespace plugin;

class BlindEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        Events::drawHudEvent.before += DrawBlind;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::drawHudEvent.before -= DrawBlind;
    }

    static void
    DrawBlind ()
    {
        if (FrontEndMenuManager.m_bMenuActive) return;

        CRect rect = CRect (0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
        CSprite2d::DrawRect (rect, color::Black);
    }
};

DEFINE_EFFECT (BlindEffect, "effect_blind", GROUP_HUD);