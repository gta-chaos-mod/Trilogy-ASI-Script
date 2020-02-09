#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/RandomHelper.h"

#include "CCarCtrl.h"

class ToTheLeftToTheRightEffect : public EffectBase
{
private:
    int wait = 0;

public:
    ToTheLeftToTheRightEffect ();

    void HandleTick ();
};
