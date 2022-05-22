#include "util/ColorHelper.h"
#include "util/EffectBase.h"
#include "util/GenericUtil.h"

using namespace plugin;

class RainbowPedsEffect : public EffectBase
{
    static inline float                                  hueShift = 0.0f;
    static inline std::list<std::pair<RwRGBA *, RwRGBA>> resetMaterialColors
        = {};

public:
    void
    OnStart (EffectInstance *inst) override
    {
        hueShift = 0.0f;
        resetMaterialColors.clear ();

        Events::pedRenderEvent.before += RenderPed;
        Events::pedRenderEvent.after += ResetPedRender;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::pedRenderEvent.before -= RenderPed;
        Events::pedRenderEvent.after -= ResetPedRender;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        hueShift += GenericUtil::CalculateTick (0.075f);
        hueShift = fmod (hueShift, 360.0f);
    }

    static void
    RenderPed (CPed *ped)
    {
        if (ped->m_pRwClump && ped->m_pRwClump->object.type == rpCLUMP)
        {
            RpClumpForAllAtomics (ped->m_pRwClump, AtomicCallback, 0);
            DeActivateDirectional ();
            SetFullAmbient ();
        }
    }

    static void
    ResetPedRender (CPed *ped)
    {
        for (auto &p : resetMaterialColors)
            *p.first = p.second;

        resetMaterialColors.clear ();
    }

    static RpAtomic *
    AtomicCallback (RpAtomic *atomic, void *data)
    {
        if (atomic->geometry)
        {
            atomic->geometry->flags |= rpGEOMETRYMODULATEMATERIALCOLOR;
            RpGeometryForAllMaterials (atomic->geometry, MaterialCallback, 0);
        }
        return atomic;
    }

    static RpMaterial *
    MaterialCallback (RpMaterial *material, void *data)
    {
        resetMaterialColors.push_back (
            std::make_pair (&material->color, material->color));

        int r = material->color.red;
        int g = material->color.green;
        int b = material->color.blue;
        ColorHelper::HueShift (r, g, b, hueShift, 0.9f);

        material->color.red   = r;
        material->color.green = g;
        material->color.blue  = b;

        return material;
    }
};

DEFINE_EFFECT (RainbowPedsEffect, "effect_rainbow_peds", 0);