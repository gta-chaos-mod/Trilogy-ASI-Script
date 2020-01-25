#pragma once

#include "util/EffectBase.h"

class TunnelVisionEffect : public EffectBase
{
public:
	TunnelVisionEffect();

	void Enable() override;
	void Disable() override;

	static void DrawTunnelVision();
};
