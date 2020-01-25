#include "GreyscaleScreenEffect.h"
#include "rw/rwcore.h"
#include <memory>
#include "CMenuManager.h"

static CdeclEvent<AddressList<0x53EBF5, H_CALL>, PRIORITY_BEFORE, ArgPickN<RwCamera*, 0>, RwCamera*(RwCamera*)> showRasterEvent;

GreyscaleScreenEffect::GreyscaleScreenEffect()
	: EffectBase("effect_upside_down")
{
	AddType("screen");
}

void GreyscaleScreenEffect::Enable() {
	EffectBase::Enable();
	
	showRasterEvent += ShowRasterEvent;
}

inline RwRGBA* GetPixel(RwRaster* raster, int x, int y) {
	return (RwRGBA*) (raster->cpPixels + y * raster->stride + (x * 4));
}

void GreyscaleScreenEffect::ShowRasterEvent(RwCamera* camera) {

	if (FrontEndMenuManager.m_bMenuActive) {
		return;
	}
	
	RwRaster* raster = camera->frameBuffer;
	RwRasterLock (raster, 0, rwRASTERLOCKREADWRITE);

	for(int y = 0; y < raster->height; y++) {
		for(int x = 0; x < raster->width; x++) {
			RwRGBA* pixel = GetPixel(raster, x, y);
			int value = (pixel->red + pixel->green + pixel->blue) / 3;

			pixel->red = pixel->green = pixel->blue = value;
		}
	}
	RwRasterUnlock(raster);
}

void GreyscaleScreenEffect::Disable() {
	showRasterEvent -= ShowRasterEvent;

	EffectBase::Disable();
}
