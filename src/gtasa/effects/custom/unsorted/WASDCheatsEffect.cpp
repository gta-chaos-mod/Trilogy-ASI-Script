#include "util/EffectBase.h"
#include "util/GenericUtil.h"
#include "util/hooks/HookMacros.h"

#include <CCheat.h>
#include <CPickups.h>
#include <CStats.h>
#include <CWeather.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

namespace
{
void
adjustPlayerStat (int stat, float value, float min, float max)
{
    float oldValue = CStats::GetStatValue (stat);
    oldValue       = std::clamp (oldValue + value, min, max);
    CStats::SetStatValue (stat, oldValue);
    GameUtil::RebuildPlayer ();
}
std::vector<std::function<void (EffectInstance *)>> customCheats = {
    [] (EffectInstance *inst)
    {
        auto *player = FindPlayerPed ();
        if (!player) return;

        auto *playerInfo = player->GetPlayerInfoForThisPlayerPed ();

        auto value = inst->Random (5.0f, 15.0f);
        player->m_fHealth
            = std::max (player->m_fHealth + value, player->m_fMaxHealth);
        playerInfo->m_nMoney += inst->Random (5, 10) * 1000;

        auto *vehicle = FindPlayerVehicle (-1, false);
        if (!vehicle) return;

        float setHealth    = std::max (vehicle->m_fHealth + 75.0f, 1250.0f);
        vehicle->m_fHealth = setHealth;
    },
    [] (EffectInstance *inst)
    { adjustPlayerStat (STAT_FAT, 50.0f, 250.0f, 750.0f); },
    [] (EffectInstance *inst)
    { adjustPlayerStat (STAT_FAT, -50.0f, 250.0f, 750.0f); },
    [] (EffectInstance *inst)
    { adjustPlayerStat (STAT_MUSCLE, 50.0f, 250.0f, 750.0f); },
    [] (EffectInstance *inst)
    { adjustPlayerStat (STAT_MUSCLE, -50.0f, 250.0f, 750.0f); },
    [] (EffectInstance *inst)
    {
        adjustPlayerStat (STAT_FAT, -50.0f, 250.0f, 750.0f);
        adjustPlayerStat (STAT_MUSCLE, -50.0f, 250.0f, 750.0f);
    },
    [] (EffectInstance *inst)
    { adjustPlayerStat (STAT_STAMINA, 50.0f, 250.0f, 750.0f); },
    [] (EffectInstance *inst)
    { adjustPlayerStat (STAT_STAMINA, -50.0f, 250.0f, 750.0f); },
    [] (EffectInstance *inst)
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            if (!vehicle) continue;

            bool cond = vehicle->m_nStatus != STATUS_WRECKED;
            cond &= vehicle->m_fHealth > 0.0f;

            if (cond && inst->Random (1, 100000) % 100 == 0)
            {
                vehicle->m_nPhysicalFlags.bExplosionProof = false;
                vehicle->BlowUpCar (nullptr, false);
                continue;
            }

            if (cond)
            {
                vehicle->m_fHealth
                    = std::max (250.0f, vehicle->m_fHealth - 125.0f);
            }

            cond &= inst->Random (1, 100000) % 20 == 0;
            cond &= vehicle->m_fHealth > 250.0f;
            if (cond)
            {
                vehicle->m_fHealth = 249.0f;
            }
        }
    },
    [] (EffectInstance *inst)
    {
        auto *player = FindPlayerPed ();
        if (!player) return;

        auto *playerInfo  = player->GetPlayerInfoForThisPlayerPed ();
        auto  dmg         = inst->Random (5.0f, 15.0f);
        player->m_fHealth = std::max (player->m_fHealth - dmg, 0.0f);
    },
    [] (EffectInstance *inst)
    {
        int stats[] = {STAT_PISTOL_SKILL,
                       STAT_SILENCED_PISTOL_SKILL,
                       STAT_DESERT_EAGLE_SKILL,
                       STAT_SHOTGUN_SKILL,
                       STAT_SAWN_OFF_SHOTGUN_SKILL,
                       STAT_COMBAT_SHOTGUN_SKILL,
                       STAT_MACHINE_PISTOL_SKILL,
                       STAT_SMG_SKILL,
                       STAT_AK_47_SKILL,
                       STAT_M4_SKILL};
        for (const auto &stat : stats)
        {
            adjustPlayerStat (stat, 10.0f, 0.0f, 1000.0f);
        }
    },
    [] (EffectInstance *inst)
    {
        int stats[] = {STAT_DRIVING_SKILL, STAT_FLYING_SKILL,
                       STAT_CYCLING_SKILL, STAT_BIKE_SKILL};
        for (const auto &stat : stats)
        {
            adjustPlayerStat (stat, 10.0f, 0.0f, 1000.0f);
        }
    },
    [] (EffectInstance *inst)
    {
        auto *wanted = FindPlayerWanted (-1);
        if (!wanted) return;

        int targetWanted = std::min (wanted->m_nWantedLevel + 1u, 6u);
        wanted->CheatWantedLevel (targetWanted);
    },
    [] (EffectInstance *inst)
    {
        auto *wanted = FindPlayerWanted (-1);
        if (!wanted) return;

        if (wanted->m_nWantedLevel > 0)
        {
            wanted->CheatWantedLevel (wanted->m_nWantedLevel - 1);
        }
    },
    [] (EffectInstance *inst)
    {
        int weather = inst->Random (0, int (WEATHER_SANDSTORM_DESERT));
        CWeather::ForceWeatherNow (weather);
    },
    [] (EffectInstance *inst)
    {
        auto *player = FindPlayerPed ();
        if (!player || player->m_nAreaCode) return;

        int  ids[] = {473, 462, 600, 409, 485, 574, 423, 583, 457};
        auto idx   = inst->Random (0, int (std::size (ids)) - 1);

        auto position = player->TransformFromObjectSpace ({0.0f, 15.0f, 5.0f});
        GameUtil::CreateVehicle (ids[idx], position, 3.1415926f, true);
    },
    [] (EffectInstance *inst)
    {
        auto *player = FindPlayerPed ();
        if (!player) return;

        auto *vehicle = FindPlayerVehicle (-1, false);

        eWeaponType weapons[] = {WEAPON_CHAINSAW, WEAPON_KATANA, WEAPON_SPAS12};
        for (CPed *ped : CPools::ms_pPedPool)
        {
            if (!ped) continue;
            if (ped == player) continue;

            Command<eScriptCommands::COMMAND_SET_CHAR_RELATIONSHIP> (
                ped, 4, ePedType::PED_TYPE_PLAYER1);
            auto weapon
                = weapons[inst->Random (0, 100000) % std::size (weapons)];

            int m = CPickups::ModelForWeapon (weapon);
            CStreaming::RequestModel (m, 2);
            CStreaming::LoadAllRequestedModels (false);
            CStreaming::SetModelIsDeletable (m);

            Command<eScriptCommands::COMMAND_GIVE_WEAPON_TO_CHAR> (ped, weapon,
                                                                   1);
            Command<eScriptCommands::COMMAND_SET_CURRENT_CHAR_WEAPON> (ped,
                                                                       weapon);
            Command<eScriptCommands::COMMAND_TASK_KILL_CHAR_ON_FOOT> (ped,
                                                                      player);
        }
    },
    [] (EffectInstance *inst)
    {
        auto *player = FindPlayerPed ();
        if (!player) return;

        auto p = player->GetPosition ();
        p.x += inst->Random (-15.0f, 15.0f);
        p.y += inst->Random (-15.0f, 15.0f);
        int explostionType = 11;
        if (inst->Random (1, 100000) % 2 == 0)
        {
            explostionType = 0;
        }
        Command<eScriptCommands::COMMAND_ADD_EXPLOSION> (p.x, p.y, p.z,
                                                         explostionType);
    }};

