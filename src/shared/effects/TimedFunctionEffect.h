#include <util/EffectBase.h>

class TimedFunctionEffect : public EffectBase
{
    std::function<void ()> function;
    bool                  *enabledState;

public:
    TimedFunctionEffect (std::function<void ()> function, int address)
        : function (function), enabledState (reinterpret_cast<bool *> (address))
    {
    }

    virtual void
    OnEnd (EffectInstance *instance) override
    {
        if (function && enabledState && *enabledState)
            function ();
    }

    virtual void
    OnTick (EffectInstance *instance) override
    {
        if (enabledState && !*enabledState)
            function ();
    }
};
