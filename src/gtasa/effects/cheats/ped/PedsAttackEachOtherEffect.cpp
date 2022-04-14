#include <effects/TimedFunctionEffect.h>
#include <util/GameUtil.h>

#include "CCheat.h"

class PedsAttackEachOtherEffect : public TimedFunctionEffect
{
public:
    PedsAttackEachOtherEffect ()
        : TimedFunctionEffect (CCheat::MayhemCheat, 0x96913E)
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

DEFINE_EFFECT (PedsAttackEachOtherEffect, "effect_peds_attack_each_other",
               GROUP_PED_SPAWNS | GROUP_PEDS_ATTACK);