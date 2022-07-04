#include "util/EffectBase.h"

#include <CFont.h>
#include <CMenuManager.h>
#include <CSprite.h>

using namespace plugin;

class PedWallhackEffect : public EffectBase
{
    static inline std::vector<std::string> weaponNames = {"None",
                                                          "Brassknuckle",
                                                          "Golfclub",
                                                          "Nightstick",
                                                          "Knife",
                                                          "Bat",
                                                          "Shovel",
                                                          "Poolstick",
                                                          "Katana",
                                                          "Chainsaw",
                                                          "Fun Toy", // DILDO1
                                                          "Fun Toy", // DILDO2
                                                          "Fun Toy", // VIBE1
                                                          "Fun Toy", // VIBE2
                                                          "Flowers",
                                                          "Cane",
                                                          "Grenade",
                                                          "Teargas",
                                                          "Molotov",
                                                          "Rocket Launcher",
                                                          "HS Rocket Launcher",
                                                          "Unused",
                                                          "Pistol",
                                                          "Silenced Pistol",
                                                          "Desert Eagle",
                                                          "Shotgun",
                                                          "Sawn-off Shotgun",
                                                          "Combat Shotgun",
                                                          "Micro Uzi",
                                                          "MP5",
                                                          "AK-47",
                                                          "M4",
                                                          "Tec-9",
                                                          "Country Rifle",
                                                          "Sniper",
                                                          "Rocket Launcher",
                                                          "HS Rocket Launcher",
                                                          "Flamethrower",
                                                          "Minigun",
                                                          "Satchel",
                                                          "Satchel Detonator",
                                                          "Spraycan",
                                                          "Fire Extinguisher",
                                                          "Camera",
                                                          "Nightvision Goggles",
                                                          "Infrared Goggles",
                                                          "Parachute",
                                                          "Unused",
                                                          "Armor",
                                                          "Flare"};

public:
    void
    OnStart (EffectInstance *inst) override
    {
        Events::drawHudEvent.before += OnDraw;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::drawHudEvent.before -= OnDraw;
    }

    static void
    OnDraw ()
    {
        if (FrontEndMenuManager.m_bMenuActive) return;

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        for (CPed *ped : CPools::ms_pPedPool)
        {
            if (!ped || ped == player || !ped->IsAlive ()) continue;

            Wallhack (ped);
        }
    }

    static std::string
    GetActivePedWeapon (CPed *ped)
    {
        int slot = ped->m_nActiveWeaponSlot;
        if (slot == 0) return "None";

        CWeapon weapon = ped->m_aWeapons[slot];
        return weaponNames[weapon.m_nType];
    }

    static std::string
    IsPedInCar (CPed *ped)
    {
        CVehicle *vehicle = ped->m_pVehicle;
        if (vehicle && (vehicle->IsDriver (ped) || vehicle->IsPassenger (ped)))
            return "true";

        return "false";
    }

    static void
    Wallhack (CPed *ped)
    {
        CVector position = ped->GetPosition ();
        RwV3d   pos      = {position.x, position.y, position.z};

        RwV3d coords;
        float w, h;

        if (!CSprite::CalcScreenCoors (pos, &coords, &w, &h, true, true))
            return;

        CFont::SetOrientation (ALIGN_LEFT);
        CFont::SetColor (color::White);
        CFont::SetDropShadowPosition (1);
        CFont::SetBackground (false, false);
        CFont::SetWrapx (SCREEN_WIDTH);
        CFont::SetScale (0.5, 1.0);
        CFont::SetFontStyle (FONT_SUBTITLES);
        CFont::SetProportional (true);

        std::string text = std::format ("Skin ID: {0:}~n~", ped->m_nModelIndex);
        text.append (std::format ("Position: {:.2f}, {:.2f}, {:.2f}~n~", pos.x,
                                  pos.y, pos.z));
        text.append (std::format ("Health: {:.2f}~n~", ped->m_fHealth));
        text.append (std::format ("Armor: {:.2f}~n~", ped->m_fArmour));
        text.append (std::format ("Weapon: {}~n~", GetActivePedWeapon (ped)));
        text.append (std::format ("In Vehicle: {}~n~", IsPedInCar (ped)));

        CFont::PrintString (coords.x, coords.y, (char *) text.c_str ());
    }
};

DEFINE_EFFECT (PedWallhackEffect, "effect_ped_wallhack", 0);