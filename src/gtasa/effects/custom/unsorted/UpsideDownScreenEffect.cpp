#include "UpsideDownScreenEffect.h"
#include "rw/rwcore.h"
#include <memory>
#include "CMenuManager.h"

static CdeclEvent<AddressList<0x53EBF5, H_CALL>, PRIORITY_BEFORE, ArgPickN<RwCamera*, 0>, RwCamera*(RwCamera*)> showRasterEvent;

UpsideDownScreenEffect::UpsideDownScreenEffect()
	: EffectBase("effect_upside_down")
{
	AddType("screen");
}

void UpsideDownScreenEffect::Enable() {
	EffectBase::Enable();
	
	showRasterEvent += ShowRasterEvent;
}

inline RwRGBA* GetPixel(RwRaster* raster, int x, int y) {
	return (RwRGBA*) (raster->cpPixels + y * raster->stride + (x * 4));
}

void UpsideDownScreenEffect::ShowRasterEvent(RwCamera* camera) {

	if (FrontEndMenuManager.m_bMenuActive) {
		return;
	}
	
	RwRaster* raster = camera->frameBuffer;
	RwRasterLock (raster, 0, rwRASTERLOCKREADWRITE);

	for(int y = 0; y < raster->height / 2; y++) {
		for(int x = 0; x < raster->width; x++) {
			RwRGBA tmp = *GetPixel(raster, x, y);
			memcpy (GetPixel (raster, x, y),
					GetPixel (raster, x, raster->height - y - 1),
					4);
			memcpy (GetPixel (raster, x, raster->height - y - 1),
					&tmp,
					4);
		}
	}
	RwRasterUnlock(raster);
}

void UpsideDownScreenEffect::Disable() {
	showRasterEvent -= ShowRasterEvent;

	EffectBase::Disable();
}
