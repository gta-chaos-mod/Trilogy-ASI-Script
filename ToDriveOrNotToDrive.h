#pragma once

#include "TimedEffect.h"

#include "CBike.h"
#include "CAutomobile.h"
#include "CPools.h"

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

