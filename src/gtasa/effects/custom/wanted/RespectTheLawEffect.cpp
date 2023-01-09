// Effect created by gromchek

#include "util/EffectBase.h"

class RespectTheLawEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CWanted *wanted = FindPlayerWanted (-1);
        if (!wanted) return;

        if (!player->CanSetPedState () || !player->IsAlive ()) return;

        if (!wanted->m_nWantedLevel) return;

        player->SetPedState (PEDSTATE_ARRESTED);
    }
};

DEFINE_EFFECT (RespectTheLawEffect, "effect_respect_the_law", GROUP_WANTED);