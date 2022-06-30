#include "util/EffectBase.h"
#include "util/Globals.h"

#include <CFont.h>
#include <CMenuManager.h>
#include <CStats.h>
#include <CWeather.h>

using namespace plugin;

class TooMuchInformationEffect : public EffectBase
{
    struct Info
    {
        std::string_view              name;
        CVector2D                     position;
        std::function<std::string ()> function;
    };

    static inline std::vector<Info> information = {};

public:
    void
    OnStart (EffectInstance *inst) override
    {
        GenerateInformation (inst);

        Events::drawAfterFadeEvent += OnDraw;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::drawAfterFadeEvent -= OnDraw;

        information.clear ();
    }

    static const char *
    BoolToString (bool variable)
    {
        return variable ? "true" : "false";
    }

    void
    AddInformation (EffectInstance *inst, const char *name,
                    std::function<std::string ()> function)
    {
        information.push_back (
            Info{.name = name,
                 .position
                 = CVector2D (inst->Random (SCREEN_COORD_LEFT (20.0f),
                                            SCREEN_COORD_RIGHT (20.0f)),
                              inst->Random (SCREEN_COORD_TOP (20.0f),
                                            SCREEN_COORD_BOTTOM (20.0f))),
                 .function = function});
    }

    void
    GenerateInformation (EffectInstance *inst)
    {
        information.clear ();

        // Player Exists
        AddInformation (inst, "Player Exists",
                        []
                        {
                            CPlayerPed *player = FindPlayerPed ();
                            return BoolToString (player != nullptr);
                        });

        // Player Alive
        AddInformation (inst, "Player Alive",
                        []
                        {
                            CPlayerPed *player = FindPlayerPed ();
                            return BoolToString (player != nullptr
                                                 && player->IsAlive ());
                        });

        // Skin ID
        AddInformation (inst, "Skin ID",
                        []
                        {
                            int skinId = 0;

                            CPlayerPed *player = FindPlayerPed ();
                            if (player) skinId = player->m_nModelIndex;

                            return std::to_string (skinId);
                        });

        // Health
        AddInformation (inst, "Health",
                        []
                        {
                            float health = 0.0f;

                            CPlayerPed *player = FindPlayerPed ();
                            if (player) health = player->m_fHealth;

                            return std::format ("{:.2f}", health);
                        });

        // Armor
        AddInformation (inst, "Armor",
                        []
                        {
                            float armor = 0.0f;

                            CPlayerPed *player = FindPlayerPed ();
                            if (player) armor = player->m_fArmour;

                            return std::format ("{:.2f}", armor);
                        });

        // Position
        AddInformation (inst, "Position",
                        []
                        {
                            CVector position (0, 0, 0);

                            CPlayerPed *player = FindPlayerPed ();
                            if (player) position = player->GetPosition ();

                            return std::format ("{:.2f}, {:.2f}, {:.2f}",
                                                position.x, position.y,
                                                position.z);
                        });

        // Player State
        AddInformation (inst, "Player State",
                        []
                        {
                            ePedState state = PEDSTATE_NONE;

                            CPlayerPed *player = FindPlayerPed ();
                            if (player) state = player->m_nPedState;

                            return std::to_string (state);
                        });

        // Wanted Level
        AddInformation (inst, "Wanted Level",
                        []
                        {
                            int wanted = 0;

                            CPlayerPed *player = FindPlayerPed ();
                            if (player) wanted = player->GetWantedLevel ();

                            return std::to_string (wanted);
                        });

        // In Water
        AddInformation (
            inst, "In Water",
            []
            {
                bool water = false;

                CPlayerPed *player = FindPlayerPed ();
                if (player)
                    water = player->m_nPhysicalFlags.bTouchingWater
                            || player->m_nPhysicalFlags.bSubmergedInWater;

                return BoolToString (water);
            });

        // Player Vehicle Exists
        AddInformation (inst, "Player Vehicle Exists",
                        []
                        {
                            CVehicle *playerVehicle
                                = FindPlayerVehicle (-1, false);
                            return BoolToString (playerVehicle != nullptr);
                        });

        // Player Vehicle Model ID
        AddInformation (inst, "Player Vehicle Model ID",
                        []
                        {
                            int modelId = 0;

                            CVehicle *playerVehicle
                                = FindPlayerVehicle (-1, false);
                            if (playerVehicle)
                                modelId = playerVehicle->m_nModelIndex;

                            return std::to_string (modelId);
                        });

        // Vehicle Health
        AddInformation (inst, "Vehicle Health",
                        []
                        {
                            float health = 0.0f;

                            CVehicle *playerVehicle
                                = FindPlayerVehicle (-1, false);
                            if (playerVehicle)
                                health = playerVehicle->m_fHealth;

                            return std::format ("{:.2f}", health);
                        });

        // Vehicle Position
        AddInformation (inst, "Vehicle Position",
                        []
                        {
                            CVector position (0, 0, 0);

                            CVehicle *playerVehicle
                                = FindPlayerVehicle (-1, false);
                            if (playerVehicle)
                                position = playerVehicle->GetPosition ();

                            return std::format ("{:.2f}, {:.2f}, {:.2f}",
                                                position.x, position.y,
                                                position.z);
                        });

        // Vehicle State
        AddInformation (inst, "Vehicle State",
                        []
                        {
                            eEntityStatus status = STATUS_SIMPLE;

                            CVehicle *playerVehicle
                                = FindPlayerVehicle (-1, false);
                            if (playerVehicle)
                                status
                                    = (eEntityStatus) playerVehicle->m_nStatus;

                            return std::to_string (status);
                        });

        // Weather
        AddInformation (inst, "Weather",
                        []
                        { return std::to_string (CWeather::NewWeatherType); });

        // Ped Count
        AddInformation (inst, "Ped Count",
                        [] {
                            return std::to_string (
                                CPools::ms_pPedPool->GetNoOfUsedSpaces ());
                        });

        // Vehicle Count
        AddInformation (inst, "Vehicle Count",
                        [] {
                            return std::to_string (
                                CPools::ms_pVehiclePool->GetNoOfUsedSpaces ());
                        });

        // Building Count
        AddInformation (inst, "Building Count",
                        [] {
                            return std::to_string (
                                CPools::ms_pBuildingPool->GetNoOfUsedSpaces ());
                        });

        // Object Count
        AddInformation (inst, "Object Count",
                        [] {
                            return std::to_string (
                                CPools::ms_pObjectPool->GetNoOfUsedSpaces ());
                        });

        // Oysters Collected
        AddInformation (inst, "Oysters Collected",
                        []
                        {
                            return std::format (
                                "{:.0f}/{:.0f}",
                                CStats::GetStatValue (STAT_OYSTERS_COLLECTED),
                                CStats::GetStatValue (STAT_TOTAL_OYSTERS));
                        });

        // Horseshoes Collected
        AddInformation (inst, "Horseshoes Collected",
                        []
                        {
                            return std::format ("{:.0f}/{:.0f}",
                                                CStats::GetStatValue (
                                                    STAT_HORSESHOES_COLLECTED),
                                                CStats::GetStatValue (
                                                    STAT_TOTAL_HORSESHOES));
                        });

        // Snapshots Taken
        AddInformation (inst, "Snapshots Taken",
                        []
                        {
                            return std::format (
                                "{:.0f}/{:.0f}",
                                CStats::GetStatValue (STAT_SNAPSHOTS_TAKEN),
                                CStats::GetStatValue (STAT_TOTAL_SNAPSHOTS));
                        });

        // Luck
        AddInformation (inst, "Luck",
                        [] {
                            return std::format ("{:.0f}", CStats::GetStatValue (
                                                              STAT_LUCK));
                        });

        // Memes

        // Ryder
        AddInformation (inst, "Ryder", [] { return "Shermhead"; });

        // Yes
        AddInformation (inst, "Yes", [] { return "No."; });

        // No
        AddInformation (inst, "No", [] { return "Yes."; });
    }

