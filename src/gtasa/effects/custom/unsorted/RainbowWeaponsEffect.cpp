#include "util/ColorHelper.h"
#include "util/EffectBase.h"
#include "util/GenericUtil.h"

using namespace plugin;

// TODO: The hooks are not working correctly?
// Also check if the object is a weapon model and not just *any* object
class RainbowWeaponsEffect : public EffectBase
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

        Events::objectRenderEvent.before += RenderObject;
        Events::objectRenderEvent.after += ResetObjectRender;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Events::objectRenderEvent.before -= RenderObject;
        Events::objectRenderEvent.after -= ResetObjectRender;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        hueShift += GenericUtil::CalculateTick (0.075f);
        hueShift = fmod (hueShift, 360.0f);
    }

    static void
    RenderObject (CObject *object)
    {
        if (object->m_pRwObject)
        {
            if (object->m_pRwObject->type == rpCLUMP)
                RpClumpForAllAtomics (reinterpret_cast<RpClump *> (
                                          object->m_pRwObject),
                                      AtomicCallback, 0);
            else
                AtomicCallback (reinterpret_cast<RpAtomic *> (
                                    object->m_pRwObject),
                                0);
        }
    }

    static void
    ResetObjectRender (CObject *object)
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

DEFINE_EFFECT (RainbowWeaponsEffect, "effect_rainbow_weapons", 0);