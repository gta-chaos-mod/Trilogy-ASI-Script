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
template <class... SubHandlers> class EffectSubHandlers
{
    std::tuple<SubHandlers...> handlers;

public:
    EffectSubHandlers (const nlohmann::json &effectData)
    {
        (..., (std::get<SubHandlers> (handlers).Initialise (effectData)));
    }

    EffectSubHandlers () = default;

    bool
    HandleOnQueue () const
    {
        return (... & std::get<SubHandlers> (handlers).HandleOnQueue ());
    }

    bool
    HandleOnAddEffect (EffectBase *effect) const
    {
        return (...
                & std::get<SubHandlers> (handlers).HandleOnAddEffect (effect));
    }

    bool
    HandleOnEffectIncompatibility () const
    {
        return (...
                & std::get<SubHandlers> (handlers)
                      .HandleOnEffectIncompatibility ());
    }

    bool
    HandleOnEffectActivated () const
    {
        return (...
                & std::get<SubHandlers> (handlers).HandleOnEffectActivated ());
    }

    template <typename T>
    T &
    Get ()
    {
        return std::get<T> (handlers);
    }
};
