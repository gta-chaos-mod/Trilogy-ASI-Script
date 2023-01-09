#include "util/EffectBase.h"

#include <CPlayerInfo.h>

class MillionaireEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        inst->SetIsOneTimeEffect ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CPlayerInfo *playerInfo = player->GetPlayerInfoForThisPlayerPed ();
        if (!playerInfo) return;

        playerInfo->m_nMoney += 1000000;
        inst->Disable ();
    }
};

DEFINE_EFFECT (MillionaireEffect, "effect_millionaire", 0);
