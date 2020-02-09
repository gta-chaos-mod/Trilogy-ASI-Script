#include "RainbowCarsEffect.h"

float                                  RainbowCarsEffect::hueShift = 0.0f;
std::list<std::pair<RwRGBA *, RwRGBA>> RainbowCarsEffect::resetMaterialColors
    = {};

// Custom events for CVehicle::SetupRender and CVehicle::ResetAfterRender
// TODO: Figure out addresses for Vice City
static ThiscallEvent<AddressList<-1, H_CALL>, PRIORITY_BEFORE,
                     ArgPickN<CVehicle *, 0>, void (CVehicle *)>
    setupRenderEvent;
static ThiscallEvent<AddressList<-1, H_CALL>, PRIORITY_AFTER,
                     ArgPickN<CVehicle *, 0>, void (CVehicle *)>
    resetAfterRenderEvent;

RainbowCarsEffect::RainbowCarsEffect () : EffectBase ("effect_rainbow_cars") {}

void
RainbowCarsEffect::Enable ()
{
    EffectBase::Enable ();

    setupRenderEvent += SetupRenderEvent;
    resetAfterRenderEvent += ResetAfterRenderEvent;
}

void
RainbowCarsEffect::Disable ()
{
    resetAfterRenderEvent -= ResetAfterRenderEvent;
    setupRenderEvent -= SetupRenderEvent;

    EffectBase::Disable ();
}

void
RainbowCarsEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    hueShift += CalculateTick (0.075f);
    if (hueShift > 360.0f)
    {
        hueShift -= 360.0f;
    }
}

void
RainbowCarsEffect::SetupRenderEvent (CVehicle *vehicle)
{
    ModifyCarPaint (vehicle);
}

void
RainbowCarsEffect::ResetAfterRenderEvent (CVehicle *vehicle)
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
RainbowCarsEffect::ModifyCarPaint (CVehicle *vehicle)
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
RainbowCarsEffect::MaterialCallback (RpMaterial *material, void *data)
{
    if (!data)
    {
        return material;
    }

    CVehicle *vehicle = reinterpret_cast<CVehicle *> (data);

    resetMaterialColors.push_back (
        std::make_pair (&material->color, material->color));

    CVehicleModelInfo *vehModel = reinterpret_cast<CVehicleModelInfo *> (
        CModelInfo::ms_modelInfoPtrs[vehicle->m_nModelIndex]);
    CRGBA color = vehModel->m_anPrimaryColors[vehicle->m_nPrimaryColor];

    int r = color.r;
    int g = color.g;
    int b = color.b;
    ColorHelper::HueShift (r, g, b, hueShift, 0.9f);

    material->color.red   = r;
    material->color.green = g;
    material->color.blue  = b;

    return material;
}

RpAtomic *
RainbowCarsEffect::AtomicCallback (RpAtomic *atomic, void *data)
{
    if (atomic->geometry)
    {
        atomic->geometry->flags |= rpGEOMETRYMODULATEMATERIALCOLOR;
        RpGeometryForAllMaterials (atomic->geometry, MaterialCallback, data);
    }
    return atomic;
}
