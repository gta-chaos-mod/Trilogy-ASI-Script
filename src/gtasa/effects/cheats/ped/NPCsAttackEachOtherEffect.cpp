#include "effects/DisabledForMissionEffect.h"
#include "effects/TimedFunctionEffect.h"
#include "util/GameUtil.h"

#include <CCheat.h>

class NPCsAttackEachOtherEffect : public TimedFunctionEffect
{
public:
    NPCsAttackEachOtherEffect ()
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

using RegisterPedsAttackEachOtherEffect
    = DisabledForMissionEffect<NPCsAttackEachOtherEffect>;

DEFINE_EFFECT (RegisterPedsAttackEachOtherEffect,
               "effect_peds_attack_each_other",
               GROUP_PED_SPAWNS | GROUP_PEDS_ATTACK);