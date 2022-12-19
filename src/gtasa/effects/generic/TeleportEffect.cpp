#include "util/EffectBase.h"
#include "util/Teleportation.h"

class TeleportEffect : public EffectBase
{
    CVector destination;

public:
    bool
    CanActivate () override
    {
        return Teleportation::CanTeleport ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        this->destination = {inst->GetCustomData ().value ("posX", 0.0f),
                             inst->GetCustomData ().value ("posY", 0.0f),
                             inst->GetCustomData ().value ("posZ", 0.0f)};
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (!CanActivate ())
        {
            inst->ResetTimer ();
            return;
        }

        Teleportation::Teleport (this->destination);
        inst->Disable ();
    }
};

DEFINE_EFFECT (TeleportEffect, "effect_teleport", GROUP_TELEPORT);
