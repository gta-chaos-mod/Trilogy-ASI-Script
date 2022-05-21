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
        if (player)
        {
            CPlayerInfo *playerInfo = player->GetPlayerInfoForThisPlayerPed ();

            float healthDamage = playerInfo->m_nMaxHealth * 0.25f;
            float armorDamage  = playerInfo->m_nMaxArmour * 0.25f;

            player->m_fHealth -= healthDamage;
            player->m_fArmour -= armorDamage;
            playerInfo->m_nMoney = std::max (0, playerInfo->m_nMoney - 250000);

            CVehicle *vehicle = FindPlayerVehicle (-1, false);
            if (vehicle) vehicle->m_fHealth -= 250.0f;
        }
    }
};

DEFINE_EFFECT (AntiHealthArmorMoneyEffect, "effect_anti_health_armor_money",
               GROUP_HEALTH);