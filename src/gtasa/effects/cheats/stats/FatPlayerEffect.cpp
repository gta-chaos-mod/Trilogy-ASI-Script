#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

#include <CStats.h>

class FatPlayerEffect : public OneTimeEffect
{
public:
    // Will not activate for CC if the player has more than 750/1000 fat.
    bool
    CanActivate () override
    {
        return CStats::GetStatValue (STAT_FAT) < 750.0f;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CStats::SetStatValue (STAT_FAT, 1000.0f);

        GameUtil::RebuildPlayer ();
    }
};

DEFINE_EFFECT (FatPlayerEffect, "effect_fat_player", 0);