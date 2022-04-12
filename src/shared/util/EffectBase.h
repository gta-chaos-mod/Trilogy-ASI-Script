#pragma once

#include <type_traits>
#include <string>

#include "EffectDatabase.h"
#include "EffectInstance.h"

class EffectBase
{
    struct EffectMetadata
    {
        std::string id;
        std::string name;
        int         duration;
    } metadata;

    void SetMetadata (const EffectMetadata &metadata)
    {
        this->metadata = metadata;
    }

public:
    template <typename T, int N, typename... Args>
    static T &
    Register (const EffectMetadata &metadata, Args... args)
    {
        static_assert (std::is_base_of_v<EffectBase, T>,
                       "Invalid Effect base class");

        static T sm_Instance (args...);
        sm_Instance.SetMetadata (metadata);
        return sm_Instance;
    }

    virtual void OnTick (EffectInstance *instance){};
    virtual void OnStart (EffectInstance *instance){};
    virtual void OnEnd (EffectInstance *instance){};

    virtual const EffectMetadata& GetMetadata() {
        return metadata;
    };

    virtual EffectInstance
    CreateInstance ()
    {
        return EffectInstance (this);
    };

    EffectBase ()
    {
        EffectDatabase::GetInstance ().RegisterEffect (this);
    }
};

#define CONCAT(a, b) CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a ## b

#define DEFINE_EFFECT(className, effectId, effectName, effectDuration, ...)    \
    auto &CONCAT (className##_inst_, __LINE__)                                 \
        = className::Register<className, __LINE__> (                           \
            {effectId, effectName, effectDuration} __VA_OPT__ (, )             \
                __VA_ARGS__);\
