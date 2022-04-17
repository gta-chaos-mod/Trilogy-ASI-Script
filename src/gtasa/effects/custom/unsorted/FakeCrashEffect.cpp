#include <util/EffectBase.h>

#include <thread>

#include "CTimer.h"
#include "CMenuManager.h"

class FakeCrashEffect : public EffectBase
{
    bool doneCrashing = false;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        doneCrashing = false;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CTimer::EndUserPause ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (doneCrashing)
        {
            inst->Disable ();
            return;
        }

        if (!FrontEndMenuManager.m_bMenuActive)
        {
            int randomCrashTime = inst->Random (5000, 10000);

            std::thread t (
                [=] ()
                {
                    std::this_thread::sleep_for (
                        std::chrono::milliseconds (randomCrashTime));
                    doneCrashing = true;
                    CTimer::EndUserPause ();
                });
            t.detach ();

            CTimer::StartUserPause ();
        }
    }
};

DEFINE_EFFECT (FakeCrashEffect, "effect_fake_crash", 0);