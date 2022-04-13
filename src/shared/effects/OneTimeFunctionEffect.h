#include <effects/OneTimeEffect.h>

class OneTimeFunctionEffect : public OneTimeEffect
{
    std::vector<std::function<void ()>> functions;

public:
    template <typename... Args>
    OneTimeFunctionEffect (Args... functions) : functions ({functions...})
    {
    }

    virtual void
    OnStart (EffectInstance *instance) override
    {
        for (const auto &function : functions)
            function ();
    }
};
