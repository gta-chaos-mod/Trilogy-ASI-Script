#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

using namespace plugin;

template <RwV3d scale, float zAdjustment = 0.0f>
class VehicleSizeEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK (inst, Hooked_FrameSyncDirty, signed int (), 0x7EF37C);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
            ScaleEntity (vehicle, false);
    }

    static void
    ScaleEntity (CEntity *entity, bool reset = false)
    {
        if (!IsEntityPointerValid (entity) || !entity->m_matrix
            || !entity->m_pRwObject)
            return;

        auto frame = GetObjectParent (entity->m_pRwObject);
        if (!frame) return;

        auto matrix = &frame->modelling;
        if (!matrix) return;

        if (reset)
        {
            entity->m_matrix->UpdateRW (&frame->modelling);

            entity->UpdateRwFrame ();
            return;
        }

        entity->m_matrix->CopyToRwMatrix (matrix);

        RwFrameScale (frame, &scale, rwCOMBINEPRECONCAT);

        entity->UpdateRwFrame ();
    }

    static signed int
    Hooked_FrameSyncDirty (auto &&cb)
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
            ScaleEntity (vehicle);

        return cb ();
    }
};

// clang-format off
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