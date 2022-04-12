#pragma once

#include "util/EffectDrawHandler.h"

#include <string>
#include <memory>

class EffectBase;

class EffectInstance
{
    EffectBase *effect;

    std::string overrideName;
    std::string twitchVoter;

    int crowdControlID = -1;

    int remaining = 0;
    int duration  = 0;

    bool timerVisible = true;
    bool isRunning = false;

    std::shared_ptr<void *> customData;

    EffectDrawHandler drawHandler;

public:
    EffectInstance (EffectBase *effect);

    EffectInstance (const EffectInstance &other) = delete;
    EffectInstance (EffectInstance &&other)      = default;

    // Setters
    void
    SetDuration (int duration)
    {
        this->duration = remaining = duration;
    };

    void
    SetTwitchVoter (std::string_view voter)
    {
        twitchVoter = voter;
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

    // Getters
    bool
    HasTwitchVoter () const
    {
        return twitchVoter != "";
    }

    std::string_view
    GetTwitchVoter () const
    {
        return twitchVoter;
    }

    bool
    IsRunning () const
    {
        return isRunning;
    };

    bool
    DoesEffectDrawTimer () const
    {
        return IsRunning () && timerVisible;
    }

    int GetEffectDuration () const
    {
        return duration;
    }
    
    int GetEffectRemaining () const
    {
        return remaining;
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
        if (!isRunning) {
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
