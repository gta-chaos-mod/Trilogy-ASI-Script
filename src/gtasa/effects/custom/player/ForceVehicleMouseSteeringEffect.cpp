#include "util/EffectBase.h"

using namespace plugin;

class ForceVehicleMouseSteeringEffect : public EffectBase
{
    static inline bool overrideMouseSteering = true;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        for (int address :
             {0x52565D + 2, // Mouse Steering
              0x6AD7AC + 1, 0x6BE39C + 1, 0x6CE03D + 1, 0x6F0AFA + 1,

              0x525665 + 2, // Mouse Flying
              0x6C4880 + 1, 0x6CAE07 + 1})
        {
            injector::WriteMemory<bool *> (address, &overrideMouseSteering);
        }

        for (int address : {0x6CE1BC, 0x6CE118, 0x6C4A5A, 0x6CB095, 0x6CAF56})
        {
            injector::MakeCALL (address, Hooked_CPad_GetPadSteeringUpDown);
        }

        for (int address : {0x6AD907, 0x6AD846, 0x6BE5D9, 0x6BE488, 0x6F0C3C,
                            0x6C4A78, 0x6CB04F, 0x6CAF0F})
        {
            injector::MakeCALL (address, Hooked_CPad_GetPadSteeringLeftRight);
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        // TODO: Unhook

        for (int address :
             {0x52565D + 2, // Mouse Steering
              0x6AD7AC + 1, 0x6BE39C + 1, 0x6CE03D + 1, 0x6F0AFA + 1})
        {
            injector::WriteMemory<bool *> (address,
                                           &CVehicle::m_bEnableMouseSteering);
        }

        for (int address : {0x525665 + 2, // Mouse Flying
                            0x6C4880 + 1, 0x6CAE07 + 1})
        {
            injector::WriteMemory<bool *> (address,
                                           &CVehicle::m_bEnableMouseFlying);
        }
    }

    static __int16 __fastcall Hooked_CPad_GetPadSteeringUpDown (CPad *thisPad)
    {
        return 0;
    }

    static __int16 __fastcall Hooked_CPad_GetPadSteeringLeftRight (
        CPad *thisPad)
    {
        return 0;
    }
};

DEFINE_EFFECT (ForceVehicleMouseSteeringEffect,
               "effect_force_vehicle_mouse_steering", GROUP_CONTROLS);