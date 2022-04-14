#include <effects/TimedFunctionEffect.h>
#include <util/GameUtil.h>

#include "CCheat.h"

class HaveABountyOnYourHeadEffect : public TimedFunctionEffect
{
public:
    HaveABountyOnYourHeadEffect ()
        : TimedFunctionEffect (CCheat::EverybodyAttacksPlayerCheat, 0x96913F)
    {
    }

    void
    OnStart (EffectInstance *inst) override
    {
        GameUtil::BackupAcquaintances ();

        TimedFunctionEffect::OnStart (inst);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        TimedFunctionEffect::OnEnd (inst);

        GameUtil::RestoreSavedAcquaintances ();
    }
};

DEFINE_EFFECT (HaveABountyOnYourHeadEffect, "effect_have_a_bounty_on_your_head",
               GROUP_PED_SPAWNS | GROUP_PEDS_ATTACK);