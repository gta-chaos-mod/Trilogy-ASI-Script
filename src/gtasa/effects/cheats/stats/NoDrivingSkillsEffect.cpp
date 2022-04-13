#include <effects/OneTimeEffect.h>

#include "CStats.h"

class NoDrivingSkillsEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CStats::SetStatValue (eStats::STAT_DRIVING_SKILL, 0.0f); // Driving
        CStats::SetStatValue (eStats::STAT_FLYING_SKILL, 0.0f);  // Flying
        CStats::SetStatValue (eStats::STAT_BIKE_SKILL, 0.0f);    // Bike
        CStats::SetStatValue (eStats::STAT_CYCLING_SKILL, 0.0f); // Cycling
    }
};

DEFINE_EFFECT (NoDrivingSkillsEffect, "effect_no_driving_skills", 0);