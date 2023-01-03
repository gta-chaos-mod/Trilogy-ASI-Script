# Foreword

This contributing document is still WIP.

If you have any questions please feel free to open a new post in the Discussions tab.

**Ninja (<img src="https://i.imgur.com/z8Yty1X.png" title="Ninja Fortnite" alt="Not Fortnite" width="20"/>) is highly recommended as a build system.**

# Basic Style-Guide

-   Effects are headerless, meaning all you need is a `.cpp` file in the correct subfolder
-   Includes are grouped and sorted according to their categories, which means these rules need to be followed:
    -   Includes from the Chaos Mod (`util/` and such) are to be written with quotation marks (`""`) but still use their full path, even if the corresponding file is in the same folder
    -   Includes from system headers are to be written with angled brackets (`<>`)
    -   Includes from plugin-sdk are to be written with angled brackets (`<>`)
    -   Uses of namespaces should be done after the plugin-sdk includes
-   Effect classes should **always** end with `Effect`
    -   **Correct:** `MyVeryCoolEffect`
    -   **Incorrect:** `TeleportPlayerAway`

# Effect files

There are many different ways of doing effects.

Currently active effects will disable themselves if a new effect is being activated that has the same type.

To find all available types please check the `eEffectGroups` enum in `src/shared/util/EffectBase.h`

## One Time Effect

A one time effect does what the name implies:  
_It only runs once._

```cpp
#include "effects/OneTimeEffect.h"

class MyVeryCoolEffect : public OneTimeEffect
{
public:
    // Optional
    bool
    CanActivate() override
    {
        // This is mostly used for Crowd Control support.
        // By default this will return true, so you don't need to override it.
        // Return false if the effect can't be activated right now.
        // Example: The player has no weapons so RemoveAllWeapons wouldn't do anything.
        return true;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        // Code that runs when the effect starts
        // You want to always reset any variables you have in here
    }
};

// Register your effect
// DEFINE_EFFECT (CLASS_NAME, "effect_<name_here>", TYPES | WHICH | CAN | BE | COMBINED);
DEFINE_EFFECT (MyVeryCoolEffect, "effect_very_cool", 0);
```

## Timed Effect

A timed effect runs every game tick and / or script tick.

```cpp
#include "util/EffectBase.h"

class MyVeryCoolEffect : public EffectBase
{
public:
    // Optional
    bool
    CanActivate() override
    {
        // This is mostly used for Crowd Control support.
        // By default this will return true, so you don't need to override it.
        // Return false if the effect can't be activated right now.
        // Example: The player has no weapons so RemoveAllWeapons wouldn't do anything.
        return true;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        // Code that runs when the effect starts
        // You want to always reset any variables you have in here
    }

    // Optional
    void
    OnEnd (EffectInstance *inst) override
    {
        // Code that runs when the effect ends
    }

    // Optional
    void
    OnTick (EffectInstance *inst) override
    {
        // Code that runs every game tick
    }

    // Optional
    void
    OnProcessScripts(EffectInstance *inst) override
    {
        // Code that runs every time the scripts are processed
        // This is necessary for things like modifying the player controls / CPad
    }
};

DEFINE_EFFECT (MyVeryCoolEffect, "effect_very_cool", 0);
```

## Disabling effects for missions

Sometimes you want to disable effects during a mission.

For this, there is a wrapper class available.

The usage is as follows:

```cpp
#include "effects/DisabledForMissionEffect.h"
#include "util/EffectBase.h"

class MyVeryCoolEffect : public EffectBase
{
    // All the effect code
};

using RegisterMyVeryCoolEffect
    = DisabledForMissionEffect<MyVeryCoolEffect>;

DEFINE_EFFECT (RegisterMyVeryCoolEffect,
               "effect_very_cool",
               0);
```

## Helpful functions and methods

These are some helpful methods you might want to use in your effects.

```cpp
void
OnStart (EffectInstance *inst) override
{
    // Sometimes you want to do a One Time Effect but need to wait for it to be ready.
    // In this case you need to use EffectBase instead of OneTimeEffect as a base.
    // To have the effect show on the right side of the screen, call the following method in the OnStart method:
    inst->SetIsOneTimeEffect ();

    // Sets the duration of this effect instance.
    // This will also reset the remaining time.
    inst->SetDuration(1000 * 10);

    // Overrides effect name that is shown in the history
    // on the right side of the screen
    inst->OverrideName("Lorem ipsum");

    // If this is a timed effect, shows or hides the timer.
    // This can be useful if you want to have an effect that can
    // re-engage at a later point.
    inst->SetTimerVisible(false);

    // Get's custom data that was sent from the Chaos Mod UI
    // or another provider.
    //
    // Currently there is no easy way of adding custom data
    // to effects in the Chaos Mod UI.
    // However, it is also generally not necessary.
    int vehicleID = inst->GetCustomData().value("vehicleID", 411);

    // Useful in getting random values with the help of the
    // seeded random instance.
    //
    // This is deterministic based on the seed that is being sent from
    // the Chaos Mod UI or another provider.
    int randomID = inst->Random(5, 20);

    // Resets the remaining time to the duration.
    // This can be useful when an effect has to wait for a condition
    // to be met before it can activate.
    //
    // Example: Waiting for the player to be safe before teleporting them.
    inst->ResetTimer();

    // Disables the effect.
    // Should be used in combination with "ResetTimer" to disable an
    // effect that has to wait for a condition to be met.
    inst->Disable();

    // Writes data to memory and will add it to the internal
    // cleanup handler so it will get reset once the effect ends.
    inst->WriteMemory<byte>(0x420ABC, 69);
}
```

## Hooks

WIP

IDA and a database for GTA:SA is recommended.

For now, please refer to effects that already utilize hooks.
