#include "util/EffectBase.h"

using namespace plugin;

template <RwV3d scale, float zAdjustment = 0.0f>
class VehicleSizeEffect : public EffectBase
{
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
    RenderVehicleEvent (CVehicle *vehicle)
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        // Potential fix for boats flickering
        if (DistanceBetweenPoints (player->GetPosition (),
                                   vehicle->GetPosition ())
            > 200.0f)
            return;

        auto frame = GetObjectParent (vehicle->m_pRwObject);

        RwFrameScale (frame, &scale, rwCOMBINEPRECONCAT);

        RwV3d translation = {0.0f, 0.0f, zAdjustment};

        RwFrameTranslate (frame, &translation, rwCOMBINEPRECONCAT);
    }
};

// TODO: Fix boats flickering when low LOD - maybe a distance check to the
// player?

// clang-format off
// Sizes / Scales
using VehicleSizeTinyCarsEffect = VehicleSizeEffect<RwV3d {0.5f, 0.5f, 0.5f}, -0.3f>;
DEFINE_EFFECT (VehicleSizeTinyCarsEffect, "effect_vehicle_size_tiny", 0);

using VehicleSizeLargeCarsEffect = VehicleSizeEffect<RwV3d {2.0f, 2.0f, 2.0f}, 0.3f>;
DEFINE_EFFECT (VehicleSizeLargeCarsEffect, "effect_vehicle_size_large", 0);

using VehicleSizeWideEffect = VehicleSizeEffect<RwV3d {2.0f, 1.0f, 1.0f}>;
DEFINE_EFFECT (VehicleSizeWideEffect, "effect_vehicle_size_wide", 0);

using VehicleSizeSuperWideEffect = VehicleSizeEffect<RwV3d {3.0f, 1.0f, 1.0f}>;
DEFINE_EFFECT (VehicleSizeSuperWideEffect, "effect_vehicle_size_super_wide", 0);

using VehicleSizeTallEffect = VehicleSizeEffect<RwV3d {1.0f, 1.0f, 2.0f}, 0.3f>;
DEFINE_EFFECT (VehicleSizeTallEffect, "effect_vehicle_size_tall", 0);

using VehicleSizeLongEffect = VehicleSizeEffect<RwV3d {1.0f, 2.0f, 1.0f}>;
DEFINE_EFFECT (VehicleSizeLongEffect, "effect_vehicle_size_long", 0);

using VehicleSizePaperThinEffect = VehicleSizeEffect<RwV3d {0.01f, 1.0f, 1.0f}>;
DEFINE_EFFECT (VehicleSizePaperThinEffect, "effect_vehicle_size_paper_thin", 0);

using VehicleSizeFlatEffect = VehicleSizeEffect<RwV3d {1.00f, 1.0f, 0.01f}>;
DEFINE_EFFECT (VehicleSizeFlatEffect, "effect_vehicle_size_flat", 0);
// clang-format on