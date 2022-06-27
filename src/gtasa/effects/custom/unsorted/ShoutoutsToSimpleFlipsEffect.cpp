#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CText.h>

class ShoutoutsToSimpleFlipsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD_ARGS (inst, Hooked_CText_Get, char *(CText *, char *),
                          0x6A0050);
    }

    static char *
    Hooked_CText_Get (auto &&cb, CText *text, char *key)
    {
        return (char *) "Shoutouts to SimpleFlips.";
    }
};

DEFINE_EFFECT (ShoutoutsToSimpleFlipsEffect, "effect_shoutouts_to_simpleflips",
               0);