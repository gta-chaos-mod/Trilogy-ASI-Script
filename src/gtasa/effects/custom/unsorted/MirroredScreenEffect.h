#pragma once

#include "util/EffectBase.h"

class MirroredScreenEffect : public EffectBase
{

	static RwRaster* raster;
	static RwIm2DVertex vertices[4];

	static void ResetRaster();
	
public:
	MirroredScreenEffect();

	void Enable() override;
	
	void Disable() override;

	static void EndUpdateEvent(RwCamera* camera);
};
