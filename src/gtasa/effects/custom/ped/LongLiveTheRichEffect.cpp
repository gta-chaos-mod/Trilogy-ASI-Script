#include "util/CPedDamageResponseCalculator.h"
#include "util/EffectBase.h"

#include <CPickup.h>
#include <CPlayerInfo.h>
#include <CTheScripts.h>
#include <CWorld.h>

using namespace plugin;

class LongLiveTheRichEffect : public EffectBase
{
    static inline int   storedMoney      = 0;
    static inline float gainedMoney      = 0.0f;
    bool               *neverHungryCheat = reinterpret_cast<bool *> (0x969174);

public:
    void
    OnStart (EffectInstance *inst) override
    {
        storedMoney = 0;
        gainedMoney = 0.0f;

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPlayerInfo *playerInfo = player->GetPlayerInfoForThisPlayerPed ();
            storedMoney             = playerInfo->m_nMoney;

            gainedMoney       = player->m_fHealth;
            player->m_fHealth = player->m_fMaxHealth;
        }

        injector::MakeCALL (0x58EE9A, Hooked_CHud_RenderHealthBar);
        injector::MakeCALL (0x4B5B27, Hooked_ComputeWillKillPed);
        for (int address : {0x45902E, 0x459095})
        {
            injector::MakeCALL (address, Hooked_CPickup_Update);
        }

        injector::MakeCALL (0x5D1552, Hooked_CPlayerInfo_Save);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        *neverHungryCheat = false;

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            player->m_fHealth = std::min (gainedMoney, player->m_fMaxHealth);

            CPlayerInfo *playerInfo = player->GetPlayerInfoForThisPlayerPed ();

            playerInfo->m_nMoney = std::min ((int) gainedMoney * 100, 100000);
            playerInfo->m_nMoney += storedMoney;
            playerInfo->m_nDisplayMoney = playerInfo->m_nMoney;
        }

        injector::MakeCALL (0x5D1552, 0x5D3AC0);
        // TODO: Unhook
    }

    void
    OnTick (EffectInstance *inst) override
    {
        *neverHungryCheat = true;

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPlayerInfo *playerInfo = player->GetPlayerInfoForThisPlayerPed ();

            playerInfo->m_nMoney        = (int) gainedMoney;
            playerInfo->m_nDisplayMoney = (int) gainedMoney;
        }
    }

    static void
    Hooked_CHud_RenderHealthBar (int playerId, signed int x, signed int y)
    {
    }

    static void __fastcall Hooked_ComputeWillKillPed (
        CPedDamageResponseCalculator *thisCalc, void *edx, CPed *ped,
        uint8_t *cDamageResponseInfo, char a4)
    {
        float maxDamage = std::min (ped->m_fHealth, thisCalc->m_fDamageFactor);
        maxDamage = thisCalc->m_pedPieceType == 9 ? ped->m_fHealth : maxDamage;

        CPlayerPed *player       = FindPlayerPed ();
        CEntity    *playerEntity = FindPlayerEntity (-1);
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

    static bool __fastcall Hooked_CPickup_Update (CPickup    *thisPickup,
                                                  void       *edx,
                                                  CPlayerPed *playerPed,
                                                  CVehicle   *vehicle,
                                                  int         playerId)
    {
        bool isMoneyPickup
            = thisPickup->m_nPickupType == ePickupType::PICKUP_MONEY
              || thisPickup->m_nPickupType
                     == ePickupType::PICKUP_MONEY_DOESNTDISAPPEAR
              || thisPickup->m_nPickupType == ePickupType::PICKUP_ASSET_REVENUE;

        if (isMoneyPickup && thisPickup->m_nAmmo > 0) return false;

        return plugin::CallMethodAndReturn<bool, 0x457410, CPickup *,
                                           CPlayerPed *, CVehicle *, int> (
            thisPickup, playerPed, vehicle, playerId);
    }

    static char __fastcall Hooked_CPlayerInfo_Save (CPlayerInfo *thisInfo)
    {
        thisInfo->m_nMoney = storedMoney;
        char result
            = CallMethodAndReturn<char, 0x5D3AC0, CPlayerInfo *> (thisInfo);
        thisInfo->m_nMoney = (int) gainedMoney;

        return result;
    }
};

DEFINE_EFFECT (LongLiveTheRichEffect, "effect_long_live_the_rich",
               GROUP_HEALTH);