#pragma once

#include "util/EffectBase.h"

class GreyscaleScreenEffect : public EffectBase
{
public:
	GreyscaleScreenEffect();

	void Enable() override;
	
	void Disable() override;

	static void ShowRasterEvent(RwCamera* camera);
};
