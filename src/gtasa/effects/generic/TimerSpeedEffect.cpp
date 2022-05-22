#include "util/EffectBase.h"
#include "util/Globals.h"

template <float speed> class TimerSpeedEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        Globals::effectTimerSpeed = speed;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Globals::effectTimerSpeed = 1.0f;
    }
};

using HalfTimerSpeedEffect = TimerSpeedEffect<0.5f>;
DEFINE_EFFECT (HalfTimerSpeedEffect, "effect_half_timer_speed", GROUP_TIMER_SPEED);

using DoubleTimerSpeedEffect = TimerSpeedEffect<2.0f>;
DEFINE_EFFECT (DoubleTimerSpeedEffect, "effect_double_timer_speed", GROUP_TIMER_SPEED);

using QuintupleTimerSpeedEffect = TimerSpeedEffect<5.0f>;
DEFINE_EFFECT (QuintupleTimerSpeedEffect, "effect_quintuple_timer_speed", GROUP_TIMER_SPEED);