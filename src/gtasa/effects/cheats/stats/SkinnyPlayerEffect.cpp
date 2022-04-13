#include <effects/OneTimeEffect.h>
#include <util/GameUtil.h>

#include "CStats.h"

class SkinnyPlayerEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CStats::SetStatValue (eStats::STAT_FAT, 0.0f);
        CStats::SetStatValue (eStats::STAT_MUSCLE, 0.0f);

        GameUtil::RebuildPlayer ();
    }
};

DEFINE_EFFECT (SkinnyPlayerEffect, "effect_skinny_player", 0);