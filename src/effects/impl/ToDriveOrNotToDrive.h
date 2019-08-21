// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "CAutomobile.h"
#include "CBike.h"

class ToDriveOrNotToDrive : public TimedEffect
{
private:
	bool doPop = true;
	int wait = 0;

public:
	ToDriveOrNotToDrive(int _duration, std::string _description);

	void Disable() override;

	void HandleTick() override;

private:
	void FixTires();
	void PopTires();
};
