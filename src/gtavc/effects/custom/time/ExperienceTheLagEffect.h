#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/RandomHelper.h"

#include "util/Config.h"

class ExperienceTheLagEffect : public EffectBase
{
private:
    int wait = 0;

public:
    ExperienceTheLagEffect ();

    void Disable () override;

    void HandleTick () override;
};
