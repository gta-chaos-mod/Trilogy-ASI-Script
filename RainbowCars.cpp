#include "RainbowCars.h"

bool RainbowCars::isEnabled;
float RainbowCars::hueShift;
std::map<RpMaterial*, RwRGBA> RainbowCars::resetMaterials;

RainbowCars::RainbowCars(int _duration, std::string _description) : TimedEffect(_duration, _description) {}

void RainbowCars::Enable() {
	isEnabled = true;
}

void RainbowCars::Disable() {
	isEnabled = false;

	for (auto it = resetMaterials.begin(); it != resetMaterials.end(); ++it) {
		it->first->color = it->second;
	}

	resetMaterials.clear();
}

void RainbowCars::HandleTick() {
	hueShift += 5.0f;
	if (hueShift >= 360.0f) {
		hueShift -= 360.0f;
	}
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
	CVehicle* vehicle = reinterpret_cast<CVehicle*>(data);

	if (!resetMaterials.contains(material)) {
		resetMaterials[material] = material->color;
	}

	CVehicleModelInfo* info = (CVehicleModelInfo*)CModelInfo::GetModelInfo(vehicle->m_nModelIndex);
	CRGBA color = CVehicleModelInfo::ms_vehicleColourTable[vehicle->m_nPrimaryColor];

	int r = color.r;
	int g = color.g;
	int b = color.b;
	ColorHelper::HueShift(r, g, b, hueShift);

	material->color = CRGBA(r, g, b, (unsigned int)material->color.alpha).ToRwRGBA();
	return material;
}

RpAtomic* RainbowCars::AtomicCallback(RpAtomic* atomic, void* data) {
	if (atomic->geometry) {
		atomic->geometry->flags |= rpGEOMETRYMODULATEMATERIALCOLOR;
		RpGeometryForAllMaterials(atomic->geometry, MaterialCallback, data);
	}
	return atomic;
}
