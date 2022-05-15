#include "effects/OneTimeEffect.h"

#include <thread>

class FakeCrashEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        int randomCrashTime = inst->Random (5000, 10000);

        std::this_thread::sleep_for (
            std::chrono::milliseconds (randomCrashTime));

        inst->OverrideName (
            inst->GetCustomData ().value ("realEffectName", "Fake Crash"));
    }
};

DEFINE_EFFECT (FakeCrashEffect, "effect_fake_crash", 0);