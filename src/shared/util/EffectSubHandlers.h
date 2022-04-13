#pragma once

#include <tuple>

class EffectBase;

// Subhandler that always returns true
class EffectSubHandler
{
public:
    bool
    HandleOnQueue () const
    {
        return true;
    }
    bool
    HandleOnAddEffect (EffectBase *effect) const
    {
        return true;
    }
    bool
    HandleOnEffectIncompatibility () const
    {
        return true;
    }
    bool
    HandleOnEffectActivated () const
    {
        return true;
    }
};

// Class to manage multiple subhandlers.
template <class... SubHandler> class EffectSubHandlers
{
    std::tuple<SubHandler...> handlers;

    class SpecialBool
    {
        bool value = false;

    public:
        void
        operator= (bool other)
        {
            if (!value)
                value = other;
        }

        operator bool () { return value; }
    };

public:
    EffectSubHandlers (const nlohmann::json &effectData)
    {
        (..., (std::get<SubHandler> (handlers).Initialise (effectData)));
    }

    EffectSubHandlers () = default;

    bool
    HandleOnQueue () const
    {
        SpecialBool ret;
        (..., (ret = std::get<SubHandler> (handlers).HandleOnQueue ()));

        return ret;
    }

    bool
    HandleOnAddEffect (EffectBase *effect) const
    {
        SpecialBool ret;
        (...,
         (ret = std::get<SubHandler> (handlers).HandleOnAddEffect (effect)));

        return ret;
    }

    bool
    HandleOnEffectIncompatibility () const
    {
        SpecialBool ret;
        (...,
         (ret
          = std::get<SubHandler> (handlers).HandleOnEffectIncompatibility ()));

        return ret;
    }

    bool
    HandleOnEffectActivated () const
    {
        SpecialBool ret;
        (...,
         (ret = std::get<SubHandler> (handlers).HandleOnEffectActivated ()));

        return ret;
    }

    template <typename T>
    T &
    Get ()
    {
        return std::get<T> (handlers);
    }
};
