#include "HealthArmorMoneyCheat.h"

HealthArmorMoneyCheat::HealthArmorMoneyCheat ()
    : EffectPlaceholder ("cheat_health_armor_money")
{
    if (Config::GetOrDefault ("CrowdControl.Enabled", false))
    {
        AddType ("health");
    }
}

void
HealthArmorMoneyCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        player->m_fHealth = player->m_fMaxHealth;
        player->m_fArmour = 100.0f;
        player->GetPlayerInfoForThisPlayerPed ()->m_nMoney += 250000;

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
