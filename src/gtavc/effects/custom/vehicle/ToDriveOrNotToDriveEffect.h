#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include "CAutomobile.h"
#include "CBike.h"

class ToDriveOrNotToDriveEffect : public EffectBase
{
private:
    bool doPop = true;
    int  wait  = 0;

public:
    ToDriveOrNotToDriveEffect ();

    void Disable () override;

    void HandleTick () override;

private:
    void FixTires ();
    void PopTires ();
};
