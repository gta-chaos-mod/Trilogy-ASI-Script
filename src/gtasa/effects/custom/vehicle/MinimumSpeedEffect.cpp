#include "util/EffectBase.h"
#include "util/GenericUtil.h"

#include <CAudioEngine.h>

using namespace plugin;

class MinimumSpeedEffect : public EffectBase
{
    static inline const float SPEED_THRESHOLD = 75.0f;

    static inline CVehicle *currentVehicle;
    static inline int       timeLeft     = 1000 * 10;
    static inline float     currentSpeed = 0.0f;

    int beepCooldown = 0;

public:
    bool
    CanActivate () override
    {
        return FindPlayerVehicle (-1, false);
    }

    void
    OnStart (EffectInstance *inst) override
    {
        currentVehicle = FindPlayerVehicle (-1, false);
        if (currentVehicle)
        {
            currentSpeed = currentVehicle->m_vecMoveSpeed.Magnitude ();
        }

        timeLeft     = 1000 * 10;
        beepCooldown = 0;

        Events::drawAfterFadeEvent += OnDraw;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::drawAfterFadeEvent -= OnDraw;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (!EnsureVehicle ()) return;

        currentSpeed = currentVehicle->m_vecMoveSpeed.Magnitude () * 175.0f;

        int tick = (int) GenericUtil::CalculateTick ();

        beepCooldown -= tick;
        beepCooldown = std::clamp (beepCooldown, 0, 500);

        if (currentSpeed >= SPEED_THRESHOLD)
            timeLeft += tick;
        else
        {
            timeLeft -= tick;
            DoBeepIfNecessary ();
        }

        timeLeft = std::clamp (timeLeft, 0, 1000 * 10);

        if (timeLeft == 0)
        {
            BlowUpVehicle (currentVehicle);

            timeLeft = 1000 * 10;
        }
    }

    bool
    EnsureVehicle ()
    {
        currentVehicle = nullptr;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (IsVehiclePointerValid (currentVehicle) && vehicle != currentVehicle)
        {
            BlowUpVehicle (currentVehicle);
            return false;
        }

        if (IsVehiclePointerValid (vehicle) && vehicle->CanBeDriven ()
            && vehicle->m_nStatus != STATUS_WRECKED)
        {
            currentVehicle = vehicle;
        }

        return currentVehicle != nullptr;
    }

    void
    BlowUpVehicle (CVehicle *vehicle)
    {
        if (IsVehiclePointerValid (vehicle) && vehicle->CanBeDriven ()
            && vehicle->m_nStatus != STATUS_WRECKED)
        {
            vehicle->m_nPhysicalFlags.bExplosionProof = false;
            vehicle->BlowUpCar (NULL, false);
        }
    }

    void
    DoBeepIfNecessary ()
    {
        // TODO: Find beep sound
        // AudioEngine.ReportFrontendAudioEvent (0x1455, 0.0f, 1.0f);
    }

    static void
    OnDraw ()
    {
        if (GenericUtil::IsMenuActive () || !currentVehicle) return;

        // Calculate between 0.0f and 1.0f
        float timeLeftWidth = (float) timeLeft / (1000 * 10.0f);

        CRGBA rectColor = color::ForestGreen;
        if (timeLeft < 7000) rectColor = color::Orange;
        if (timeLeft < 4000) rectColor = color::Red;

        float x      = 70.0f;
        float y      = 300.0f;
        float width  = 200.0f;
        float height = 30.0f;

        float left   = SCREEN_MULTIPLIER (x);
        float top    = SCREEN_COORD_BOTTOM (y);
        float right  = SCREEN_MULTIPLIER (x + width);
        float bottom = SCREEN_COORD_BOTTOM (y - height);

        float rightFilled = SCREEN_MULTIPLIER (x + width * timeLeftWidth);

        CRect fullWidth   = CRect (left, top, right, bottom);
        CRect filledWidth = CRect (left, top, rightFilled, bottom);

        CSprite2d::DrawRect (fullWidth, color::DarkGray);
        CSprite2d::DrawRect (filledWidth, rectColor);

        char speedBuffer[64];
        sprintf_s (speedBuffer, "%.0f", currentSpeed);

        CRGBA speedColor
            = currentSpeed > SPEED_THRESHOLD ? color::White : color::Orange;

        gamefont::PrintUnscaled (speedBuffer,
                                 left + (SCREEN_MULTIPLIER (width) / 2),
                                 top + SCREEN_MULTIPLIER (2.0f), FONT_DEFAULT,
                                 SCREEN_MULTIPLIER (0.8f),
                                 SCREEN_MULTIPLIER (0.8f), speedColor,
                                 gamefont::AlignCenter, 1, color::Black, true,
                                 9999.0F, false);
    }
};

DEFINE_EFFECT (MinimumSpeedEffect, "effect_minimum_speed", 0);