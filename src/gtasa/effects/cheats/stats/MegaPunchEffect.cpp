#include "effects/TimedAddressEffect.h"

#include <CCarCtrl.h>

using namespace plugin;

class MegaPunchEffect : public TimedAddressEffect
{
public:
    MegaPunchEffect () : TimedAddressEffect (0x969173) {}

    void
    OnStart (EffectInstance *inst) override
    {
        for (int address : {0x624577, 0x66412C})
        {
            injector::MakeCALL (address, Hooked_Fight_HitCar);
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        // TODO: Unhook
    }

    static void __fastcall Hooked_Fight_HitCar (
        CTaskSimpleFight *thisTask, void *edx, CPed *ped, CVehicle *vehicle,
        CVector *colCoord, CVector *colDir, int colComp, int a7)
    {
        float angle = ped->GetHeading ();

        CCarCtrl::SwitchVehicleToRealPhysics (vehicle);
        vehicle->m_vecMoveSpeed.x = 2.5f * -sin (angle);
        vehicle->m_vecMoveSpeed.y = 2.5f * cos (angle);
        vehicle->m_vecMoveSpeed.z = 0;

        CallMethod<0x61D0B0, CTaskSimpleFight *> (thisTask, ped, vehicle,
                                                  colCoord, colDir, colComp,
                                                  a7);
    }
};

DEFINE_EFFECT (MegaPunchEffect, "effect_mega_punch", 0);