#pragma once

#include "util/EffectBase.h"

class TunnelVisionEffect : public EffectBase
{
public:
    TunnelVisionEffect ();

    EffectBase *SetEffectDuration (int duration) override;

    void Enable () override;
    void Disable () override;

    static void DrawTunnelVision ();
};
