#include "MegaPunchCheat.h"

MegaPunchCheat::MegaPunchCheat ()
    : TimedAddressEffect ("cheat_mega_punch", 0x969173)
{
}

void
MegaPunchCheat::InitializeHooks ()
{
    TimedAddressEffect::InitializeHooks ();

    for (int address : {0x624577, 0x66412C})
    {
        HookCall (address, HookedFightHitCar);
    }
}

void __fastcall MegaPunchCheat::HookedFightHitCar (
    CTaskSimpleFight *thisTask, void *edx, CPed *ped, CVehicle *vehicle,
    CVector *colCoord, CVector *colDir, int colComp, int a7)
{
    float angle = ped->GetHeading ();

    CCarCtrl::SwitchVehicleToRealPhysics (vehicle);
    vehicle->m_vecMoveSpeed.x = 2.5f * -sin (angle);
    vehicle->m_vecMoveSpeed.y = 2.5f * cos (angle);
    vehicle->m_vecMoveSpeed.z = 0;

    CallMethod<0x61D0B0, CTaskSimpleFight *> (thisTask, ped, vehicle, colCoord,
                                              colDir, colComp, a7);
}
