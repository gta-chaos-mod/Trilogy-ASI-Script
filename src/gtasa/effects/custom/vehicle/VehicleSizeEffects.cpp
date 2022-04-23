#include "util/EffectBase.h"

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

        // TODO: Translate vehicle so wheels touch ground
        // RwFrameTranslate (frame, &translation, rwCOMBINEPRECONCAT);
    }
};

// clang-format off
// Sizes / Scales
using VehicleSizeTinyCarsEffect = VehicleSizeEffect<RwV3d {0.5f, 0.5f, 0.5f}, RwV3d {0.0f, 0.0f, 0.0f}, 0.0f>;
DEFINE_EFFECT (VehicleSizeTinyCarsEffect, "effect_vehicle_size_tiny", 0);

using VehicleSizeLargeCarsEffect = VehicleSizeEffect<RwV3d {2.0f, 2.0f, 2.0f}, RwV3d {0.0f, 0.0f, 0.0f}, 0.0f>;
DEFINE_EFFECT (VehicleSizeLargeCarsEffect, "effect_vehicle_size_large", 0);

using VehicleSizeWideEffect = VehicleSizeEffect<RwV3d {2.0f, 1.0f, 1.0f}, RwV3d {0.0f, 0.0f, 0.0f}, 0.0f>;
DEFINE_EFFECT (VehicleSizeWideEffect, "effect_vehicle_size_wide", 0);

using VehicleSizeSuperWideEffect = VehicleSizeEffect<RwV3d {3.0f, 1.0f, 1.0f}, RwV3d {0.0f, 0.0f, 0.0f}, 0.0f>;
DEFINE_EFFECT (VehicleSizeSuperWideEffect, "effect_vehicle_size_super_wide", 0);

using VehicleSizeTallEffect = VehicleSizeEffect<RwV3d {1.0f, 1.0f, 2.0f}, RwV3d {0.0f, 0.0f, 0.0f}, 0.0f>;
DEFINE_EFFECT (VehicleSizeTallEffect, "effect_vehicle_size_tall", 0);

using VehicleSizeLongEffect = VehicleSizeEffect<RwV3d {1.0f, 2.0f, 1.0f}, RwV3d {0.0f, 0.0f, 0.0f}, 0.0f>;
DEFINE_EFFECT (VehicleSizeLongEffect, "effect_vehicle_size_long", 0);

using VehicleSizePaperThinEffect = VehicleSizeEffect<RwV3d {0.01f, 1.0f, 1.0f}, RwV3d {0.0f, 0.0f, 0.0f}, 0.0f>;
DEFINE_EFFECT (VehicleSizePaperThinEffect, "effect_vehicle_size_paper_thin", 0);

// Rotations
using VehicleSizeBackwardsEffect = VehicleSizeEffect<RwV3d {1.0f, 1.0f, 1.0f}, RwV3d {0.0f, 0.0f, 1.0f}, 180.0f>;
DEFINE_EFFECT (VehicleSizeBackwardsEffect, "effect_vehicle_size_backwards", 0);

using VehicleSizeFlippedEffect = VehicleSizeEffect<RwV3d {1.0f, 1.0f, 1.0f}, RwV3d {0.0f, 1.0f, 0.0f}, 180.0f>;
DEFINE_EFFECT (VehicleSizeFlippedEffect, "effect_vehicle_size_flipped", 0);
// clang-format on