#include "util/EffectBase.h"
#include "util/GlobalRenderer.h"

template <RwV3d scale> class ObjectSizeEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        GlobalRenderer::RenderBuildingEvent += RenderBuilding;
        GlobalRenderer::RenderObjectEvent += RenderObject;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        GlobalRenderer::RenderBuildingEvent -= RenderBuilding;
        GlobalRenderer::RenderObjectEvent -= RenderObject;
    }

    static void
    RenderBuilding (CBuilding *building, RwFrame *frame)
    {
        RwFrameScale (frame, &scale, rwCOMBINEPRECONCAT);
    }

    static void
    RenderObject (CObject *object, RwFrame *frame)
    {
        RwFrameScale (frame, &scale, rwCOMBINEPRECONCAT);
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

using ObjectSizeFlatEffect = ObjectSizeEffect<RwV3d {1.0f, 1.0f, 0.01f}>;
DEFINE_EFFECT (ObjectSizeFlatEffect, "effect_object_size_flat", 0);
// clang-format on