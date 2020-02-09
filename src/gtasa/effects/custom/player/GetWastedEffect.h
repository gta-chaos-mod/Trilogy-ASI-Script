#pragma once

#include "util/EffectBase.h"

#include "CCutsceneMgr.h"

class GetWastedEffect : public EffectBase
{
public:
    GetWastedEffect ();

    void HandleTick () override;
};
