#pragma once

#include "util/EffectBase.h"
#include "rw/rwcore.h"

class UpsideDownScreenEffect : public EffectBase
{
private:

	static RwRaster* raster;
	static RwIm2DVertex vertices[4];

	static void ResetRaster();

public:
	UpsideDownScreenEffect();

	void Enable() override;

	void Disable() override;

	static void EndUpdateEvent(RwCamera* camera);
};
