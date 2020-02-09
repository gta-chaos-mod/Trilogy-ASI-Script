#pragma once

#include "util/EffectBase.h"

class OneHitKOEffect : public EffectBase
{
private:
    bool *neverHungryCheat = reinterpret_cast<bool *> (0x969174);

public:
    OneHitKOEffect ();

    void InitializeHooks () override;

    void Disable () override;

    void HandleTick () override;

private:
    static void HookedCHudRenderHealthBar (int playerId, signed int x,
                                           signed int y);
};
