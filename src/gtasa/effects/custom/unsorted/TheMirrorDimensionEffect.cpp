#include "util/EffectBase.h"
#include "util/GlobalRenderer.h"

class TheMirrorDimensionEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        GlobalRenderer::RenderBuildingEvent += RenderBuilding;
        GlobalRenderer::RenderObjectEvent += RenderObject;
        GlobalRenderer::RenderVehicleEvent += RenderVehicle;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        GlobalRenderer::RenderBuildingEvent -= RenderBuilding;
        GlobalRenderer::RenderObjectEvent -= RenderObject;
        GlobalRenderer::RenderVehicleEvent -= RenderVehicle;
    }

    static void
    RenderBuilding (CBuilding *building, RwFrame *frame)
    {
        RenderFrame (building->GetPosition (), frame);
    }

    static void
    RenderObject (CObject *object, RwFrame *frame)
    {
        RenderFrame (object->GetPosition (), frame);
    }

    static void
    RenderVehicle (CVehicle *vehicle, RwFrame *frame)
    {
        RenderFrame (vehicle->GetPosition (), frame);
    }

    static void
    RenderFrame (CVector position, RwFrame *frame)
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CVector playerPosition = player->GetPosition ();

        float offsetX = fmod (playerPosition.x - position.x, 360.0f);
        float offsetY = fmod (playerPosition.y - position.y, 360.0f);
        float offsetZ = fmod (playerPosition.z - position.z, 360.0f);

        // X Axis
        RwV3d rotation = {1.0f, 0.0f, 0.0f};
        RwFrameRotate (frame, &rotation, offsetX, rwCOMBINEPRECONCAT);

        // Y Axis
        rotation = {0.0f, 1.0f, 0.0f};
        RwFrameRotate (frame, &rotation, offsetY, rwCOMBINEPRECONCAT);

        // Z Axis
        rotation = {0.0f, 0.0f, 1.0f};
        RwFrameRotate (frame, &rotation, offsetZ, rwCOMBINEPRECONCAT);
    }
};

DEFINE_EFFECT (TheMirrorDimensionEffect, "effect_the_mirror_dimension", 0);