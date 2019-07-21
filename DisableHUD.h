#pragma once

#include "TimedEffect.h"

#include "CRadar.h"
#include "CHud.h"

class DisableHUD : public TimedEffect
{
public:
	static bool isEnabled;

public:
	DisableHUD(int _duration, std::string _description);

	void Enable() override;
	void Disable() override;
};

