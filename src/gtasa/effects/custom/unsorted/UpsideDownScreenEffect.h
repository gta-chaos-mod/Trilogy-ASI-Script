#pragma once

#include "util/EffectBase.h"

class UpsideDownScreenEffect : public EffectBase
{
public:
	UpsideDownScreenEffect();

	void Enable() override;
	
	void Disable() override;

	static void ShowRasterEvent(RwCamera* camera);
};
