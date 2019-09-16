// Copyright (c) 2019 Lordmau5
#include "RainbowCars.h"

float RainbowCars::hueShift = 0.0f;
std::vector<std::pair<RwRGBA*, RwRGBA>> RainbowCars::resetMaterialColors;

// Custom events for CVehicle::SetupRender and CVehicle::ResetAfterRender
static ThiscallEvent<AddressList<0x5532A9, H_CALL>, PRIORITY_BEFORE, ArgPickN<CVehicle*, 0>, void(CVehicle*)> setupRenderEvent;
static ThiscallEvent<AddressList<0x55332A, H_CALL>, PRIORITY_AFTER, ArgPickN<CVehicle*, 0>, void(CVehicle*)> resetAfterRenderEvent;

RainbowCars::RainbowCars(int _duration, std::string _description)
	: TimedEffect(_duration, std::move(_description)) {}

void RainbowCars::Enable() {
	setupRenderEvent += SetupRenderEvent;
	resetAfterRenderEvent += ResetAfterRenderEvent;
}

void RainbowCars::Disable() {
	resetAfterRenderEvent -= ResetAfterRenderEvent;
	setupRenderEvent -= SetupRenderEvent;

	TimedEffect::Disable();
}

void RainbowCars::HandleTick() {
	hueShift += CalculateTick(0.075f);
	if (hueShift > 360.0f) {
		hueShift -= 360.0f;
	}
}

void RainbowCars::SetupRenderEvent(CVehicle* vehicle) {
	ModifyCarPaint(vehicle);
}

void RainbowCars::ResetAfterRenderEvent(CVehicle* vehicle) {
	// In case some material got added more than once, restore in reverse order
	for (auto it = resetMaterialColors.rbegin(); it != resetMaterialColors.rend(); ++it) {
		*it->first = it->second;
	}

	resetMaterialColors.clear();
}

void RainbowCars::ModifyCarPaint(CVehicle* vehicle) {
	if (vehicle->m_pRwObject) {
		if (vehicle->m_pRwObject->type == rpCLUMP) {
			RpClumpForAllAtomics(reinterpret_cast<RpClump*>(vehicle->m_pRwObject), AtomicCallback, vehicle);
		}
		else {
			AtomicCallback(reinterpret_cast<RpAtomic*>(vehicle->m_pRwObject), vehicle);
		}
	}
}

RpMaterial* RainbowCars::MaterialCallback(RpMaterial* material, void* data) {
	if (!data) {
		return material;
	}

	CVehicle* vehicle = reinterpret_cast<CVehicle*>(data);

	resetMaterialColors.emplace_back(&material->color, material->color);

	CRGBA color = CVehicleModelInfo::ms_vehicleColourTable[vehicle->m_nPrimaryColor];

	int r = color.r;
	int g = color.g;
	int b = color.b;
	ColorHelper::HueShift(r, g, b, hueShift, 0.9f);

	material->color.red = r;
	material->color.green = g;
	material->color.blue = b;

	return material;
}

RpAtomic* RainbowCars::AtomicCallback(RpAtomic* atomic, void* data) {
	if (atomic->geometry) {
		atomic->geometry->flags |= rpGEOMETRYMODULATEMATERIALCOLOR;
		RpGeometryForAllMaterials(atomic->geometry, MaterialCallback, data);
	}
	return atomic;
}