    static std::string
    GetInfoString (Info info)
    {
        if (Globals::isShoutoutsToSimpleFlipsEffectEnabled)
        {
            return "Shoutouts To SimpleFlips: Shoutouts To SimpleFlips.";
        }

        return std::string (info.name).append (": ").append (info.function ());
    }

    static void
    OnDraw ()
    {
        if (FrontEndMenuManager.m_bMenuActive) return;

        for (Info info : information)
        {
            const float TEXT_SCALE_X = 1.0f;
            const float TEXT_SCALE_Y = 1.2f;

            float       xPos       = info.position.x;
            std::string infoString = GetInfoString (info);

            CFont::SetScaleForCurrentlanguage (TEXT_SCALE_X, TEXT_SCALE_Y);
            float renderWidth = CFont::GetStringWidth (const_cast<char *> (
                                                           infoString.data ()),
                                                       true, false);

            if (xPos + renderWidth > SCREEN_WIDTH)
            {
                xPos = SCREEN_COORD_RIGHT (renderWidth);
            }

            gamefont::PrintUnscaled (GetInfoString (info), xPos,
                                     info.position.y, FONT_DEFAULT,
                                     TEXT_SCALE_X, TEXT_SCALE_Y, color::White,
                                     gamefont::AlignLeft, 1, color::Black, true,
                                     9999.0F, true);
        }
    }
};

DEFINE_EFFECT (TooMuchInformationEffect, "effect_too_much_information", 0);
