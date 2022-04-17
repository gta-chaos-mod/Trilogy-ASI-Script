#include <effects/OneTimeEffect.h>

class LaunchAllPedsEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();

        for (CPed *ped : CPools::ms_pPedPool)
        {
            if (ped == player)
            {
                continue;
            }

            ped->GetPosition ().z += 0.5f;
            ped->ApplyMoveForce ({0, 0, 200.0f});
        }
    }
};

DEFINE_EFFECT (LaunchAllPedsEffect, "effect_launch_all_peds", 0);