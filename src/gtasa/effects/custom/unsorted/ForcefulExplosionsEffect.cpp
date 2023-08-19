#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

class ForcefulExplosionsEffect : public EffectBase
{
    static inline bool                    applyForce = false;
    static inline std::array<CVector, 32> vectors;
    static inline unsigned int            idx = 0;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        applyForce = false;

        HOOK_ARGS (inst, Hooked_CWorld_TriggerExplosion,
                   void (CVector *, float, float, CEntity *, CEntity *, bool,
                         float),
                   0x7374DA);

        HOOK_METHOD_ARGS (inst, Hooked_CPhysical_ApplyForce,
                          void (CPhysical *, CVector, CVector, bool), 0x542B50);

        HOOK_METHOD_ARGS (inst, Hooked_CPhysical_ApplyMoveForce,
                          void (CPhysical *, CVector), 0x5429F0);
        for (auto &v : vectors)
        {
            v.x = inst->Random (-0.5f, 0.5f);
            v.y = inst->Random (-0.5f, 0.5f);
            v.z = inst->Random (-0.5f, 0.5f);
        }
        idx = 0;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        for (auto &v : vectors)
        {
            v.x = inst->Random (-0.5f, 0.5f);
            v.y = inst->Random (-0.5f, 0.5f);
            v.z = inst->Random (-0.5f, 0.5f);
        }
    }

    static void
    Hooked_CPhysical_ApplyMoveForce (auto &&cb, CPhysical *thisPhys,
                                     CVector force)
    {
        cb ();

        // peds
        if (thisPhys && applyForce)
        {
            thisPhys->m_vecMoveSpeed += vectors[idx++ % vectors.size ()] * 2.0f;

            thisPhys->m_vecMoveSpeed.x
                = std::clamp (thisPhys->m_vecMoveSpeed.x, -2.0f, 2.0f);
            thisPhys->m_vecMoveSpeed.y
                = std::clamp (thisPhys->m_vecMoveSpeed.y, -2.0f, 2.0f);
        }
    }

    static void
    Hooked_CPhysical_ApplyForce (auto &&cb, CPhysical *thisPhys, CVector dir,
                                 CVector velocity, bool flag)
    {
        cb ();

        // vehicles
        if (thisPhys && applyForce)
        {
            thisPhys->m_vecMoveSpeed += vectors[idx++ % vectors.size ()];

            thisPhys->m_vecMoveSpeed.x
                = std::clamp (thisPhys->m_vecMoveSpeed.x, -2.0f, 2.0f);
            thisPhys->m_vecMoveSpeed.y
                = std::clamp (thisPhys->m_vecMoveSpeed.y, -2.0f, 2.0f);
        }
    }

    static void
    Hooked_CWorld_TriggerExplosion (auto &&cb, CVector *point, float radius,
                                    float visibleDistance, CEntity *victim,
                                    CEntity *creator, bool a7, float &damage)
    {
        applyForce = true;
        cb ();
        applyForce = false;
    }
};

DEFINE_EFFECT (ForcefulExplosionsEffect, "effect_forceful_explosions",
               GROUP_GRAVITY);
