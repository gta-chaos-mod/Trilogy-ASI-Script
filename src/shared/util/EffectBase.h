#pragma once

#include <type_traits>
#include <string>

#include "EffectDatabase.h"
#include "EffectInstance.h"

class EffectBase
{
protected:
    struct EffectMetadata
    {
        std::string id;
        std::string name;
        int         duration;
    } metadata;

public:
    
    template <typename T>
    static T &
    Register ()
    {
        static_assert (std::is_base_of_v<EffectBase, T>,
                       "Invalid Effect base class");

        static T sm_Instance;
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

    EffectBase (EffectMetadata metadata) : metadata (metadata)
    {
        EffectDatabase::GetInstance ().RegisterEffect (this);
    }
};


#define DEFINE_EFFECT(className, effectId, effectName, effectDuration)         \
    className () : EffectBase ({effectId, effectName, effectDuration}) {}      \
    inline static auto &sm_Instance = EffectBase::Register<className> ();
