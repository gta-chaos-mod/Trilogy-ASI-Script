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

using RegisterNPCsAttackEachOtherEffect
    = DisabledForMissionEffect<NPCsAttackEachOtherEffect>;

DEFINE_EFFECT (RegisterNPCsAttackEachOtherEffect,
               "effect_npcs_attack_each_other",
               GROUP_NPC_SPAWNS | GROUP_NPCS_ATTACK);