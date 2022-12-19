#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

#include <CStats.h>

class SkinnyPlayerEffect : public OneTimeEffect
{
public:
    // Will not activate for CC if the player has less than 250/1000 muscle or
    // fat.
    bool
    CanActivate () override
    {
        return CStats::GetStatValue (STAT_FAT) > 250.0f
               || CStats::GetStatValue (STAT_MUSCLE) > 250.0f;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CStats::SetStatValue (STAT_FAT, 0.0f);
        CStats::SetStatValue (STAT_MUSCLE, 0.0f);

        GameUtil::RebuildPlayer ();
    }
};

DEFINE_EFFECT (SkinnyPlayerEffect, "effect_skinny_player", 0);