#include <util/EffectBase.h>
#include <util/GameUtil.h>

#include <CTimer.h>

class ZeroGravityEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        GameUtil::SetVehiclesToRealPhysics ();

        for (CPed *ped : CPools::ms_pPedPool)
            NegateGravity (ped);

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
            NegateGravity (vehicle);

        for (CObject *object : CPools::ms_pObjectPool)
            NegateGravity (object);
    }

    void
    NegateGravity (CPhysical *physical)
    {
        float negativeGravity
            = CTimer::ms_fTimeStep * physical->m_fMass * -0.008f;
        physical->ApplyMoveForce ({0, 0, -negativeGravity});
    }
};

DEFINE_EFFECT (ZeroGravityEffect, "effect_zero_gravity", GROUP_GRAVITY);