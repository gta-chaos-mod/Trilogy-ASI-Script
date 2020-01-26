#include "MirroredScreenEffect.h"
#include "rw/rwcore.h"
#include <memory>
#include "CMenuManager.h"

static CdeclEvent<AddressList<0x53EBF5, H_CALL>, PRIORITY_BEFORE, ArgPickN<RwCamera*, 0>, RwCamera * (RwCamera*)> showRasterEvent;

MirroredScreenEffect::MirroredScreenEffect()
	: EffectBase("effect_mirrored_screen") {}

void MirroredScreenEffect::Enable() {
	EffectBase::Enable();

	showRasterEvent += ShowRasterEvent;
}

void MirroredScreenEffect::Disable() {
	showRasterEvent -= ShowRasterEvent;

	EffectBase::Disable();
}

inline RwRGBA* GetPixel(RwRaster* raster, int x, int y) {
	return (RwRGBA*)(raster->cpPixels + y * raster->stride + (x * 4));
}

void MirroredScreenEffect::ShowRasterEvent(RwCamera* camera) {
	if (FrontEndMenuManager.m_bMenuActive) {
		return;
	}

	RwRaster* raster = camera->frameBuffer;

	RwRasterLock(raster, 0, rwRASTERLOCKREADWRITE);

	static RwUInt8* tmp = new RwUInt8[raster->stride];

	for (int y = 0; y < raster->height; y++) {
		for (int x = 0; x < raster->width / 2; x++) {
			RwRGBA tmp = *GetPixel(raster, x, y);
			memcpy(GetPixel(raster, x, y),
				GetPixel(raster, raster->width - 1 - x, y),
				4);
			memcpy(GetPixel(raster, raster->width - 1 - x, y),
				&tmp,
				4);
		}
	}
	RwRasterUnlock(raster);
}
