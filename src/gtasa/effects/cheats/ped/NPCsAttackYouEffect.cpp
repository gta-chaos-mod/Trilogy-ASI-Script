#include "effects/DisabledForMissionEffect.h"
#include "effects/TimedFunctionEffect.h"
#include "util/GameUtil.h"

#include <CCheat.h>

class NPCsAttackYouEffect : public TimedFunctionEffect
{
public:
    NPCsAttackYouEffect ()
        : TimedFunctionEffect (CCheat::VillagePeopleCheat, 0x969158)
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

using RegisterNPCsAttackYouEffect
    = DisabledForMissionEffect<NPCsAttackYouEffect>;

DEFINE_EFFECT (RegisterNPCsAttackYouEffect, "effect_npcs_attack_you",
               GROUP_PED_SPAWNS | GROUP_PEDS_ATTACK);