#pragma once

#include "util/EffectDatabase.h"
#include "util/EffectInstance.h"

#include <string>
#include <type_traits>

enum eEffectGroups : unsigned long long
{
    GROUP_WEATHER            = (1ull << 0),
    GROUP_NPC_SPAWNS         = (1ull << 1),
    GROUP_NPCS_ATTACK        = (1ull << 2),
    GROUP_NPCS_RECRUIT       = (1ull << 3),
    GROUP_HEALTH             = (1ull << 4),
    GROUP_THEME              = (1ull << 5),
    GROUP_TIME               = (1ull << 6),
    GROUP_GAME_SPEED         = (1ull << 7),
    GROUP_AUDIO_PITCH        = (1ull << 8),
    GROUP_VEHICLE_COLOR      = (1ull << 9),
    GROUP_VEHICLE_RARITY     = (1ull << 10),
    GROUP_INVISIBLE_VEHICLES = (1ull << 11),
    GROUP_WANTED             = (1ull << 12),
    GROUP_WEAPONS            = (1ull << 13),
    GROUP_CONTROLS           = (1ull << 14),
    GROUP_GRAVITY            = (1ull << 15),
    GROUP_HUD                = (1ull << 16),
    GROUP_CAMERA             = (1ull << 17),
    GROUP_HANDLING           = (1ull << 18),
    GROUP_FRAMERATE          = (1ull << 19),
    GROUP_SCREEN             = (1ull << 20), // TODO: GROUP_PIXEL_SHADER
    GROUP_PED_BONES          = (1ull << 21),
    GROUP_VISION             = (1ull << 22),
    GROUP_TIMER_SPEED        = (1ull << 23),

    GROUP_MAX_GROUPS = 32
};

class EffectBase
{
    struct EffectMetadata
    {
        std::string                   id;
        std::string                   name;
        float                         durationMultiplier;
        std::bitset<GROUP_MAX_GROUPS> groups;
    } metadata;

    void
    SetMetadata (const EffectMetadata &metadata)
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

        static T effectInstance (args...);
        effectInstance.SetMetadata (metadata);

        EffectDatabase::GetInstance ().RegisterEffect (&effectInstance);
        return effectInstance;
    }

    virtual void OnStart (EffectInstance *instance){};
    virtual void OnEnd (EffectInstance *instance){};
    virtual void OnTick (EffectInstance *instance){};
    virtual void OnProcessScripts (EffectInstance *instance){};

    // Only used for Crowd Control. Return false if the effect cannot be
    // triggered at the moment and Crowd Control needs to send effect later.
    virtual bool
    CanActivate ()
    {
        return true;
    }

    virtual const EffectMetadata &
    GetMetadata ()
    {
        return metadata;
    };

    virtual EffectInstance
    CreateInstance ()
    {
        return EffectInstance (this);
    };
};

#define CONCAT(a, b) CONCAT_INNER (a, b)
#define CONCAT_INNER(a, b) a##b

#define DEFINE_EFFECT(className, effectId, effectTypes, ...)                   \
    auto &CONCAT (className##_inst_, __LINE__)                                 \
        = className::Register<className, __LINE__> (                           \
            {effectId, effectId, 1, effectTypes} __VA_OPT__ (, ) __VA_ARGS__);\
