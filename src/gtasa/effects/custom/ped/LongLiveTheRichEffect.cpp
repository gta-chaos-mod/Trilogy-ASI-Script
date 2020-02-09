#include "LongLiveTheRichEffect.h"

bool  LongLiveTheRichEffect::isEnabled   = false;
int   LongLiveTheRichEffect::storedMoney = 0;
float LongLiveTheRichEffect::gainedMoney = 0.0f;

LongLiveTheRichEffect::LongLiveTheRichEffect ()
    : EffectBase ("effect_long_live_the_rich")
{
    AddType ("health");

    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        storedMoney = player->GetPlayerInfoForThisPlayerPed ()->m_nMoney;
    }
}

void
LongLiveTheRichEffect::InitializeHooks ()
{
    EffectBase::InitializeHooks ();

    HookCall (0x58EE9A, HookedCHudRenderHealthBar);
    HookCall (0x4B5B27, HookedComputeWillKillPed);

    for (int address : {0x45902E, 0x459095})
    {
        HookCall (address, HookedPickupUpdate);
    }
}

void
LongLiveTheRichEffect::Enable ()
{
    EffectBase::Enable ();

    *neverHungryCheat = true;

    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        gainedMoney       = player->m_fHealth;
        player->m_fHealth = player->m_fMaxHealth;
    }
}

void
LongLiveTheRichEffect::Disable ()
{
    isEnabled = false;

    *neverHungryCheat = false;

    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        player->m_fHealth = std::min (gainedMoney, player->m_fMaxHealth);

        player->GetPlayerInfoForThisPlayerPed ()->m_nMoney
            = std::min ((int) gainedMoney * 100, 100000);
        player->GetPlayerInfoForThisPlayerPed ()->m_nMoney += storedMoney;
        player->GetPlayerInfoForThisPlayerPed ()->m_nDisplayMoney
            = player->GetPlayerInfoForThisPlayerPed ()->m_nMoney;
    }

    EffectBase::Disable ();
}

void
LongLiveTheRichEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    isEnabled = true;

    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        player->GetPlayerInfoForThisPlayerPed ()->m_nMoney = (int) gainedMoney;
        player->GetPlayerInfoForThisPlayerPed ()->m_nDisplayMoney
            = (int) gainedMoney;
    }
}

void __fastcall LongLiveTheRichEffect::HookedComputeWillKillPed (
    CPedDamageResponseCalculator *thisCalc, void *edx, CPed *ped,
    uint8_t *cDamageResponseInfo, char a4)
{
    float maxDamage = std::min (ped->m_fHealth, thisCalc->m_fDamageFactor);
    maxDamage = thisCalc->m_pedPieceType == 9 ? ped->m_fHealth : maxDamage;

    CPlayerPed *player       = FindPlayerPed ();
    CEntity *   playerEntity = FindPlayerEntity (-1);
    if (thisCalc->m_pDamager == playerEntity && ped != playerEntity)
    {
        gainedMoney += maxDamage / 10.0f;
    }
    else if (ped == player)
    {
        gainedMoney -= thisCalc->m_fDamageFactor;
        gainedMoney = std::max (0.0f, gainedMoney);

        if (gainedMoney == 0.0f)
        {
            player->m_fHealth = 0.0f;
            thisCalc->ComputeWillKillPed (ped, cDamageResponseInfo, a4);
        }

        return;
    }

    thisCalc->ComputeWillKillPed (ped, cDamageResponseInfo, a4);
}

bool __fastcall LongLiveTheRichEffect::HookedPickupUpdate (
    CPickup *thisPickup, void *edx, CPlayerPed *playerPed, CVehicle *vehicle,
    int playerId)
{
    bool isMoneyPickup
        = thisPickup->m_nPickupType == ePickupType::PICKUP_MONEY
          || thisPickup->m_nPickupType
                 == ePickupType::PICKUP_MONEY_DOESNTDISAPPEAR
          || thisPickup->m_nPickupType == ePickupType::PICKUP_ASSET_REVENUE;

    if (isMoneyPickup && thisPickup->m_nAmmo > 0)
    {
        return false;
    }

    return plugin::CallMethodAndReturn<bool, 0x457410, CPickup *, CPlayerPed *,
                                       CVehicle *, int> (thisPickup, playerPed,
                                                         vehicle, playerId);
}

void
LongLiveTheRichEffect::HookedCHudRenderHealthBar (int playerId, signed int x,
                                                  signed int y)
{
}
