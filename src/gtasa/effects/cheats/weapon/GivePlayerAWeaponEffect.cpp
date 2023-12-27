#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"

#include <CPickups.h>
#include <CStreaming.h>
#include <CWeaponInfo.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;
namespace
{
enum eWeaponSlot : unsigned int
{
    UNARMED,
    MELEE,
    HANDGUN,
    SHOTGUN,
    SMG,
    RIFLE,
    SNIPER,
    HEAVY,
    THROWN,
    SPECIAL,
    GIFT,
    PARACHUTE,
    DETONATOR,
};
} // namespace

class GivePlayerAWeapon : public OneTimeEffect
{
private:
    eWeaponType weaponType = WEAPON_BRASSKNUCKLE;

public:
    GivePlayerAWeapon (eWeaponType weapon) : weaponType (weapon) {}

    bool
    CanActivate () override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return false;

        if (player->m_aWeapons[player->GetWeaponSlot (weaponType)].m_eWeaponType
            == WEAPON_PARACHUTE)
            return false;

        return GameUtil::IsPlayerSafe ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        auto m = CPickups::ModelForWeapon (weaponType);
        CStreaming::RequestModel (m, 2);
        CStreaming::LoadAllRequestedModels (false);

        const auto *info = CWeaponInfo::GetWeaponInfo (weaponType, 1);

        if (!info) return;

        unsigned int ammo = 0;

        switch (info->m_nSlot)
        {
            case eWeaponSlot::HANDGUN: ammo = 50; break;
            case eWeaponSlot::SHOTGUN: ammo = 35; break;
            case eWeaponSlot::SMG: ammo = 100; break;
            case eWeaponSlot::RIFLE: ammo = 50; break;
            case eWeaponSlot::SNIPER: ammo = 20; break;
            case eWeaponSlot::HEAVY: ammo = 10; break;
            case eWeaponSlot::THROWN: ammo = 10; break;
            case eWeaponSlot::SPECIAL: ammo = 500; break;
            default: break;
        }

        if (weaponType == WEAPON_MINIGUN)
        {
            ammo = 250;
        }

        Command<eScriptCommands::COMMAND_GIVE_WEAPON_TO_CHAR> (player,
                                                               weaponType,
                                                               ammo);

        CStreaming::SetModelIsDeletable (m);
    }
};

// clang-format off
DEFINE_EFFECT (GivePlayerAWeapon, "effect_give_ak47", GROUP_WEAPONS, WEAPON_AK47);
DEFINE_EFFECT (GivePlayerAWeapon, "effect_give_uzi", GROUP_WEAPONS, WEAPON_MICRO_UZI);
DEFINE_EFFECT (GivePlayerAWeapon, "effect_give_sniper", GROUP_WEAPONS, WEAPON_SNIPERRIFLE);
DEFINE_EFFECT (GivePlayerAWeapon, "effect_give_shotgun", GROUP_WEAPONS, WEAPON_SPAS12);
DEFINE_EFFECT (GivePlayerAWeapon, "effect_give_rocket_launcher", GROUP_WEAPONS, WEAPON_RLAUNCHER_HS);
DEFINE_EFFECT (GivePlayerAWeapon, "effect_give_pistol", GROUP_WEAPONS, WEAPON_PISTOL_SILENCED);
DEFINE_EFFECT (GivePlayerAWeapon, "effect_give_minigun", GROUP_WEAPONS, WEAPON_MINIGUN);
DEFINE_EFFECT (GivePlayerAWeapon, "effect_weapon_set_4", GROUP_WEAPONS, WEAPON_MINIGUN);
DEFINE_EFFECT (GivePlayerAWeapon, "effect_give_grenades", GROUP_WEAPONS, WEAPON_GRENADE);
DEFINE_EFFECT (GivePlayerAWeapon, "effect_give_chainsaw", GROUP_WEAPONS, WEAPON_CHAINSAW);
DEFINE_EFFECT (GivePlayerAWeapon, "effect_get_parachute", GROUP_WEAPONS, WEAPON_PARACHUTE);
// clang-format on