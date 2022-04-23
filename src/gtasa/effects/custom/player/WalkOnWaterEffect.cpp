#include <util/EffectBase.h>

#include <CStreaming.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class WalkOnWaterEffect : public EffectBase
{
    CObject *roadObject;

public:
    void
    OnEnd (EffectInstance *inst) override
    {
        if (roadObject && IsObjectPointerValid (roadObject))
            roadObject->Remove ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CVector position = player->GetPosition ();
            if (position.z < 1.0f && position.z > -5.0f)
                player->SetPosn (position.x, position.y, 1.0f);

            float     heading = player->m_fCurrentRotation;
            CVehicle *vehicle = FindPlayerVehicle (-1, false);
            if (vehicle) heading = vehicle->GetHeading ();

            if (!roadObject || !IsObjectPointerValid (roadObject))
            {
                // TODO: Find better object that is bigger so we don't have to
                // teleport it as often?
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
                // TODO: Fix CJ sliding on the constantly teleporting object?
                roadObject->Teleport ({position.x, position.y, 0.5f}, false);
                roadObject->SetOrientation (0.0f, 0.0f, heading);
            }
        }
    }
};

DEFINE_EFFECT (WalkOnWaterEffect, "effect_walk_on_water", 0);