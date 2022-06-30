#include "effects/OneTimeEffect.h"

#include <CStreaming.h>
#include <CTimer.h>
#include <CWorld.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class SpawnTableEffect : public OneTimeEffect
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

        position.z -= 0.5f;

        CObject *tableObject;

        int model = 2115; // Table
        CStreaming::RequestModel (model, 2);
        CStreaming::LoadAllRequestedModels (false);
        Command<eScriptCommands::COMMAND_CREATE_OBJECT> (model, position.x,
                                                         position.y, position.z,
                                                         &tableObject);
        CStreaming::SetModelIsDeletable (model);

        CMatrix *matrix;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle)
            matrix = vehicle->GetMatrix ();
        else
            matrix = player->GetMatrix ();

        tableObject->SetMatrix (*matrix);
        tableObject->SetPosn (position);
        tableObject->m_nPhysicalFlags.bCollisionProof = true;
        tableObject->m_nObjectType                    = OBJECT_TEMPORARY;
        tableObject->m_dwRemovalTime
            = CTimer::m_snTimeInMilliseconds + 1000 * 5;
    }
};

DEFINE_EFFECT (SpawnTableEffect, "effect_spawn_table", 0);