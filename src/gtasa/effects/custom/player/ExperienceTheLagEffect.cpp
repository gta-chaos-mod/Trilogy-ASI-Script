#include "util/EffectBase.h"
#include "util/GenericUtil.h"
#include "util/Teleportation.h"

class ExperienceTheLagEffect : public EffectBase
{
    int wait = 0;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        wait = inst->Random (1000, 1000 * 2);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0) return;

        TeleportLag (inst);

        wait = inst->Random (1000, 1000 * 2);
    }

    void
    TeleportLag (EffectInstance *inst)
    {
        if (!Teleportation::CanTeleport ()) return;

        CEntity *entity = FindPlayerEntity (-1);
        if (!entity) return;

        float range = 2.0f;
        if (inst->Random (0, 4) == 0) range = 7.5f;

        CVector position = entity->GetPosition ()
                           + CVector (inst->Random (-range, range),
                                      inst->Random (-range, range), 0.0f);

        bool  worked = false;
        float newZ   = CWorld::FindGroundZFor3DCoord (position.x, position.y,
                                                      position.z + 10.0f, &worked,
                                                      nullptr);
        if (worked && newZ > position.z) position.z = newZ + 2.0f;

        entity->SetPosn (position);
    }
};

DEFINE_EFFECT (ExperienceTheLagEffect, "effect_experience_the_lag", 0);
