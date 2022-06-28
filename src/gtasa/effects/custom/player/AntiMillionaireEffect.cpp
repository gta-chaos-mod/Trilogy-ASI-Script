#include "util/EffectBase.h"

#include <CPlayerInfo.h>

class AntiMillionaireEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CPlayerInfo *playerInfo = player->GetPlayerInfoForThisPlayerPed ();
        if (!playerInfo) return;

        // -= 1 million
        playerInfo->m_nMoney -= 1000000;
        playerInfo->m_nMoney = std::max (playerInfo->m_nMoney, 0);
        inst->Disable ();
    }
};

DEFINE_EFFECT (AntiMillionaireEffect, "effect_anti_millionaire", 0);