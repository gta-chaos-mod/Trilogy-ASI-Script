#include "effects/OneTimeEffect.h"

#include <CStreaming.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

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

        CMatrix *matrix;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle)
            matrix = vehicle->GetMatrix ();
        else
            matrix = player->GetMatrix ();

        treeObject->SetMatrix (*matrix);
        treeObject->SetPosn (position);
        treeObject->m_nObjectType = OBJECT_MISSION;
    }
};

DEFINE_EFFECT (SpawnTreeEffect, "effect_spawn_tree", 0);