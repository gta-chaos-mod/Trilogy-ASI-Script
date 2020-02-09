#pragma once

#include "util/EffectBase.h"
#include "util/RandomHelper.h"

class DVDScreensaverEffect : public EffectBase
{
private:
    static bool goingDown;
    static bool goingRight;

    static float x;
    static float y;

public:
    DVDScreensaverEffect ();

    EffectBase *SetEffectDuration (int duration) override;

    void Enable () override;
    void Disable () override;

    void HandleTick () override;

    static std::pair<float, float> CalculateStartingXY (int boxNumber);
    static std::pair<float, float> CalculateWidthHeight (int boxNumber);
    static void                    DrawScreensaver ();
};
