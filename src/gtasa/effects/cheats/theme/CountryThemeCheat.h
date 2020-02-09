#pragma once

#include "util/GameUtil.h"
#include "effects/TimedFunctionEffect.h"

#include "CCheat.h"

class CountryThemeCheat : public TimedFunctionEffect
{
public:
    CountryThemeCheat ();

private:
    static void CountryTheme ();
};
