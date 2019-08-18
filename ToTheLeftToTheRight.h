// Copyright (c) 2019 Lordmau5
#pragma once

#include "TimedEffect.h"

#include "CCarCtrl.h"

class ToTheLeftToTheRight : public TimedEffect
{
private:
	int wait = 0;

public:
	ToTheLeftToTheRight(int _duration, std::string _description);

	void HandleTick();
};
