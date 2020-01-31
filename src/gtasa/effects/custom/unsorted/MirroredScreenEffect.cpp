#include "MirroredScreenEffect.h"
#include "CMenuManager.h"
#include "util/DrawHelper.h"
#include "Color.h"
#include "CScene.h"

static CdeclEvent<AddressList<0x53EBF5, H_CALL>, PRIORITY_BEFORE, ArgPickN<RwCamera*, 0>, RwCamera * (RwCamera*)> endUpdateEvent;
static CdeclEvent<AddressList<0x745C7D, H_CALL>, PRIORITY_BEFORE, ArgPickNone, void ()> createCameraSubRasterEvent;


RwRaster* MirroredScreenEffect::raster = nullptr;
RwIm2DVertex MirroredScreenEffect::vertices[4] = {};

MirroredScreenEffect::MirroredScreenEffect()
	: EffectBase("effect_mirrored") {}

void MirroredScreenEffect::Enable() {
	EffectBase::Enable();

	ResetRaster();
	
	endUpdateEvent += EndUpdateEvent;
	createCameraSubRasterEvent += ResetRaster;
}

void MirroredScreenEffect::Disable() {
	endUpdateEvent -= EndUpdateEvent;
	createCameraSubRasterEvent -= ResetRaster;

	EffectBase::Disable();
}

void MirroredScreenEffect::ResetRaster() {
	if(raster) {
		RwRasterDestroy(raster);
            }
	auto cameraRaster = Scene.m_pRwCamera->frameBuffer;
	raster = RwRasterCreate(cameraRaster->width, cameraRaster->height,
				cameraRaster->depth, rwRASTERTYPECAMERATEXTURE);

	// Reset raster and vertices
	DrawHelper::Append(vertices, 0, CVector2D(0, 0), plugin::color::White, 1, 0);
	DrawHelper::Append(vertices, 1, CVector2D(cameraRaster->width, 0), plugin::color::White, 0, 0);
	DrawHelper::Append(vertices, 3, CVector2D(cameraRaster->width, cameraRaster->height), plugin::color::White, 0, 1);
	DrawHelper::Append(vertices, 2, CVector2D(0, cameraRaster->height), plugin::color::White, 1, 1);
}

void MirroredScreenEffect::EndUpdateEvent(RwCamera* camera) {
	if (FrontEndMenuManager.m_bMenuActive) {
		return;
	}

	SetRenderState(rwRENDERSTATESHADEMODE, rwSHADEMODEFLAT);
	
	RwCameraEndUpdate(camera);
	RwRasterPushContext(raster);
	RwRasterRenderFast(camera->frameBuffer, 0, 0);
	RwRasterPopContext();
	RwCameraBeginUpdate(camera);

	SetRenderState(rwRENDERSTATETEXTURERASTER, (int) raster);
	
	RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, vertices, 4);
}
