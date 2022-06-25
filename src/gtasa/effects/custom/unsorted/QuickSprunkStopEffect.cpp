#include "effects/OneTimeEffect.h"

#include <CStreaming.h>
#include <CTimer.h>
#include <CWorld.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class QuickSprunkStopEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CVector position
            = player->TransformFromObjectSpace (CVector (0.0f, 10.0f, 0.0f));

        bool  groundResult = false;
        float groundPos = CWorld::FindGroundZFor3DCoord (position.x, position.y,
                                                         position.z + 5.0f,
                                                         &groundResult, 0)
                          + 0.5f;

        if (groundResult) position.z = groundPos;

        CObject *sprunkObject;

        int model = 955; // Sprunk Machine
        CStreaming::RequestModel (model, 2);
        CStreaming::LoadAllRequestedModels (false);
        Command<eScriptCommands::COMMAND_CREATE_OBJECT> (model, position.x,
                                                         position.y, position.z,
                                                         &sprunkObject);
        CStreaming::SetModelIsDeletable (model);

        CMatrix *matrix;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle)
            matrix = vehicle->GetMatrix ();
        else
            matrix = player->GetMatrix ();

        sprunkObject->SetMatrix (*matrix);
        sprunkObject->SetPosn (position);
        sprunkObject->m_nObjectType = OBJECT_TEMPORARY;
        sprunkObject->m_dwRemovalTime
            = CTimer::m_snTimeInMilliseconds + 1000 * 5;
    }
};

DEFINE_EFFECT (QuickSprunkStopEffect, "effect_quick_sprunk_stop", 0);