#pragma once

#include <tuple>

class EffectBase;

// Subhandler that always returns true
class EffectSubhandler
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
template <class... Subhandlers> class EffectSubhandlers
{
    std::tuple<Subhandlers...> handlers;

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
    EffectSubhandlers (const nlohmann::json &effectData)
    {
        (..., (std::get<Subhandlers> (handlers).Initialise (effectData)));
    }

    EffectSubhandlers () = default;

    bool
    HandleOnQueue () const
    {
        SpecialBool ret;
        (..., (ret = std::get<Subhandlers> (handlers).HandleOnQueue ()));

        return ret;
    }

    bool
    HandleOnAddEffect (EffectBase *effect) const
    {
        SpecialBool ret;
        (...,
         (ret = std::get<Subhandlers> (handlers).HandleOnAddEffect (effect)));

        return ret;
    }

    bool
    HandleOnEffectIncompatibility () const
    {
        SpecialBool ret;
        (...,
         (ret
          = std::get<Subhandlers> (handlers).HandleOnEffectIncompatibility ()));

        return ret;
    }

    bool
    HandleOnEffectActivated () const
    {
        SpecialBool ret;
        (...,
         (ret = std::get<Subhandlers> (handlers).HandleOnEffectActivated ()));

        return ret;
    }

    template <typename T>
    T &
    Get ()
    {
        return std::get<T> (handlers);
    }
};
