#include <util/EffectBase.h>
#include <util/GameUtil.h>

#include <CTimer.h>

class InvertedGravityEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        // Set everyone's Z position a bit higher so gravity triggers
        for (CPed *ped : CPools::ms_pPedPool)
        {
            ped->GetPosition ().z += 0.1f;
            ped->m_vecMoveSpeed.z = 0;
        }

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            vehicle->GetPosition ().z += 0.1f;
            vehicle->m_vecMoveSpeed.z = 0;
        }

        for (CObject *object : CPools::ms_pObjectPool)
        {
            object->GetPosition ().z += 0.1f;
            object->m_vecMoveSpeed.z = 0;
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        GameUtil::SetVehiclesToRealPhysics ();

        for (CPed *ped : CPools::ms_pPedPool)
        {
            NegateGravity (ped);
            ApplyGravity (ped, -0.002f);
        }

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            NegateGravity (vehicle);
            ApplyGravity (vehicle, -0.002f);
        }

        for (CObject *object : CPools::ms_pObjectPool)
        {
            NegateGravity (object);
            ApplyGravity (object, -0.002f);
        }
    }

    void
    NegateGravity (CPhysical *physical)
    {
        float negativeGravity
            = CTimer::ms_fTimeStep * physical->m_fMass * -0.008f;
        physical->ApplyMoveForce ({0, 0, -negativeGravity});
    }

    void
    ApplyGravity (CPhysical *physical, float gravity)
    {
        float newGravity = CTimer::ms_fTimeStep * physical->m_fMass * -gravity;
        physical->ApplyMoveForce ({0, 0, newGravity});
    }
};

DEFINE_EFFECT (InvertedGravityEffect, "effect_inverted_gravity", GROUP_GRAVITY);