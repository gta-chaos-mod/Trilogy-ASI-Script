#include "util/CPedDamageResponseCalculator.h"
#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

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

        HOOK_METHOD_ARGS (inst, Hooked_ComputeWillKillPed,
                          void (CPedDamageResponseCalculator *, CPed *,
                                uint8_t *, char),
                          0x4B5B27);

        HOOK_METHOD_ARGS (inst, Hooked_CPickup_Update,
                          bool (CPickup *, CPlayerPed *, CVehicle *, int),
                          0x45902E, 0x459095);

        HOOK_METHOD_ARGS (inst, Hooked_CPlayerInfo_Save, char (CPlayerInfo *),
                          0x5D1552);

        // Chud::RenderHealthBar int playerId, signed int x, signed int y
        HOOK (inst, Hooked_Empty, void (int, signed int, signed int), 0x58EE9A);
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
    Hooked_ComputeWillKillPed (auto                        &&cb,
                               CPedDamageResponseCalculator *thisCalc,
                               CPed *ped, uint8_t *cDamageResponseInfo, char a4)
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
                cb ();
            }

            return;
        }

        cb ();
    }

    static bool
    Hooked_CPickup_Update (auto &&cb, CPickup *thisPickup,
                           CPlayerPed *playerPed, CVehicle *vehicle,
                           int playerId)
    {
        bool isMoneyPickup
            = thisPickup->m_nPickupType == ePickupType::PICKUP_MONEY
              || thisPickup->m_nPickupType
                     == ePickupType::PICKUP_MONEY_DOESNTDISAPPEAR
              || thisPickup->m_nPickupType == ePickupType::PICKUP_ASSET_REVENUE;

        if (isMoneyPickup && thisPickup->m_nAmmo > 0) return false;

        return cb ();
    }

    static char
    Hooked_CPlayerInfo_Save (auto &&cb, CPlayerInfo *thisInfo)
    {
        thisInfo->m_nMoney = storedMoney;
        char result        = cb ();
        thisInfo->m_nMoney = (int) gainedMoney;

        return result;
    }

    static void
    Hooked_Empty (auto &&cb)
    {
    }
};

DEFINE_EFFECT (LongLiveTheRichEffect, "effect_long_live_the_rich",
               GROUP_HEALTH);