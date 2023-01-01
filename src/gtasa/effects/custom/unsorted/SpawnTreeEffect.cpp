#include "effects/OneTimeEffect.h"

#include <CStreaming.h>
#include <CTimer.h>
#include <CWorld.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

// TODO: Randomize trees?

class SpawnTreeEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CVector position
            = player->TransformFromObjectSpace (CVector (0.0f, 10.0f, -1.0f));

        CObject *treeObject;

        int model = 708; // Tree
        CStreaming::RequestModel (model, 2);
        CStreaming::LoadAllRequestedModels (false);
        Command<eScriptCommands::COMMAND_CREATE_OBJECT> (model, position.x,
                                                         position.y, position.z,
                                                         &treeObject);
        CStreaming::SetModelIsDeletable (model);

        bool  worked = false;
        float newZ   = CWorld::FindGroundZFor3DCoord (position.x, position.y,
                                                      position.z + 10.0f, &worked,
                                                      nullptr);
        if (worked && newZ > position.z) position.z = newZ;

        CMatrix *matrix;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle)
            matrix = vehicle->GetMatrix ();
        else
            matrix = player->GetMatrix ();

        treeObject->SetMatrix (*matrix);
        treeObject->SetPosn (position);
        treeObject->m_nObjectType = OBJECT_TEMPORARY;
        treeObject->m_dwRemovalTime
            = CTimer::m_snTimeInMilliseconds + (1000 * 60 * 30);
        treeObject->m_nColDamageEffect                    = 0x14;
        treeObject->m_pObjectInfo->m_fColDamageMultiplier = 0.5f;
    }
};

DEFINE_EFFECT (SpawnTreeEffect, "effect_spawn_tree", 0);