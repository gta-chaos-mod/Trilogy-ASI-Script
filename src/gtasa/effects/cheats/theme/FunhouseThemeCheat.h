#pragma once

#include "util/GameUtil.h"
#include "effects/TimedFunctionEffect.h"

#include "CCheat.h"

class FunhouseThemeCheat : public TimedFunctionEffect
{
public:
	FunhouseThemeCheat();

private:
	static void FunhouseTheme();
};
