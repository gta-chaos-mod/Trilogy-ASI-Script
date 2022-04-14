#include <util/EffectBase.h>
#include <util/GameUtil.h>

class SimpleGravityEffect : public EffectBase
{
    float gravity = 0.008f;

public:
    SimpleGravityEffect (float gravity) : EffectBase ()
    {
        this->gravity = gravity;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        injector::WriteMemory (0x863984, 0.008f, true);
        injector::WriteMemory (0x871494, (-0.008f / 2), true);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        GameUtil::SetVehiclesToRealPhysics ();

        injector::WriteMemory (0x863984, this->gravity, true);

        // Potentially fix bikes disappearing with zero / negative gravity
        injector::WriteMemory (0x871494,
                               this->gravity == 0.0f ? -0.00000001f
                                                     : (-this->gravity / 2),
                               true);
    }
};

// clang-format off
DEFINE_EFFECT (SimpleGravityEffect, "effect_quarter_gravity",   GROUP_GRAVITY, 0.002f);
DEFINE_EFFECT (SimpleGravityEffect, "effect_half_gravity",      GROUP_GRAVITY, 0.004f);
DEFINE_EFFECT (SimpleGravityEffect, "effect_double_gravity",    GROUP_GRAVITY, 0.016f);
DEFINE_EFFECT (SimpleGravityEffect, "effect_quadruple_gravity", GROUP_GRAVITY, 0.032f);
DEFINE_EFFECT (SimpleGravityEffect, "effect_insane_gravity",    GROUP_GRAVITY, 0.64f);
// clang-format on