std::string cheatString;
} // namespace

class WASDCheatsEffect : public EffectBase
{
    int       timer      = 0;
    int       CHECK_TIME = 5000;
    const int SUBSTR_LEN = 10;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        cheatString.reserve (32);
        cheatString.clear ();

        HOOK_ARGS (inst, Hook_AddToCheatString, void (char key), 0x438480);
    }

    static void
    Hook_AddToCheatString (auto &&cb, char key)
    {
        cb ();
        if (!CCutsceneMgr::ms_running)
        {
            cheatString.append (1, key);
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (!GameUtil::IsPlayerSafe ()) return;

        timer += int (GenericUtil::CalculateTick ());

        if (timer >= CHECK_TIME)
        {
            if (isWASDTyped ())
            {
                Command<eScriptCommands::COMMAND_PRINT_HELP> ("CHEAT1");
                int cheat = inst->Random (0, 100000) % customCheats.size ();
                customCheats[cheat](inst);
            }
            cheatString.clear ();
            timer -= CHECK_TIME;
        }
    }

    bool
    isWASDTyped () const
    {
        if (cheatString.empty ())
        {
            return false;
        }

        std::string cheat (cheatString.substr (0, SUBSTR_LEN));

        for (auto c : cheat)
        {
            c = std::tolower (c);
            if (c != 'w' && c != 'a' && c != 's' && c != 'd')
            {
                return false;
            }
        }

        return true;
    }
};

DEFINE_EFFECT (WASDCheatsEffect, "effect_wasd_cheats", 0);
