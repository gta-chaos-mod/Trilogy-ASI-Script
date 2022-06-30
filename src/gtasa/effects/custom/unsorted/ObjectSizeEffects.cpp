#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

using namespace plugin;

template <RwV3d scale> class ObjectSizeEffect : public EffectBase
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
        for (CObject *object : CPools::ms_pObjectPool)
            ScaleEntity (object, true);

        for (CBuilding *building : CPools::ms_pBuildingPool)
            ScaleEntity (building, true);
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
        for (CObject *object : CPools::ms_pObjectPool)
            ScaleEntity (object);

        for (CBuilding *building : CPools::ms_pBuildingPool)
            ScaleEntity (building);

        return cb ();
    }
};

// clang-format off
using ObjectSizeTinyCarsEffect = ObjectSizeEffect<RwV3d {0.5f, 0.5f, 0.5f}>;
DEFINE_EFFECT (ObjectSizeTinyCarsEffect, "effect_object_size_tiny", 0);

using ObjectSizeLargeCarsEffect = ObjectSizeEffect<RwV3d {2.0f, 2.0f, 2.0f}>;
DEFINE_EFFECT (ObjectSizeLargeCarsEffect, "effect_object_size_large", 0);

using ObjectSizeWideEffect = ObjectSizeEffect<RwV3d {2.0f, 1.0f, 1.0f}>;
DEFINE_EFFECT (ObjectSizeWideEffect, "effect_object_size_wide", 0);

using ObjectSizeSuperWideEffect = ObjectSizeEffect<RwV3d {3.0f, 1.0f, 1.0f}>;
DEFINE_EFFECT (ObjectSizeSuperWideEffect, "effect_object_size_super_wide", 0);

using ObjectSizeTallEffect = ObjectSizeEffect<RwV3d {1.0f, 1.0f, 2.0f}>;
DEFINE_EFFECT (ObjectSizeTallEffect, "effect_object_size_tall", 0);

using ObjectSizeLongEffect = ObjectSizeEffect<RwV3d {1.0f, 2.0f, 1.0f}>;
DEFINE_EFFECT (ObjectSizeLongEffect, "effect_object_size_long", 0);

using ObjectSizePaperThinEffect = ObjectSizeEffect<RwV3d {0.01f, 1.0f, 1.0f}>;
DEFINE_EFFECT (ObjectSizePaperThinEffect, "effect_object_size_paper_thin", 0);

using ObjectSizeFlatEffect = ObjectSizeEffect<RwV3d {1.00f, 1.0f, 0.01f}>;
DEFINE_EFFECT (ObjectSizeFlatEffect, "effect_object_size_flat", 0);
// clang-format on