#pragma once

#include "util/EffectCrowdControlHandler.h"
#include "util/EffectTwitchHandler.h"
#include "util/EffectDrawHandler.h"
#include "util/EffectSubHandlers.h"
#include "util/RandomHelper.h"

#include <string>
#include <memory>

class EffectBase;

class EffectInstance
{
public:
    using Subhandlers_t
        = EffectSubhandlers<EffectCrowdControlHandler, EffectTwitchHandler>;

private:
    EffectBase *effect;

    std::string overrideName;

    int remaining = 0;
    int duration  = 0;

    bool timerVisible = true;
    bool isRunning    = false;

    nlohmann::json customData = {{"seed", 0}};

    EffectDrawHandler drawHandler;
    Subhandlers_t     subhandlers;

    RandomHelper randomHelper;

public:
    EffectInstance (EffectBase *effect);

    EffectInstance (const EffectInstance &other) = delete;
    EffectInstance (EffectInstance &&other)      = default;

    /// Returns whether other effect can run together with this effect.
    bool IsOtherEffectIncompatible (const EffectInstance &other);

    // Setters
    void
    SetDuration (int duration)
    {
        this->duration = remaining = duration;
    };

    void
    OverrideName (std::string_view name)
    {
        overrideName = name;
    };

    void
    SetTimerVisible (bool timerVisible)
    {
        this->timerVisible = timerVisible;
    }

    bool
    IsRunning () const
    {
        return isRunning;
    };

    bool
    IsShownOnScreen () const
    {
        return GetEffectRemaining () > 0;
    };

    bool
    DoesEffectDrawTimer () const
    {
        return IsRunning () && timerVisible;
    }

    int
    GetEffectDuration () const
    {
        return duration;
    }

    int
    GetEffectRemaining () const
    {
        return remaining;
    }

    nlohmann::json &
    GetCustomData ()
    {
        return this->customData;
    }

    void
    SetSubhandlers (const Subhandlers_t &other)
    {
        this->subhandlers = other;
    }

    template <typename T>
    T &
    GetSubhandler ()
    {
        return subhandlers.Get<T> ();
    }

    void
    SetCustomData (const nlohmann::json &data)
    {
        if (data.contains ("seed"))
            randomHelper.SetSeed (data["seed"]);

        this->customData = data;
    }

    void
    ResetTimer ()
    {
        remaining = duration;
    }

    template <typename T>
    T
    Random (T min, T max, T amplify = 1)
    {
        return randomHelper.Random (min, max, amplify);
    }

    std::string_view GetName () const;

    // Handler functions
    void Start ();
    void End ();
    void Tick ();

    /* Enable/Disable functions */
    void
    Disable ()
    {
        if (isRunning)
        {
            End ();
            isRunning = false;
        }
    };

    void
    Enable ()
    {
        if (!isRunning)
        {
            isRunning = true;
            Start ();
        }
    };

    void
    Draw (int idx, bool inset)
    {
        this->drawHandler.Draw (this, idx, inset);
    }
};
