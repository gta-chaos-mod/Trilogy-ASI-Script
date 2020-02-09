#pragma once

#include "util/GameUtil.h"
#include "effects/TimedFunctionEffect.h"

#include "CCheat.h"

class NinjaThemeCheat : public TimedFunctionEffect
{
public:
    NinjaThemeCheat ();

private:
    static void NinjaTheme ();
};
