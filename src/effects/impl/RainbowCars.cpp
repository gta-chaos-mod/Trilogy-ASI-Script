// Copyright (c) 2019 Lordmau5
#include "RainbowCars.h"

bool RainbowCars::isEnabled = false;
float RainbowCars::hueShift = 0.0f;
std::list<std::pair<unsigned int*, unsigned int>> RainbowCars::resetEntries;

RainbowCars::RainbowCars(int _duration, std::string _description)
	: TimedEffect(_duration, _description) {}

void RainbowCars::Enable() {
	isEnabled = true;

	Events::vehicleRenderEvent.before += RenderVehicleEventBefore;
	Events::vehicleRenderEvent.after += RenderVehicleEventAfter;
}

void RainbowCars::Disable() {
	isEnabled = false;

	Events::vehicleRenderEvent.before -= RenderVehicleEventBefore;
	Events::vehicleRenderEvent.after -= RenderVehicleEventAfter;

	TimedEffect::Disable();
}

void RainbowCars::HandleTick() {
	hueShift += 2.0f;
	if (hueShift >= 360.0f) {
		hueShift -= 360.0f;
	}
}

void RainbowCars::RenderVehicleEventBefore(CVehicle* vehicle) {
	if (isEnabled && vehicle) {
		ModifyCarPaint(vehicle);
	}
}

void RainbowCars::RenderVehicleEventAfter(CVehicle* vehicle) {
	for (auto& p : resetEntries) {
		*p.first = p.second;
	}

	resetEntries.clear();
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

	resetEntries.push_back(std::make_pair(reinterpret_cast<unsigned int*>(&material->color), *reinterpret_cast<unsigned int*>(&material->color)));

	CRGBA color = CVehicleModelInfo::ms_vehicleColourTable[vehicle->m_nPrimaryColor];

	int r = color.r;
	int g = color.g;
	int b = color.b;
	ColorHelper::HueShift(r, g, b, hueShift, 0.85f);

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
