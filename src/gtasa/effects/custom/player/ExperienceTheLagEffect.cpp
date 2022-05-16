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
        wait = inst->Random (250, 500);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0) return;

        TeleportLag (inst);

        wait = inst->Random (250, 500);
    }

    void
    TeleportLag (EffectInstance *inst)
    {
        if (Teleportation::CanTeleport ())
        {
            CEntity *entity = FindPlayerEntity (-1);
            if (entity)
            {
                float range = 0.5f;
                if (inst->Random (0, 4) == 0) range = 2.0f;

                CVector position
                    = entity->GetPosition ()
                      + CVector (inst->Random (-range, range),
                                 inst->Random (-range, range), 0.0f);

                entity->SetPosn (position);
            }
        }
    }
};

DEFINE_EFFECT (ExperienceTheLagEffect, "effect_experience_the_lag", 0);
