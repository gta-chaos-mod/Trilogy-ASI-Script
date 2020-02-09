#pragma once

#include "util/EffectBase.h"

class CPed;

class BigHeadsEffect : public EffectBase
{
public:
    BigHeadsEffect ();

    void Enable () override;
    void Disable () override;

    static void RenderPedEvent (CPed *ped);
};
