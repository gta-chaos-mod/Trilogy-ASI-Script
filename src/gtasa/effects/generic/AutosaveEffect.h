#pragma once

#include "effects/EffectPlaceholder.h"
#include "util/GameUtil.h"

#include "util/Config.h"

class AutosaveEffect : public EffectPlaceholder
{
private:
    bool didSave        = false;
    int  missionsPassed = 0;

public:
    AutosaveEffect (int missionsPassed);

    bool IsPlaceholder () override;

    void HandleTick () override;
};
