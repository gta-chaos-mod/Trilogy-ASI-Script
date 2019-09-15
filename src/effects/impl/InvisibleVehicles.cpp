// Copyright (c) 2019 Lordmau5
#include "InvisibleVehicles.h"

bool InvisibleVehicles::onlyWheels = false;
bool InvisibleVehicles::isEnabled = false;

InvisibleVehicles::InvisibleVehicles(bool _onlyWheels, int _duration, std::string _description)
	: TimedEffect(_duration, _description, "invisible_vehicles") {
	onlyWheels = _onlyWheels;
}

void InvisibleVehicles::InitializeHooks() {
	patch::RedirectCall(0x6A2C24, HookedRenderAutomobile); // Automobile
	patch::RedirectCall(0x6BDE5E, HookedRenderBike); // Bike + Bmx
	patch::RedirectCall(0x6CAB80, HookedRenderPlane); // Plane
	patch::RedirectCall(0x6C4523, HookedRenderHeli); // Heli

	patch::RedirectCall(0x5343B2, HookedRenderEffects);

	// Vehicle Shadows (Car, Bike, BMX, Heli, Plane)
	for (int address : { 0x6ABCF5, 0x6BD667, 0x6C0B21, 0x6C58A0, 0x6CA73A }) {
		patch::RedirectCall(address, HookedRenderShadows);
	}

	// Vehicle Headlights (Car, Bike)
	for (int address : { 0x6A2EDA, 0x6A2EF2, 0x6BDE80 }) {
		patch::RedirectCall(address, HookedCVehicleDoHeadLightBeam);
	}

	// Vehicle Lights (Car, Bike, Train)
	/*for (int address : { 0x6ABCB9, 0x6BD65F, 0x6F5592, 0x6F55A1, 0x6F55B4 }) {
		patch::RedirectCall(address, HookedCVehicleDoVehicleLights);
	}*/
}

void InvisibleVehicles::Disable() {
	isEnabled = false;

	TimedEffect::Disable();
}

void InvisibleVehicles::HandleTick() {
	isEnabled = true;
}

void InvisibleVehicles::TryRenderAtomic(RwFrame* frameArray[], int size, int slot) {
	if (frameArray && slot < size && frameArray[slot]) {
		RpAtomic* atomic = (RpAtomic*)GetFirstObject(frameArray[slot]);
		if (atomic) {
			atomic->renderCallBack(atomic);
		}
	}
}

void __fastcall InvisibleVehicles::HookedRenderAutomobile(CAutomobile* thisAutomobile, void* edx) {
	if (!thisAutomobile) {
		return;
	}

	if (!isEnabled) {
		plugin::CallMethod<0x6D0E60, CVehicle*>(thisAutomobile);
	}
	else if (onlyWheels) {
		TryRenderAtomic(thisAutomobile->m_aCarNodes, eCarNodes::CAR_NUM_NODES, eCarNodes::CAR_WHEEL_RF);
		TryRenderAtomic(thisAutomobile->m_aCarNodes, eCarNodes::CAR_NUM_NODES, eCarNodes::CAR_WHEEL_RM);
		TryRenderAtomic(thisAutomobile->m_aCarNodes, eCarNodes::CAR_NUM_NODES, eCarNodes::CAR_WHEEL_RB);

		TryRenderAtomic(thisAutomobile->m_aCarNodes, eCarNodes::CAR_NUM_NODES, eCarNodes::CAR_WHEEL_LF);
		TryRenderAtomic(thisAutomobile->m_aCarNodes, eCarNodes::CAR_NUM_NODES, eCarNodes::CAR_WHEEL_LM);
		TryRenderAtomic(thisAutomobile->m_aCarNodes, eCarNodes::CAR_NUM_NODES, eCarNodes::CAR_WHEEL_LB);
	}
}

void __fastcall InvisibleVehicles::HookedRenderHeli(CHeli* thisHeli, void* edx) {
	if (!thisHeli) {
		return;
	}

	if (!isEnabled) {
		plugin::CallMethod<0x534310, CVehicle*>(thisHeli);
	}
	else if (onlyWheels) {
		TryRenderAtomic(thisHeli->m_aCarNodes, eHeliNodes::HELI_NUM_NODES, eHeliNodes::HELI_WHEEL_RF);
		TryRenderAtomic(thisHeli->m_aCarNodes, eHeliNodes::HELI_NUM_NODES, eHeliNodes::HELI_WHEEL_RM);
		TryRenderAtomic(thisHeli->m_aCarNodes, eHeliNodes::HELI_NUM_NODES, eHeliNodes::HELI_WHEEL_RB);

		TryRenderAtomic(thisHeli->m_aCarNodes, eHeliNodes::HELI_NUM_NODES, eHeliNodes::HELI_WHEEL_LF);
		TryRenderAtomic(thisHeli->m_aCarNodes, eHeliNodes::HELI_NUM_NODES, eHeliNodes::HELI_WHEEL_LM);
		TryRenderAtomic(thisHeli->m_aCarNodes, eHeliNodes::HELI_NUM_NODES, eHeliNodes::HELI_WHEEL_LB);
	}
}

