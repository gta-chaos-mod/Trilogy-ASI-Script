#include "effects/OneTimeEffect.h"

#include <CCheat.h>
#include <CPlayerInfo.h>

class AntiHealthArmorMoneyEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CPlayerInfo *playerInfo = player->GetPlayerInfoForThisPlayerPed ();

        player->m_fHealth    = std::min (player->m_fHealth, 25.0f);
        player->m_fArmour    = 0.0f;
        playerInfo->m_nMoney = std::max (0, playerInfo->m_nMoney - 250000);

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle) vehicle->m_fHealth = 250.0f;
    }
};

DEFINE_EFFECT (AntiHealthArmorMoneyEffect, "effect_anti_health_armor_money",
               GROUP_HEALTH);