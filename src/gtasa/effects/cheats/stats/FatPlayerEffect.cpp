#include <effects/OneTimeEffect.h>
#include <util/GameUtil.h>

#include <CStats.h>

class FatPlayerEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CStats::SetStatValue (STAT_FAT, 1000.0f);

        GameUtil::RebuildPlayer ();
    }
};

DEFINE_EFFECT (FatPlayerEffect, "effect_fat_player", 0);