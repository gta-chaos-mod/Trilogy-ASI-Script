#include "util/EffectBase.h"
#include "util/Teleportation.h"

class VoidWarpEffect : public EffectBase
{
public:
    bool
    CanActivate () override
    {
        return Teleportation::CanTeleport ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        inst->SetIsOneTimeEffect ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (!CanActivate ())
        {
            inst->ResetTimer ();
            return;
        }

        CEntity *entity = FindPlayerEntity (-1);
        if (!entity) return;

        CVector position = entity->GetPosition ();

        position.z = -20.0f;

        Teleportation::Teleport (position);

        inst->Disable ();
    }
};

DEFINE_EFFECT (VoidWarpEffect, "effect_void_warp", 0);
