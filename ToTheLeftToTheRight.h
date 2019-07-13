#pragma once

#include "TimedEffect.h"

#include "CPools.h"
#include "CCarCtrl.h"

class ToTheLeftToTheRight : public TimedEffect
{
private:
	int wait = 0;

public:
	ToTheLeftToTheRight(int duration, std::string description);

	void HandleTick();
};

