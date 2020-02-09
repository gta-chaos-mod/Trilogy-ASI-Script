#pragma once

#include "util/GameUtil.h"
#include "effects/TimedFunctionEffect.h"

#include "CCheat.h"

class BeachThemeCheat : public TimedFunctionEffect
{
public:
    BeachThemeCheat ();

private:
    static void BeachTheme ();
};
