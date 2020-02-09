#pragma once

#include "util/GameUtil.h"
#include "effects/TimedFunctionEffect.h"

#include "CCheat.h"

class KinkyThemeCheat : public TimedFunctionEffect
{
public:
    KinkyThemeCheat ();

private:
    static void KinkyTheme ();
};
