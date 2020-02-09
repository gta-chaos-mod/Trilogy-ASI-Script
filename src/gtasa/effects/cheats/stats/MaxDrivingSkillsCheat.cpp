#include "MaxDrivingSkillsCheat.h"

MaxDrivingSkillsCheat::MaxDrivingSkillsCheat ()
    : EffectPlaceholder ("cheat_max_driving_skills")
{
}

void
MaxDrivingSkillsCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CStats::SetStatValue (eStats::STAT_DRIVING_SKILL, 1000.0f); // Driving
    CStats::SetStatValue (eStats::STAT_FLYING_SKILL, 1000.0f);  // Flying
    CStats::SetStatValue (eStats::STAT_BIKE_SKILL, 1000.0f);    // Bike
    CStats::SetStatValue (eStats::STAT_CYCLING_SKILL, 1000.0f); // Cycling
}
