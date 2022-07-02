#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CClock.h>

class BackwardsClockEffect : public EffectBase
{
    static inline byte *daysInMonth = reinterpret_cast<byte *> (0x8CCF23);

public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK (inst, Hooked_CClock_Update, void (), 0x53BFBD);
        HOOK (inst, Hooked_CWeather_Update, void (), 0x53BFC2);
    }

    static void
    Hooked_CClock_Update (auto &&cb)
    {
        unsigned char minutesBefore = CClock::ms_nGameClockMinutes;
        unsigned char hoursBefore   = CClock::ms_nGameClockHours;

        unsigned int clockTickBefore = CClock::ms_nLastClockTick;

        cb ();

        unsigned int clockTickAfter = CClock::ms_nLastClockTick;

        if (clockTickBefore >= clockTickAfter) return;

        // Reset for calculation
        CClock::ms_nGameClockMinutes = minutesBefore;
        CClock::ms_nGameClockHours   = hoursBefore;

        CClock::ms_nGameClockMinutes -= 1;
        if (CClock::ms_nGameClockMinutes > UCHAR_MAX / 2)
        {
            CClock::ms_nGameClockMinutes += 60;

            CClock::ms_nGameClockHours -= 1;
            if (CClock::ms_nGameClockHours - 1 > UCHAR_MAX / 2)
            {
                CClock::ms_nGameClockHours += 24;
            }
        }
    }

    // Empty so we don't get flickering weather
    static void
    Hooked_CWeather_Update (auto &&cb)
    {
    }
};

DEFINE_EFFECT (BackwardsClockEffect, "effect_backwards_clock", GROUP_TIME);