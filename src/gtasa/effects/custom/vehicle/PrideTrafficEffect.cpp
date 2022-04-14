#include <util/ColorHelper.h>
#include <util/EffectBase.h>
#include <util/GenericUtil.h>

#include <utility>

using namespace plugin;

// Custom events for CVehicle::SetupRender and CVehicle::ResetAfterRender
static ThiscallEvent<AddressList<0x5532A9, H_CALL>, PRIORITY_BEFORE,
                     ArgPickN<CVehicle *, 0>, void (CVehicle *)>
    setupRenderEvent;
static ThiscallEvent<AddressList<0x55332A, H_CALL>, PRIORITY_AFTER,
                     ArgPickN<CVehicle *, 0>, void (CVehicle *)>
    resetAfterRenderEvent;

class PrideTrafficEffect : public EffectBase
{
    static inline float                                  hueShift = 0.0f;
    static inline std::list<std::pair<RwRGBA *, RwRGBA>> resetMaterialColors
        = {};

public:
    void
    OnStart (EffectInstance *inst) override
    {
        setupRenderEvent += SetupRenderEvent;
        resetAfterRenderEvent += ResetAfterRenderEvent;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        resetAfterRenderEvent -= ResetAfterRenderEvent;
        setupRenderEvent -= SetupRenderEvent;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        hueShift += GenericUtil::CalculateTick (0.075f);
        if (hueShift > 360.0f)
        {
            hueShift -= 360.0f;
        }
    }

    static void
    SetupRenderEvent (CVehicle *vehicle)
    {
        ModifyCarPaint (vehicle);
    }

    static void
    ResetAfterRenderEvent (CVehicle *vehicle)
    {
        // In case some material got added more than once, restore in reverse
        // order
        for (auto it = resetMaterialColors.rbegin ();
             it != resetMaterialColors.rend (); ++it)
        {
            *it->first = it->second;
        }

        resetMaterialColors.clear ();
    }

    static void
    ModifyCarPaint (CVehicle *vehicle)
    {
        if (vehicle->m_pRwObject)
        {
            if (vehicle->m_pRwObject->type == rpCLUMP)
            {
                RpClumpForAllAtomics (reinterpret_cast<RpClump *> (
                                          vehicle->m_pRwObject),
                                      AtomicCallback, vehicle);
            }
            else
            {
                AtomicCallback (reinterpret_cast<RpAtomic *> (
                                    vehicle->m_pRwObject),
                                vehicle);
            }
        }
    }

    static RpMaterial *
    MaterialCallback (RpMaterial *material, void *data)
    {
        if (!data)
        {
            return material;
        }

        CVehicle *vehicle = reinterpret_cast<CVehicle *> (data);

        resetMaterialColors.push_back (
            std::make_pair (&material->color, material->color));

        CRGBA color
            = CVehicleModelInfo::ms_vehicleColourTable[vehicle
                                                           ->m_nPrimaryColor];

        int r = color.r;
        int g = color.g;
        int b = color.b;
        ColorHelper::HueShift (r, g, b, hueShift, 0.9f);

        material->color.red   = r;
        material->color.green = g;
        material->color.blue  = b;

        return material;
    }

    static RpAtomic *
    AtomicCallback (RpAtomic *atomic, void *data)
    {
        if (atomic->geometry)
        {
            atomic->geometry->flags |= rpGEOMETRYMODULATEMATERIALCOLOR;
            RpGeometryForAllMaterials (atomic->geometry, MaterialCallback,
                                       data);
        }
        return atomic;
    }
};

DEFINE_EFFECT (PrideTrafficEffect, "effect_pride_traffic", GROUP_VEHICLE_COLOR);