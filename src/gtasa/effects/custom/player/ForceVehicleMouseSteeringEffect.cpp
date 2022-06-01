#include "util/EffectBase.h"

#include <CMenuSystem.h>

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
            inst->WriteMemory<bool *> (address, &overrideMouseSteering);
        }
    }

    void
    OnProcessScripts (EffectInstance *inst) override
    {
        if (CMenuSystem::num_menus_in_use) return;

        if (!FindPlayerVehicle (-1, false)) return;

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad)
            {
                pad->NewState.LeftStickX = 0;
                pad->NewState.LeftStickY = 0;
            }
        }
    }
};

DEFINE_EFFECT (ForceVehicleMouseSteeringEffect,
               "effect_force_vehicle_mouse_steering", GROUP_CONTROLS);