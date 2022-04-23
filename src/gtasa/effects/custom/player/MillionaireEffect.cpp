#include <util/EffectBase.h>

#include <CPlayerInfo.h>

class MillionaireEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPlayerInfo *playerInfo = player->GetPlayerInfoForThisPlayerPed ();
            if (playerInfo)
            {
                playerInfo->m_nMoney += 1000000;
                inst->Disable ();
            }
        }
    }
};

DEFINE_EFFECT (MillionaireEffect, "effect_millionaire", 0);
