#include "util/EffectBase.h"
#include "util/Teleportation.h"

#include <CRadar.h>
#include <CStreaming.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class TeleportToMarkerEffect : public EffectBase
{
public:
    bool
    CanActivate () override
    {
        return Teleportation::CanTeleport ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        ClearMarker ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (!IsMarkerPlaced ()) return;

        if (!CanActivate ())
        {
            inst->ResetTimer ();
            return;
        }

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CVector markerPosition = GetAdjustedMarkerPosition ();

        Teleportation::Teleport (markerPosition);

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle)
        {
            // Place on road properly
            vehicle->m_vecMoveSpeed = CVector (0.0f, 0.0f, 0.0f);
            vehicle->m_vecTurnSpeed = CVector (0.0f, 0.0f, 0.0f);

            int vehicleClass = vehicle->m_nVehicleClass;
            if (vehicleClass == 9)
            {
                CBike *bike = (CBike *) vehicle;
                bike->PlaceOnRoadProperly ();
            }
            else if (vehicleClass != 5)
            {
                CAutomobile *automobile = (CAutomobile *) vehicle;
                automobile->PlaceOnRoadProperly ();
            }
        }

        ClearMarker ();

        inst->Disable ();
    }

    void
    ClearMarker ()
    {
        CRadar::ClearBlip (FrontEndMenuManager.m_nTargetBlipIndex);
        FrontEndMenuManager.m_nTargetBlipIndex = 0;
    }

    bool
    IsMarkerPlaced ()
    {
        return FrontEndMenuManager.m_nTargetBlipIndex
               && CRadar::ms_RadarTrace[LOWORD (FrontEndMenuManager
                                                    .m_nTargetBlipIndex)]
                          .m_nCounter
                      == HIWORD (FrontEndMenuManager.m_nTargetBlipIndex);
    }

    CVector
    GetMarkerPosition ()
    {
        if (IsMarkerPlaced ())
        {
            return CRadar::ms_RadarTrace[LOWORD (FrontEndMenuManager
                                                     .m_nTargetBlipIndex)]
                .m_vPosition;
        }

        return {0.0f, 0.0f, 0.0f};
    }

    CVector
    GetAdjustedMarkerPosition ()
    {
        CVector markerPosition = GetMarkerPosition ();

        Command<eScriptCommands::COMMAND_REQUEST_COLLISION> (markerPosition.x,
                                                             markerPosition.y);
        CStreaming::StreamZoneModels (&markerPosition);
        CStreaming::LoadAllRequestedModels (false);
        CStreaming::LoadScene (&markerPosition);

        markerPosition.z
            = CWorld::FindGroundZForCoord (markerPosition.x, markerPosition.y)
              + 3.0f;

        return markerPosition;
    }
};

DEFINE_EFFECT (TeleportToMarkerEffect, "effect_teleport_to_marker", 0);
