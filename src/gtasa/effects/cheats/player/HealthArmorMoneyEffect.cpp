#include "effects/OneTimeEffect.h"

#include <CPlayerInfo.h>

class HealthArmorMoneyEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPlayerInfo *playerInfo = player->GetPlayerInfoForThisPlayerPed ();

            player->m_fHealth = player->m_fMaxHealth;
            player->m_fArmour = playerInfo->m_nMaxArmour;
            playerInfo->m_nMoney += 250000;

            CVehicle *vehicle = FindPlayerVehicle (-1, false);
            if (vehicle)
            {
                float setHealth
                    = vehicle->m_fHealth > 1000.0f ? 100000.0f : 1000.0f;
                vehicle->Fix ();
                vehicle->m_fHealth = setHealth;
            }
        }
    }
};

DEFINE_EFFECT (HealthArmorMoneyEffect, "effect_health_armor_money",
               GROUP_HEALTH);