#pragma once

#include "util/EffectBase.h"

class MirroredScreenEffect : public EffectBase
{
public:
	MirroredScreenEffect();

	void Enable() override;
	
	void Disable() override;

	static void ShowRasterEvent(RwCamera* camera);
};
