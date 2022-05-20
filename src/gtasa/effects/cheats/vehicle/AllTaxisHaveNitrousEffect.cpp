#include "util/EffectBase.h"

class AllTaxisHaveNitrousEffect : public EffectBase
{
    static inline bool overrideAllTaxisHaveNitrous = true;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        injector::WriteMemory<bool *> (0x6B1993 + 1,
                                       &overrideAllTaxisHaveNitrous);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        bool *originalAllTaxisHaveNitrous = reinterpret_cast<bool *> (0x96918B);
        injector::WriteMemory<bool *> (0x6B1993 + 1,
                                       originalAllTaxisHaveNitrous);
    }
};

DEFINE_EFFECT (AllTaxisHaveNitrousEffect, "effect_all_taxis_have_nitro", 0);