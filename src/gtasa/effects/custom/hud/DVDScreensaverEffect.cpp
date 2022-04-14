#include <util/EffectBase.h>
#include <util/GenericUtil.h>

using namespace plugin;

class DVDScreensaverEffect : public EffectBase
{
    static inline float x          = 0.0f;
    static inline float y          = 0.0f;
    bool                goingRight = false;
    bool                goingDown  = false;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        x          = inst->Random (0.0f, SCREEN_WIDTH - SCREEN_COORD (400.0f));
        y          = inst->Random (0.0f, SCREEN_WIDTH - SCREEN_COORD (400.0f));
        goingRight = false;
        goingDown  = false;

        Events::drawHudEvent.before += DrawScreensaver;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::drawHudEvent.before -= DrawScreensaver;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (goingRight)
        {
            x += GenericUtil::CalculateTick (0.2f);
            if (SCREEN_COORD (x) >= SCREEN_WIDTH - SCREEN_COORD (400.0f))
            {
                goingRight = false;
            }
        }
        else
        {
            x -= GenericUtil::CalculateTick (0.2f);
            if (x < 0.0f)
            {
                goingRight = true;
            }
        }

        if (goingDown)
        {
            y += GenericUtil::CalculateTick (0.2f);
            if (SCREEN_COORD (y) >= SCREEN_HEIGHT - SCREEN_COORD (400.0f))
            {
                goingDown = false;
            }
        }
        else
        {
            y -= GenericUtil::CalculateTick (0.2f);
            if (y < 0.0f)
            {
                goingDown = true;
            }
        }
    }

    static std::pair<float, float>
    CalculateStartingXY (int boxNumber)
    {
        switch (boxNumber)
        {
        case 0:
        case 1:
        default:
        {
            return std::make_pair (0.0f, 0.0f);
        }
        case 2:
        {
            return std::make_pair (SCREEN_COORD (x) + SCREEN_COORD (400.0f),
                                   SCREEN_COORD (y));
        }
        case 3:
        {
            return std::make_pair (SCREEN_COORD (x),
                                   SCREEN_COORD (y) + SCREEN_COORD (400.0f));
        }
        }
    }

    static std::pair<float, float>
    CalculateWidthHeight (int boxNumber)
    {
        switch (boxNumber)
        {
        case 0:
        default:
        {
            return std::make_pair (SCREEN_WIDTH, SCREEN_COORD (y));
        }
        case 1:
        {
            return std::make_pair (SCREEN_COORD (x), SCREEN_HEIGHT);
        }
        case 2:
        case 3:
        {
            return std::make_pair (SCREEN_WIDTH, SCREEN_HEIGHT);
        }
        }
    }

    static void
    DrawScreensaver ()
    {
        if (FrontEndMenuManager.m_bMenuActive)
        {
            return;
        }

        for (int i = 0; i < 4; i++)
        {
            std::pair<float, float> start = CalculateStartingXY (i);
            std::pair<float, float> end   = CalculateWidthHeight (i);

            CRect rect
                = CRect (start.first, start.second, end.first, end.second);
            CSprite2d::DrawRect (rect, color::Black);
        }
    }
};

DEFINE_EFFECT (DVDScreensaverEffect, "effect_dvd_screensaver", GROUP_HUD);