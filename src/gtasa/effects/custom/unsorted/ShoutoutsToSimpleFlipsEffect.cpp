#include "util/EffectBase.h"
#include "util/Globals.h"
#include "util/hooks/HookMacros.h"

#include <CFont.h>
#include <CText.h>

class ShoutoutsToSimpleFlipsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        Globals::isShoutoutsToSimpleFlipsEffectEnabled = true;

        HOOK_METHOD_ARGS (inst, Hooked_CText_Get, char *(CText *, char *),
                          0x6A0050);

        HOOK_ARGS (inst, Hooked_PrintMoney, char (float, float, char *),
                   0x58F607);

        HOOK_ARGS (inst, Hooked_PrintClockAndAmmo, char (float, float, char *),
                   0x58EC21, 0x58962A);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Globals::isShoutoutsToSimpleFlipsEffectEnabled = false;
    }

    static char *
    Hooked_CText_Get (auto &&cb, CText *text, char *key)
    {
        return (char *) "Shoutouts to SimpleFlips.";
    }

    static char
    Hooked_PrintClockAndAmmo (auto &&cb, float x, float y, char *&text)
    {
        text = (char *) "Shoutouts to SimpleFlips.";

        CFont::SetProportional (true);
        char result = cb ();
        CFont::SetProportional (false);

        return result;
    }

    static char
    Hooked_PrintMoney (auto &&cb, float x, float y, char *&text)
    {
        text = (char *) "$Shoutouts to SimpleFlips.";

        CFont::SetProportional (true);
        char result = cb ();
        CFont::SetProportional (false);

        return result;
    }
};

DEFINE_EFFECT (ShoutoutsToSimpleFlipsEffect, "effect_shoutouts_to_simpleflips",
               0);