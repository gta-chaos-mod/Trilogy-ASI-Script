#include "util/EffectBase.h"
#include "util/Variables.h"

#include <CStreaming.h>
#include <CTimer.h>
#include <CWeather.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class WalkOnWaterEffect : public EffectBase
{
    CObject *roadObject;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        Variables::isWalkOnWaterEffectEnabled = true;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        if (roadObject && IsObjectPointerValid (roadObject))
            roadObject->m_dwRemovalTime = CTimer::m_snTimeInMilliseconds;

        Variables::isWalkOnWaterEffectEnabled = false;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CVector position = player->GetPosition ();
        if (position.z < 1.0f && position.z > -5.0f)
            player->SetPosn (position.x, position.y, 1.0f);

        float     heading = player->m_fCurrentRotation;
        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle) heading = vehicle->GetHeading ();

        float waterLevel = 0.0f;
        Command<eScriptCommands::COMMAND_GET_WATER_HEIGHT_AT_COORDS> (
            position.x, position.y, false, &waterLevel);

        waterLevel += 0.5f;

        if (!roadObject || !IsObjectPointerValid (roadObject))
        {
            int model = 8418; // Flat concrete pad with parking
            CStreaming::RequestModel (model, 2);
            CStreaming::LoadAllRequestedModels (false);
            Command<eScriptCommands::COMMAND_CREATE_OBJECT> (model, position.x,
                                                             position.y,
                                                             waterLevel,
                                                             &roadObject);
            CStreaming::SetModelIsDeletable (model);
            roadObject->m_nObjectFlags.bDoNotRender = true;
            roadObject->m_nObjectType               = OBJECT_TEMPORARY;
        }
        else
        {
            roadObject->Teleport ({position.x, position.y, waterLevel}, false);
            roadObject->SetOrientation (0.0f, 0.0f, heading);
        }

        roadObject->m_dwRemovalTime = CTimer::m_snTimeInMilliseconds + 1000;

        CWeather::Wavyness = 0.0f;
    }
};

DEFINE_EFFECT (WalkOnWaterEffect, "effect_walk_on_water", 0);