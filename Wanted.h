#pragma once

#include "plugin.h"
#include "common.h"

#include "CWanted.h"

class Wanted {
public:
	static void IncreaseWantedLevel();
	static void ClearWantedLevel();
	static void SixWantedStars();
};
