#include <util/EffectBase.h>
#include <util/GameUtil.h>

class ZeroGravityEffect : public EffectBase
{
public:
    void
    OnEnd (EffectInstance *inst) override
    {
        for (CPed *ped : CPools::ms_pPedPool)
        {
            ped->m_nPhysicalFlags.bApplyGravity = true;
        }

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            vehicle->m_nPhysicalFlags.bApplyGravity = true;
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        GameUtil::SetVehiclesToRealPhysics ();

        for (CPed *ped : CPools::ms_pPedPool)
        {
            ped->m_nPhysicalFlags.bApplyGravity = false;
        }

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            vehicle->m_nPhysicalFlags.bApplyGravity = false;
        }
    }
};

DEFINE_EFFECT (ZeroGravityEffect, "effect_zero_gravity", GROUP_GRAVITY);