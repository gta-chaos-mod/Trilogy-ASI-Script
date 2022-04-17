#include <util/EffectBase.h>

#include "extensions/ScriptCommands.h"
#include "CStreaming.h"

using namespace plugin;

class WalkOnWaterEffect : public EffectBase
{
    CObject *roadObject;

public:
    void
    OnEnd (EffectInstance *inst) override
    {
        if (roadObject)
        {
            roadObject->Remove ();
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            // TODO: Figure out a way so peds won't trigger swimming
            // For a "no water physics" effect. Right now when the player is
            // going into water he tries to swim. If we get deep enough it get's
            // reset from what I noticed
            player->m_nPhysicalFlags.bTouchingWater    = false;
            player->m_nPhysicalFlags.bSubmergedInWater = false;

            CVector position = player->GetPosition ();
            if (position.z < 0.0f)
            {
                player->SetPosn (position.x, position.y, 1.0f);
            }

            float     heading = player->m_fCurrentRotation;
            CVehicle *vehicle = FindPlayerVehicle (-1, false);
            if (vehicle)
            {
                heading = vehicle->GetHeading ();

                vehicle->m_nPhysicalFlags.bTouchingWater    = false;
                vehicle->m_nPhysicalFlags.bSubmergedInWater = false;
            }

            // TODO: Invalidate pointer when game is loaded. Object isn't in
            // object pool anymore or something...
            if (!roadObject)
            {
                int model = 8418; // Flat concrete pad with parking
                CStreaming::RequestModel (model, 2);
                CStreaming::LoadAllRequestedModels (0);
                Command<eScriptCommands::COMMAND_CREATE_OBJECT> (
                    model, position.x, position.y, 0.0f, &roadObject);
                CStreaming::SetModelIsDeletable (model);
                roadObject->m_nObjectFlags.bDoNotRender = true;
            }
            else
            {
                roadObject->Teleport ({position.x, position.y, 0.5f}, false);
                roadObject->SetOrientation (0.0f, 0.0f, heading);
            }
        }
    }
};

DEFINE_EFFECT (WalkOnWaterEffect, "effect_walk_on_water", 0);