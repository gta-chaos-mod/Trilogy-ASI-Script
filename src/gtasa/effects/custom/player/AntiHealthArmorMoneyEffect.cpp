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
        if (!vehicle) return;

        float setHealth    = vehicle->m_fHealth > 1000.0f ? 1250.0f : 250.0f;
        vehicle->m_fHealth = std::min (vehicle->m_fHealth, setHealth);
    }
};

DEFINE_EFFECT (AntiHealthArmorMoneyEffect, "effect_anti_health_armor_money",
               GROUP_HEALTH);