#include "util/EffectBase.h"

class AllTaxisHaveNitrousEffect : public EffectBase
{
    static inline bool overrideAllTaxisHaveNitrous = true;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        inst->WriteMemory<bool *> (0x6B1993 + 1, &overrideAllTaxisHaveNitrous);
    }
};

DEFINE_EFFECT (AllTaxisHaveNitrousEffect, "effect_all_taxis_have_nitro", 0);