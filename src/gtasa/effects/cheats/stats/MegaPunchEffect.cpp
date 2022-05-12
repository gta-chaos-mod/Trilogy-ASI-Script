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
        HOOK_METHOD_ARGS (inst, Hooked_Fight_HitCar,
                          void (CTaskSimpleFight *, CPed *, CVehicle *,
                                CVector *, CVector *, int, int),
                          0x624577, 0x66412C);
    }

    static void
    Hooked_Fight_HitCar (auto &&Fight_HitCar, CTaskSimpleFight *thisTask,
                         CPed *ped, CVehicle *vehicle, CVector *colCoord,
                         CVector *colDir, int colComp, int a7)
    {
        float angle = ped->GetHeading ();

        CCarCtrl::SwitchVehicleToRealPhysics (vehicle);
        vehicle->m_vecMoveSpeed.x = 2.5f * -sin (angle);
        vehicle->m_vecMoveSpeed.y = 2.5f * cos (angle);
        vehicle->m_vecMoveSpeed.z = 0;

        Fight_HitCar ();
    }
};

DEFINE_EFFECT (MegaPunchEffect, "effect_mega_punch", 0);