void __fastcall InvisibleVehicles::HookedRenderBike(CBike* thisBike, void* edx) {
	if (!thisBike) {
		return;
	}

	if (!isEnabled) {
		plugin::CallMethod<0x6D0E60, CVehicle*>(thisBike);
	}
	else if (onlyWheels) {
		TryRenderAtomic(thisBike->m_aBikeNodes, eBikeNodes::BIKE_NUM_NODES, eBikeNodes::BIKE_WHEEL_FRONT);
		TryRenderAtomic(thisBike->m_aBikeNodes, eBikeNodes::BIKE_NUM_NODES, eBikeNodes::BIKE_WHEEL_REAR);
	}
}

void __fastcall InvisibleVehicles::HookedRenderPlane(CPlane* thisPlane, void* edx) {
	if (!thisPlane) {
		return;
	}

	if (!isEnabled) {
		plugin::CallMethod<0x6D0E60, CVehicle*>(thisPlane);
	}
	else if (onlyWheels) {
		TryRenderAtomic(thisPlane->m_aCarNodes, ePlaneNodes::PLANE_NUM_NODES, ePlaneNodes::PLANE_WHEEL_RF);
		TryRenderAtomic(thisPlane->m_aCarNodes, ePlaneNodes::PLANE_NUM_NODES, ePlaneNodes::PLANE_WHEEL_RM);
		TryRenderAtomic(thisPlane->m_aCarNodes, ePlaneNodes::PLANE_NUM_NODES, ePlaneNodes::PLANE_WHEEL_RB);

		TryRenderAtomic(thisPlane->m_aCarNodes, ePlaneNodes::PLANE_NUM_NODES, ePlaneNodes::PLANE_WHEEL_LF);
		TryRenderAtomic(thisPlane->m_aCarNodes, ePlaneNodes::PLANE_NUM_NODES, ePlaneNodes::PLANE_WHEEL_LM);
		TryRenderAtomic(thisPlane->m_aCarNodes, ePlaneNodes::PLANE_NUM_NODES, ePlaneNodes::PLANE_WHEEL_LB);
	}
}

void __fastcall InvisibleVehicles::HookedRenderEffects(CEntity* thisEntity, void* edx) {
	if (!thisEntity) {
		return;
	}

	if (!isEnabled || !CModelInfo::IsVehicleModelType(thisEntity->m_nModelIndex)) {
		thisEntity->RenderEffects();
	}
	else {
		switch (((CVehicle*)thisEntity)->m_nVehicleClass) {
			case VEHICLE_AUTOMOBILE:
			case VEHICLE_BIKE:
			case VEHICLE_BMX:
			case VEHICLE_HELI:
			case VEHICLE_PLANE:
				break;
			default:
				thisEntity->RenderEffects();
		}
	}
}

void InvisibleVehicles::HookedRenderShadows(CVehicle* thisVehicle, VEH_SHD_TYPE shadowType) {
	if (!thisVehicle) {
		return;
	}

	if (!isEnabled) {
		CShadows::StoreShadowForVehicle(thisVehicle, shadowType);
	}
}

void __fastcall InvisibleVehicles::HookedCVehicleDoHeadLightBeam(CVehicle* thisVehicle, void* edx, int a2, CMatrix* matrix, char a4) {
	if (!thisVehicle || !matrix) {
		return;
	}

	if (!isEnabled) {
		CallMethod<0x6E0E20, CVehicle*>(thisVehicle, a2, matrix, a4);
	}
}

void __fastcall InvisibleVehicles::HookedCVehicleDoVehicleLights(CVehicle* thisVehicle, void* edx, int a2, CMatrix* matrix, int st) {
	if (!thisVehicle || !matrix) {
		return;
	}

	if (!isEnabled) {
		CallMethod<0x6E1A60, CVehicle*>(thisVehicle, a2, matrix, st);
	}
}
