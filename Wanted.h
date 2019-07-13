#pragma once

#include "plugin.h"
#include "common.h"

#include "CWanted.h"

class Wanted {
public:
	static void Wanted::IncreaseWantedLevel();
	static void Wanted::ClearWantedLevel();
	static void Wanted::SixWantedStars();
};
