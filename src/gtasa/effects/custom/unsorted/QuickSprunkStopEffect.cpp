#include "util/EffectBase.h"

#include <CStreaming.h>
#include <CWorld.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class QuickSprunkStopEffect : public EffectBase
{
    CObject *sprunkObject;

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
                          + 2.0f;

        if (groundResult) position.z = groundPos;

        int model = 1775; // Sprunk Machine
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
        sprunkObject->m_nObjectType = OBJECT_MISSION2;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        if (sprunkObject && IsObjectPointerValid (sprunkObject))
            sprunkObject->Remove ();
    }
};

DEFINE_EFFECT (QuickSprunkStopEffect, "effect_quick_sprunk_stop", 0);