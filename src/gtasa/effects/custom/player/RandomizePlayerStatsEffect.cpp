#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

#include <CStats.h>

constexpr float DEFAULT_STAT_MAX_HEALTH = 569.0f;
using stat_list                         = std::initializer_list<eStats>;

template <const float min, const float max, typename Base>
class RandomizePlayerStatsEffect : public Base
{
    std::vector<eStats>                   stats;
    std::vector<std::pair<eStats, float>> currentStats;

public:
    RandomizePlayerStatsEffect (stat_list playerStats) : stats (playerStats) {}

    void
    OnStart (EffectInstance *inst) override
    {
        currentStats.reserve (stats.size ());
        for (auto stat : stats)
        {
            currentStats.emplace_back (stat, CStats::GetStatValue (stat));
        }

        for (const auto &stat : stats)
        {
            if (stat == STAT_MAX_HEALTH)
            {
                float mmin = std::clamp (min, DEFAULT_STAT_MAX_HEALTH, 1000.0f);
                float mmax = std::clamp (max, DEFAULT_STAT_MAX_HEALTH, 1000.0f);
                CStats::SetStatValue (stat, inst->Random (mmin, mmax));

                continue;
            }

            CStats::SetStatValue (stat, inst->Random (min, max));
        }

        GameUtil::RebuildPlayer ();
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        if (std::is_same_v<Base, EffectBase>)
        {
            for (const auto &[stat, value] : currentStats)
            {
                CStats::SetStatValue (stat, value);
            }

            GameUtil::RebuildPlayer ();
        }
    }
};

using RandomizePlayerStats
    = RandomizePlayerStatsEffect<0.0f, 1000.0f, OneTimeEffect>;

using RandomizePlayerStatsTimed
    = RandomizePlayerStatsEffect<0.0f, 1000.0f, EffectBase>;

// clang-format off
DEFINE_EFFECT (RandomizePlayerStats, "effect_randomize_player_stats_all", GROUP_WEAPONS | GROUP_HEALTH, stat_list{STAT_ARMOR, STAT_MAX_HEALTH, STAT_FAT, STAT_STAMINA, STAT_MUSCLE, STAT_DRIVING_SKILL, STAT_FLYING_SKILL, STAT_CYCLING_SKILL, STAT_BIKE_SKILL, STAT_PISTOL_SKILL, STAT_SILENCED_PISTOL_SKILL, STAT_DESERT_EAGLE_SKILL, STAT_SHOTGUN_SKILL, STAT_SAWN_OFF_SHOTGUN_SKILL, STAT_COMBAT_SHOTGUN_SKILL, STAT_MACHINE_PISTOL_SKILL, STAT_SMG_SKILL, STAT_AK_47_SKILL, STAT_M4_SKILL});
DEFINE_EFFECT (RandomizePlayerStatsTimed, "effect_randomize_player_stats_all_timed", GROUP_WEAPONS | GROUP_HEALTH, stat_list{STAT_ARMOR, STAT_MAX_HEALTH, STAT_FAT, STAT_STAMINA, STAT_MUSCLE, STAT_DRIVING_SKILL, STAT_FLYING_SKILL, STAT_CYCLING_SKILL, STAT_BIKE_SKILL, STAT_PISTOL_SKILL, STAT_SILENCED_PISTOL_SKILL, STAT_DESERT_EAGLE_SKILL, STAT_SHOTGUN_SKILL, STAT_SAWN_OFF_SHOTGUN_SKILL, STAT_COMBAT_SHOTGUN_SKILL, STAT_MACHINE_PISTOL_SKILL, STAT_SMG_SKILL, STAT_AK_47_SKILL, STAT_M4_SKILL});
// clang-format on