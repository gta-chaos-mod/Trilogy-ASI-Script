#include <effects/OneTimeEffect.h>

#include <CStats.h>

class MaxDrivingSkillsEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CStats::SetStatValue (STAT_DRIVING_SKILL, 1000.0f); // Driving
        CStats::SetStatValue (STAT_FLYING_SKILL, 1000.0f);  // Flying
        CStats::SetStatValue (STAT_BIKE_SKILL, 1000.0f);    // Bike
        CStats::SetStatValue (STAT_CYCLING_SKILL, 1000.0f); // Cycling
    }
};

DEFINE_EFFECT (MaxDrivingSkillsEffect, "effect_max_driving_skills", 0);