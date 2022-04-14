#include <util/EffectBase.h>
#include <util/GameUtil.h>

class HonkBoostEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        GameUtil::SetVehiclesToRealPhysics ();

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            if (vehicle->m_nHornCounter > 0)
            {
                float heading = vehicle->GetHeading ();
                // TODO: 3D heading and boost? - simulating "Flying Cars" when
                // holding horn

                vehicle->m_vecMoveSpeed.x = std::min (
                    std::max (-5.0f, vehicle->m_vecMoveSpeed.x * 1.025f), 5.0f);
                vehicle->m_vecMoveSpeed.y = std::min (
                    std::max (-5.0f, vehicle->m_vecMoveSpeed.y * 1.025f), 5.0f);
                vehicle->m_vecMoveSpeed.z = std::min (
                    std::max (-5.0f, vehicle->m_vecMoveSpeed.z * 1.025f), 5.0f);
            }
        }
    }
};

DEFINE_EFFECT (HonkBoostEffect, "effect_honk_boost", 0);