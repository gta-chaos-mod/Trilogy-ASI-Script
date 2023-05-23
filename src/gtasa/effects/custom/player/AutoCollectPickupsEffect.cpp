#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include <CPickups.h>

namespace
{
const float MAX_RADIUS = 15.0f;

bool
pointInRadius (const CVector &p1, const CVector &p2, const float R = MAX_RADIUS)
{
    auto dx = std::abs (p1.x - p2.x);
    auto dy = std::abs (p1.y - p2.y);
    auto dz = std::abs (p1.z - p2.z);
    if ((dx + dy + dz) <= R) return true;

    return (dx * dx + dy * dy + dz * dz <= R * R);
}
} // namespace

class AutoCollectPickupsEffect : public EffectBase
{
private:
    static constexpr int weaponsIds[]
        = {342, 343, 344, 346, 347, 348, 349, 350, 351, 352, 353, 355, 356, 357,
           358, 359, 360, 361, 362, 363, 365, 366, 367, 372, 321, 322, 323, 324,
           325, 326, 331, 333, 334, 335, 336, 337, 338, 339, 341, 371};

public:
    void
    OnTick (EffectInstance *inst) override
    {
        if (!GameUtil::IsPlayerSafe ())
        {
            return;
        }

        auto *player = FindPlayerPed ();
        if (!player) return;

        auto *wanted = FindPlayerWanted (-1);
        if (!wanted) return;

        auto *playerInfo = player->GetPlayerInfoForThisPlayerPed ();

        for (int i = 0; i < MAX_NUM_PICKUPS; i++)
        {
            auto *pickup = CPickups::aPickUps + i;
            if (!pickup) continue;

            auto pickupPos = pickup->GetPosn ();
            auto playerPos = player->GetPosition ();
            if (!pointInRadius (pickupPos, playerPos)) continue;

            if (!pickup->m_nFlags.bVisible || pickup->m_nFlags.bDisabled)
                continue;

            if (pickup->m_nModelIndex == 1247 && (wanted->m_nWantedLevel > 0))
            {
                PickupItem (pickup, player);
                continue;
            }
            if (pickup->m_nModelIndex == 1242
                && (player->m_fArmour < playerInfo->m_nMaxArmour))
            {
                PickupItem (pickup, player);
                continue;
            }
            if (pickup->m_nModelIndex == 1240
                && (player->m_fHealth < player->m_fMaxHealth))
            {
                PickupItem (pickup, player);
                continue;
            }
            if (pickup->m_nPickupType == PICKUP_MONEY)
            {
                PickupItem (pickup, player);
                continue;
            }

            auto it = std::find (std::begin (weaponsIds), std::end (weaponsIds),
                                 pickup->m_nModelIndex);
            if (it != std::end (weaponsIds))
            {
                CStreaming::RequestModel (pickup->m_nModelIndex, 2);
                CStreaming::LoadAllRequestedModels (false);

                auto type = CPickups::WeaponForModel (pickup->m_nModelIndex);
                player->GiveWeapon (eWeaponType (type), 0, 1);

                PickupItem (pickup, player);
            }
        }
    }

    void
    PickupItem (CPickup *pickup, CPlayerPed *player)
    {
        auto pickupPos = pickup->GetPosn ();
        auto playerPos = player->GetPosition ();

        pickup->SetPosn (playerPos.x, playerPos.y, playerPos.z);
        pickup->Update (player, nullptr, 0);
        pickup->SetPosn (pickupPos.x, pickupPos.y, pickupPos.z);
    }
};

DEFINE_EFFECT (AutoCollectPickupsEffect, "effect_auto_collect_pickups",
               GROUP_WEAPONS);