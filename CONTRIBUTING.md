# Foreword
This contributing document is still WIP.

If you have any questions please feel free to open a new post in the Discussions tab.

# Basic Style-Guide
- Effects are headerless, meaning all you need is a `.cpp` file in the correct subfolder
- Includes are grouped and sorted according to their categories, which means these rules need to be followed:
    - Includes from the Chaos Mod (`util/` and such) are to be written with quotation marks (`""`) but still use their full path, even if the corresponding file is in the same folder
    - Includes from system headers are to be written with angled brackets (`<>`)
    - Includes from plugin-sdk are to be written with angled brackets (`<>`)
    - Uses of namespaces should be done after the plugin-sdk includes
- Effect classes should **always** end with `Effect`
    - **Correct:** `MyVeryCoolEffect`
    - **Incorrect:** `TeleportPlayerAway`

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
    void
    OnStart (EffectInstance *inst) override
    {
        // Code that runs when the effect starts
        // You want to always reset any variables you have in here
    }
};

// Register your effect
// The syntax is:
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
    void
    OnStart (EffectInstance *inst) override
    {
        // Code that runs when the effect starts
        // You want to always reset any variables you have in here
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        // Code that runs when the effect ends
    }

    void
    OnTick (EffectInstance *inst) override
    {
        // Code that runs every game tick
    }

    void OnProcessScripts(EffectInstance *inst) override
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