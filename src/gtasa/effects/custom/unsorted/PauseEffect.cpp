#include <effects/OneTimeEffect.h>

#include <CMenuManager.h>

class PauseEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        FrontEndMenuManager.m_bActivateMenuNextFrame = true;
    }
};

DEFINE_EFFECT (PauseEffect, "effect_pause", 0);