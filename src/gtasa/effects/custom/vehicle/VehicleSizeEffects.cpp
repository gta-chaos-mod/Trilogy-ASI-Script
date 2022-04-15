#include <util/EffectBase.h>

using namespace plugin;

template <RwV3d scale, RwV3d rotation, float angle>
class VehicleSizeEffect : public EffectBase
{
    inline static float rotationAngle = angle;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        Events::vehicleRenderEvent += RenderVehicleEvent;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::vehicleRenderEvent -= RenderVehicleEvent;
    }

    static void
    SetRotationAngle (float angle)
    {
        rotationAngle = angle;
    }

    static float
    GetRotationAngle ()
    {
        return rotationAngle;
    }

    static void
    RenderVehicleEvent (CVehicle *vehicle)
    {
        auto frame = GetObjectParent (vehicle->m_pRwObject);

        RwFrameScale (frame, &scale, rwCOMBINEPRECONCAT);
        RwFrameRotate (frame, &rotation, GetRotationAngle (),
                       rwCOMBINEPRECONCAT);
    }
};

template <RwV3d scale, RwV3d rotation>
class VehicleSizeContinuousRotation
    : public VehicleSizeEffect<scale, rotation, 360.0f>
{
    using Base = VehicleSizeEffect<scale, rotation, 360.0f>;

public:
    void
    OnTick (EffectInstance *inst) override
    {
        Base::SetRotationAngle (
            fmod (Base::GetRotationAngle () + 30.0f, 360.0f));
    }
};

// clang-format off
using VehicleSizeBackwardsEffect = VehicleSizeEffect<RwV3d {1.0f, 1.0f, 1.0f}, RwV3d {0.0f, 0.0f, 1.0f}, 180.0f>;
DEFINE_EFFECT (VehicleSizeBackwardsEffect, "effect_vehicle_size_backwards", 0);

using VehicleSizeWideEffect = VehicleSizeEffect<RwV3d {2.0f, 1.0f, 1.0f}, RwV3d {0.0f, 0.0f, 0.0f}, 0.0f>;
DEFINE_EFFECT (VehicleSizeWideEffect, "effect_vehicle_size_wide", 0);

using VehicleSizeFlippedEffect = VehicleSizeEffect<RwV3d {1.0f, 1.0f, 1.0f}, RwV3d {0.0f, 1.0f, 0.0f}, 180.0f>;
DEFINE_EFFECT (VehicleSizeFlippedEffect, "effect_vehicle_size_flipped", 0);

using VehicleSizePaperThinEffect = VehicleSizeEffect<RwV3d {0.01f, 1.0f, 1.0f}, RwV3d {0.0f, 0.0f, 0.0f}, 0.0f>;
DEFINE_EFFECT (VehicleSizePaperThinEffect, "effect_vehicle_size_paper_thin", 0);
// clang-format on