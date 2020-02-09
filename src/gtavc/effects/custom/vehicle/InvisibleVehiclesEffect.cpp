#include "InvisibleVehiclesEffect.h"

InvisibleVehiclesEffect::InvisibleVehiclesEffect ()
    : EffectBase ("effect_invisible_vehicles")
{
    AddType ("invisible_vehicles");
}

void
InvisibleVehiclesEffect::InitializeHooks ()
{
    EffectBase::InitializeHooks ();

    HookCall (0x589AB2, HookedCAutomobileRender); // Automobile
    HookCall (0x60AD83, HookedCBikeRender);       // Bike
    HookJump (0x5B2580, HookedCPlaneRender);      // Plane
    HookCall (0x5AF2BE, HookedCHeliRender);       // Heli

    for (int address : {0x5A5403, 0x5A5527})
    {
        HookCall (address, HookedRwIm3DTransform); // Boat
    }
}

void __fastcall InvisibleVehiclesEffect::HookedCAutomobileRender (
    CAutomobile *thisAutomobile)
{
}

void __fastcall InvisibleVehiclesEffect::HookedCBikeRender (CBike *thisBike) {}

void __fastcall InvisibleVehiclesEffect::HookedCPlaneRender (CPlane *thisPlane)
{
}

void __fastcall InvisibleVehiclesEffect::HookedCHeliRender (CHeli *thisHeli) {}

uint8_t *
InvisibleVehiclesEffect::HookedRwIm3DTransform (uint8_t *    pVerts,
                                                signed int   numVerts,
                                                RwMatrix *   ltm,
                                                unsigned int flags)
{
    return nullptr;
}
