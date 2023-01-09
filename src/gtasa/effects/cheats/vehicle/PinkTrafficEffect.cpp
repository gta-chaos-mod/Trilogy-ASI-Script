#include "util/EffectBase.h"

#include <deque>

using namespace plugin;

class PinkTrafficEffect : public EffectBase
{
    // Custom events for CVehicle::SetupRender and CVehicle::ResetAfterRender
    static inline ThiscallEvent<AddressList<0x5532A9, H_CALL>, PRIORITY_BEFORE,
                                ArgPickN<CVehicle *, 0>, void (CVehicle *)>
        setupRenderEvent;
    static inline ThiscallEvent<AddressList<0x55332A, H_CALL>, PRIORITY_AFTER,
                                ArgPickN<CVehicle *, 0>, void (CVehicle *)>
        resetAfterRenderEvent;

    static inline std::deque<std::pair<RwRGBA *, RwRGBA>> resetMaterialColors
        = {};

public:
    void
    OnStart (EffectInstance *inst) override
    {
        resetMaterialColors.clear ();

        setupRenderEvent += SetupRenderEvent;
        resetAfterRenderEvent += ResetAfterRenderEvent;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        for (auto const &[color, backupColor] : resetMaterialColors)
            *color = backupColor;

        resetMaterialColors.clear ();

        resetAfterRenderEvent -= ResetAfterRenderEvent;
        setupRenderEvent -= SetupRenderEvent;
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
        for (auto const &[color, backupColor] : resetMaterialColors)
            *color = backupColor;

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
        if (!data) return material;

        resetMaterialColors.push_front (
            std::make_pair (&material->color, material->color));

        material->color.red   = 236;
        material->color.green = 106;
        material->color.blue  = 174;

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

DEFINE_EFFECT (PinkTrafficEffect, "effect_pink_traffic", GROUP_VEHICLE_COLOR);