#pragma once

#include "util/EffectCleanupHandler.h"
#include "util/EffectCrowdControlHandler.h"
#include "util/EffectDrawHandler.h"
#include "util/EffectSubHandlers.h"
#include "util/EffectTwitchHandler.h"
#include "util/RandomHelper.h"

#include <memory>
#include <string>

class EffectBase;

class EffectInstance
{
public:
    using SubHandlers_t
        = EffectSubHandlers<EffectCrowdControlHandler, EffectTwitchHandler>;

private:
    EffectBase *effect;

    std::string overrideName;
    std::string subtext;

    int remaining = 0;
    int duration  = 0;

    bool timerVisible = true;
    bool isRunning    = false;

    nlohmann::json customData = {{"seed", 0}};

    EffectDrawHandler drawHandler;
    SubHandlers_t     subHandlers;

    RandomHelper         randomHelper;
    EffectCleanupHandler cleanupHandler;

public:
    EffectInstance (EffectBase *effect);

    EffectInstance (const EffectInstance &other)       = delete;
    EffectInstance (EffectInstance &&other)            = default;
    EffectInstance &operator= (EffectInstance &&other) = default;

    /// Returns whether other effect can run together with this effect.
    bool IsOtherEffectIncompatible (const EffectInstance &other);

    // Setters
    void
    SetDuration (int duration)
    {
        this->duration = remaining = duration;
    }

    void
    OverrideName (std::string_view name)
    {
        overrideName = name;
    }

    void
    SetSubtext (std::string_view subtext)
    {
        this->subtext = subtext;
    }

    bool
    HasSubtext ()
    {
        return subtext.length () != 0;
    }

    std::string_view
    GetSubtext ()
    {
        return subtext;
    }

    void
    SetTimerVisible (bool timerVisible)
    {
        this->timerVisible = timerVisible;
    }

    bool
    IsRunning () const
    {
        return isRunning;
    }

    bool
    IsShownOnScreen () const
    {
        return GetEffectRemaining () > 0;
    }

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
    SetSubHandlers (const SubHandlers_t &other)
    {
        this->subHandlers = other;
    }

    template <typename T>
    T &
    GetSubhandler ()
    {
        return subHandlers.Get<T> ();
    }

    auto &
    GetCleanupHandler ()
    {
        return cleanupHandler;
    }

    void
    SetCustomData (const nlohmann::json &data)
    {
        if (data.contains ("seed")) randomHelper.SetSeed (data["seed"]);

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

    std::mt19937
    GetRNG ()
    {
        return randomHelper.GetRNG ();
    }

    std::string_view GetName () const;

    // Handler functions
    void Start ();
    void End ();
    void Tick ();
    void ProcessScripts ();

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

    template <typename T>
    void
    WriteMemory (uintptr_t addr, const T &value)
    {
        T original = injector::ReadMemory<T> (addr);
        injector::WriteMemory (addr, value);

        cleanupHandler.AddFunction (
            [addr, original] { injector::WriteMemory (addr, original); });
    }
};
