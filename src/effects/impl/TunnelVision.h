// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

class TunnelVision : public TimedEffect
{
public:
	TunnelVision(int _duration, const std::string& _description);

	void Enable() override;
	void Disable() override;

	static void DrawTunnelVision();
};
