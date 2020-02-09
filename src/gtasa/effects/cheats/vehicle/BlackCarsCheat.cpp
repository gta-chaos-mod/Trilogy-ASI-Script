#include "BlackCarsCheat.h"

std::list<std::pair<RwRGBA *, RwRGBA>> BlackCarsCheat::resetMaterialColors = {};

// Custom events for CVehicle::SetupRender and CVehicle::ResetAfterRender
static ThiscallEvent<AddressList<0x5532A9, H_CALL>, PRIORITY_BEFORE,
                     ArgPickN<CVehicle *, 0>, void (CVehicle *)>
    setupRenderEvent;
static ThiscallEvent<AddressList<0x55332A, H_CALL>, PRIORITY_AFTER,
                     ArgPickN<CVehicle *, 0>, void (CVehicle *)>
    resetAfterRenderEvent;

BlackCarsCheat::BlackCarsCheat () : EffectBase ("cheat_black_cars")
{
    AddType ("vehicle_color");
    if (Config::GetOrDefault ("CrowdControl.Enabled", false))
    {
        AddType ("ghost_town");
    }
}

void
BlackCarsCheat::Enable ()
{
    EffectBase::Enable ();

    setupRenderEvent += SetupRenderEvent;
    resetAfterRenderEvent += ResetAfterRenderEvent;
}

void
BlackCarsCheat::Disable ()
{
    resetAfterRenderEvent -= ResetAfterRenderEvent;
    setupRenderEvent -= SetupRenderEvent;

    EffectBase::Disable ();
}

void
BlackCarsCheat::SetupRenderEvent (CVehicle *vehicle)
{
    ModifyCarPaint (vehicle);
}

void
BlackCarsCheat::ResetAfterRenderEvent (CVehicle *vehicle)
{
    // In case some material got added more than once, restore in reverse order
    for (auto it = resetMaterialColors.rbegin ();
         it != resetMaterialColors.rend (); ++it)
    {
        *it->first = it->second;
    }

    resetMaterialColors.clear ();
}

void
BlackCarsCheat::ModifyCarPaint (CVehicle *vehicle)
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
            AtomicCallback (reinterpret_cast<RpAtomic *> (vehicle->m_pRwObject),
                            vehicle);
        }
    }
}

RpMaterial *
BlackCarsCheat::MaterialCallback (RpMaterial *material, void *data)
{
    if (!data)
    {
        return material;
    }

    resetMaterialColors.push_back (
        std::make_pair (&material->color, material->color));

    material->color.red   = 5;
    material->color.green = 5;
    material->color.blue  = 5;

    return material;
}

RpAtomic *
BlackCarsCheat::AtomicCallback (RpAtomic *atomic, void *data)
{
    if (atomic->geometry)
    {
        atomic->geometry->flags |= rpGEOMETRYMODULATEMATERIALCOLOR;
        RpGeometryForAllMaterials (atomic->geometry, MaterialCallback, data);
    }
    return atomic;
}
