#include "util/EffectBase.h"

#include <CPlayerInfo.h>

class BankruptEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CPlayerInfo *playerInfo = player->GetPlayerInfoForThisPlayerPed ();
        if (!playerInfo) return;

        // Cap the money at $10m so it doesn't run down endlessly
        playerInfo->m_nDisplayMoney
            = std::min (10000000, playerInfo->m_nDisplayMoney);

        playerInfo->m_nMoney = 0;
        inst->Disable ();
    }
};

DEFINE_EFFECT (BankruptEffect, "effect_bankrupt", 0);
