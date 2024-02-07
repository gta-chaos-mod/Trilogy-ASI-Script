#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

class BumperPedsEffect : public EffectBase
{
private:
    static inline std::array<float, 5> zFactor
        = {0.2f, 0.15f, 0.25f, 0.15f, 0.3f};
    static inline unsigned int idx = 0;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD_ARGS (inst, Hooked_CPed_KillPedWithCar,
                          void (CPed *, CVehicle *, float, bool), 0x54C5CC,
                          0x54C642, 0x60461F, 0x60491B, 0x604A0D);
        idx = 0;
    }

    static void
    Hooked_CPed_KillPedWithCar (auto &&cb, CPed *thisPed, CVehicle *car,
                                float arg1, bool arg2)
    {
        if (car && (thisPed != FindPlayerPed ()))
        {
            auto diff = car->GetPosition () - thisPed->GetPosition ();
            diff.Normalise ();

            float pushFactor = 0.25f;
            if (CModelInfo::IsVehicleModelType (car->m_nModelIndex)
                != VEHICLE_AUTOMOBILE)
            {
                pushFactor *= 0.5f;
            }

            car->m_vecMoveSpeed.x
                = std::clamp (diff.x, -pushFactor, pushFactor);
            car->m_vecMoveSpeed.y
                = std::clamp (diff.y, -pushFactor, pushFactor);
            car->m_vecMoveSpeed.z = zFactor[idx++ % zFactor.size ()];

            return;
        }

        cb ();
    }
};

DEFINE_EFFECT (BumperPedsEffect, "effect_bumper_peds",
               GROUP_GRAVITY | GROUP_HANDLING);
