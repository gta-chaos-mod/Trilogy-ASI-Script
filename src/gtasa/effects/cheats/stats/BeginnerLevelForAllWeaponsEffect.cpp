#include <effects/OneTimeEffect.h>

#include <CStats.h>

class BeginnerLevelForAllWeaponsEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CStats::SetStatValue (STAT_PISTOL_SKILL, 0.0f); // Pistol
        CStats::SetStatValue (STAT_SILENCED_PISTOL_SKILL,
                              0.0f); // Silenced pistol
        CStats::SetStatValue (STAT_DESERT_EAGLE_SKILL,
                              0.0f);                     // Desert eagle
        CStats::SetStatValue (STAT_SHOTGUN_SKILL, 0.0f); // Shotgun
        CStats::SetStatValue (STAT_SAWN_OFF_SHOTGUN_SKILL,
                              0.0f); // Sawn-off shotgun
        CStats::SetStatValue (STAT_COMBAT_SHOTGUN_SKILL,
                              0.0f); // Combat shotgun
        CStats::SetStatValue (STAT_MACHINE_PISTOL_SKILL,
                              0.0f);                   // Machine pistol
        CStats::SetStatValue (STAT_SMG_SKILL, 0.0f);   // SMG
        CStats::SetStatValue (STAT_AK_47_SKILL, 0.0f); // AK47
        CStats::SetStatValue (STAT_M4_SKILL, 0.0f);    // M4
        CStats::SetStatValue (STAT_RIFLE_SKILL, 0.0f); // Rifle
    }
};

DEFINE_EFFECT (BeginnerLevelForAllWeaponsEffect,
               "effect_beginner_level_for_all_weapons", 0);