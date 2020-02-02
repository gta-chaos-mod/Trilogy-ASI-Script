#include "MirroredWorldEffect.h"
#include "CMenuManager.h"
#include "util/DrawHelper.h"
#include "Color.h"
#include "CScene.h"

static CdeclEvent<AddressList<0x53EAD3, H_CALL>, PRIORITY_AFTER, ArgPickNone, void()> renderEffectsEvent;
static CdeclEvent<AddressList<0x745C7D, H_CALL>, PRIORITY_BEFORE, ArgPickNone, void()> createCameraSubRasterEvent;

RwRaster* MirroredWorldEffect::raster = nullptr;
RwIm2DVertex MirroredWorldEffect::vertices[4] = {};

MirroredWorldEffect::MirroredWorldEffect()
	: EffectBase("effect_mirrored_world") {}

void MirroredWorldEffect::InitializeHooks() {
	EffectBase::InitializeHooks();

	for (int address : {
		0x0056EC9F,
		0x006447B2,
		0x006448DA,
		0x006AD805,
		0x006AD81A,
		0x006AD846,
		0x006AD907,
		0x006B4DA9,
		0x006B4E9B,
		0x006BE411,
		0x006BE43F,
		0x006BE488,
		0x006BE5D9,
		0x006C1783,
		0x006C17BB,
		0x006C17E9,
		0x006C490F,
		0x006C4930,
		0x006C497C,
		0x006C4A78,
		0x006CAE97,
		0x006CAEC5,
		0x006CAF0F,
		0x006CB04F,
		0x006CB191,
		0x006CE0BA,
		0x006CE81E,
		0x006D8B42,
		0x006DA2EC,
		0x006DA44B,
		0x006F0B50,
		0x006F0B65,
		0x006F0B91,
		0x006F0C3C,
	}) {
		HookCall(address, HookedGetSteeringLeftRight);
	}

	for (int address : {
		0x00523C67,
		0x00523C90,
		0x00523CD0,
		0x00528E6C,
		0x005714DE,
		//0x005803FA, // Menu Input
		//0x00580444,
		0x005E1A33,
		0x0060DD75,
		0x0060DDCD,
		0x0061EA2A,
		0x0061EA49,
		0x0064F457,
		0x0067BF14,
		0x0067CFD3,
		0x0067E867,
		0x0068700F,
		0x0068702E,
		0x00687585,
		0x00687CD7,
		0x00687F75,
		0x00688416,
		0x00688AD6,
		0x00691E4D,

	}) {
		HookCall(address, HookedPedWalkLeftRight);
	}

	for (int address : {
		0x0050A679,
		0x005272F0,
		0x0052785D,
		0x0067EDEA,
		0x006A3F76,
		0x006C4B3C,
		0x006CB21D,
		0x006DA351,
		0x006DA3F9,
		0x0074213D,
	}) {
		HookCall(address, HookedGedLookLeft);
	}

	for (int address : {
		0x0050A68E,
		0x00527305,
		0x0052788F,
		0x0067EE2C,
		0x006A3F85,
		0x006C4B24,
		0x006CB1FE,
		0x006DA338,
		0x006DA435,
		0x0074214F,
	}) {
		HookCall(address, HookedGedLookRight);
	}

	// TODO:
	// - Invert Radar (0x586976, https://cdn.discordapp.com/attachments/597796844906741770/673648028229566520/unknown.png)
	// - Invert Pause Menu Map (0x575130)
}

__int16 __fastcall MirroredWorldEffect::HookedGetSteeringLeftRight(CPad* thisPad) {
	return -(CallMethodAndReturn<__int16, 0x53FB80, CPad*>(thisPad));
}

__int16 __fastcall MirroredWorldEffect::HookedPedWalkLeftRight(CPad* thisPad) {
	return -(CallMethodAndReturn<__int16, 0x53FC90, CPad*>(thisPad));
}

char __fastcall MirroredWorldEffect::HookedGedLookLeft(CPad* thisPad) {
	return CallMethodAndReturn<char, 0x53FE10, CPad*>(thisPad);
}

char __fastcall MirroredWorldEffect::HookedGedLookRight(CPad* thisPad) {
	return CallMethodAndReturn<char, 0x53FDD0, CPad*>(thisPad);
}

void MirroredWorldEffect::Enable() {
	EffectBase::Enable();

	ResetRaster();

	renderEffectsEvent += RenderEffectsEvent;
	createCameraSubRasterEvent += ResetRaster;

	CMenuManager::bInvertMouseX = true;
}

void MirroredWorldEffect::Disable() {
	CMenuManager::bInvertMouseX = false;

	renderEffectsEvent -= RenderEffectsEvent;
	createCameraSubRasterEvent -= ResetRaster;
	
	EffectBase::Disable();
}

void MirroredWorldEffect::ResetRaster() {
	if (raster) {
		RwRasterDestroy(raster);
	}
	auto cameraRaster = Scene.m_pRwCamera->frameBuffer;
	raster = RwRasterCreate(cameraRaster->width, cameraRaster->height,
		cameraRaster->depth, rwRASTERTYPECAMERATEXTURE);

	// Reset raster and vertices
	DrawHelper::Append(vertices, 0, CVector2D(0, 0), plugin::color::White, 1, 0);
	DrawHelper::Append(vertices, 1, CVector2D((float)cameraRaster->width, 0), plugin::color::White, 0, 0);
	DrawHelper::Append(vertices, 3, CVector2D((float)cameraRaster->width, (float)cameraRaster->height), plugin::color::White, 0, 1);
	DrawHelper::Append(vertices, 2, CVector2D(0, (float)cameraRaster->height), plugin::color::White, 1, 1);
}

void MirroredWorldEffect::RenderEffectsEvent() {
	if (FrontEndMenuManager.m_bMenuActive) {
		return;
	}

	Call<0x700CC0>(); //CPostEffects::ImmediateModeRenderStatesStore();
	Call<0x700D70>();  //CPostEffects::ImmediateModeRenderStatesSet

	SetRenderState(rwRENDERSTATESHADEMODE, rwSHADEMODEFLAT);

	RwCameraEndUpdate(Scene.m_pRwCamera);
	RwRasterPushContext(raster);
	RwRasterRenderFast(Scene.m_pRwCamera->frameBuffer, 0, 0);
	RwRasterPopContext();
	RwCameraBeginUpdate(Scene.m_pRwCamera);

	SetRenderState(rwRENDERSTATETEXTURERASTER, (int)raster);

	RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, vertices, 4);

	Call<0x700E00>(); //CPostEffects::ImmediateModeRenderStatesReStore
}
