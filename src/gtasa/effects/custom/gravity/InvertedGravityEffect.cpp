#include <util/EffectBase.h>
#include <util/GameUtil.h>

class InvertedGravityEffect : public EffectBase
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

            ped->m_vecMoveSpeed.z
                = std::min (ped->m_vecMoveSpeed.z + 0.001f, 1.0f);
        }

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            vehicle->m_nPhysicalFlags.bApplyGravity = false;

            vehicle->m_vecMoveSpeed.z
                = std::min (vehicle->m_vecMoveSpeed.z + 0.001f, 1.0f);
        }
    }
};

DEFINE_EFFECT (InvertedGravityEffect, "effect_inverted_gravity", GROUP_GRAVITY);