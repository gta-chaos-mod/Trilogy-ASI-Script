#include "BeginnerLevelForAllWeaponsCheat.h"

BeginnerLevelForAllWeaponsCheat::BeginnerLevelForAllWeaponsCheat ()
    : EffectPlaceholder ("cheat_beginner_level_for_all_weapons")
{
}

void
BeginnerLevelForAllWeaponsCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CStats::SetStatValue (eStats::STAT_PISTOL_SKILL, 0.0f); // Pistol
    CStats::SetStatValue (eStats::STAT_SILENCED_PISTOL_SKILL,
                          0.0f); // Silenced pistol
    CStats::SetStatValue (eStats::STAT_DESERT_EAGLE_SKILL,
                          0.0f);                             // Desert eagle
    CStats::SetStatValue (eStats::STAT_SHOTGUN_SKILL, 0.0f); // Shotgun
    CStats::SetStatValue (eStats::STAT_SAWN_OFF_SHOTGUN_SKILL,
                          0.0f); // Sawn-off shotgun
    CStats::SetStatValue (eStats::STAT_COMBAT_SHOTGUN_SKILL,
                          0.0f); // Combat shotgun
    CStats::SetStatValue (eStats::STAT_MACHINE_PISTOL_SKILL,
                          0.0f);                           // Machine pistol
    CStats::SetStatValue (eStats::STAT_SMG_SKILL, 0.0f);   // SMG
    CStats::SetStatValue (eStats::STAT_AK_47_SKILL, 0.0f); // AK47
    CStats::SetStatValue (eStats::STAT_M4_SKILL, 0.0f);    // M4
    CStats::SetStatValue (eStats::STAT_RIFLE_SKILL, 0.0f); // Rifle
}
