#pragma once

#include "effects/EffectPlaceholder.h"
#include "util/GameUtil.h"

#include "util/Config.h"

#include "CGangWars.h"

class QuickSaveEffect : public EffectPlaceholder
{
private:
    bool didSave = false;

public:
    QuickSaveEffect ();

    bool IsPlaceholder () override;

    void HandleTick () override;
};
