// Copyright (c) 2019 Lordmau5
#include "InvisibleVehicles.h"

bool InvisibleVehicles::onlyWheels = false;
bool InvisibleVehicles::isEnabled = false;

InvisibleVehicles::InvisibleVehicles(bool _onlyWheels, int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "invisible_vehicles") {
	onlyWheels = _onlyWheels;
}

void InvisibleVehicles::InitializeHooks() {
	HookCall(0x6A2C24, HookedRenderAutomobile); // Automobile
	HookCall(0x6BDE5E, HookedRenderBike); // Bike + Bmx
	HookJump(0x6CAB80, HookedRenderPlane); // Plane
	HookCall(0x6C4523, HookedRenderHeli); // Heli
	HookJump(0x6F55C0, HookedRenderTrain); // Train

	HookCall(0x6F022F, HookedRenderBoat); // Boat
	for (int address : { 0x6F07C7, 0x6F08E1 }) {
		HookCall(address, HookedRwIm3DTransform); // Boat
	}

	HookCall(0x5343B2, HookedRenderEffects);

	// Vehicle Shadows (Car, Bike, BMX, Heli, Plane)
	for (int address : { 0x6ABCF5, 0x6BD667, 0x6C0B21, 0x6C58A0, 0x6CA73A }) {
		HookCall(address, HookedRenderShadows);
	}

	// Vehicle Headlights (Car, Bike)
	for (int address : { 0x6A2EDA, 0x6A2EF2, 0x6BDE80 }) {
		HookCall(address, HookedCVehicleDoHeadLightBeam);
	}

	// Vehicle Exhaust Particles (Car, Bike)
	for (int address : { 0x6AB344, 0x6BD3FF }) {
		HookCall(address, HookedCVehicleAddExhaustParticles);
	}

	// Vehicle Water Splash Particles (Car)
	HookCall(0x6AB2FF, HookedCVehicleAddWaterSplashParticles);

	// Vehicle Wheel Particles (Car, Bike)
	for (int address : { 0x6AB136, 0x6AB1FD, 0x6AB2B7, 0x6BD38C, 0x6C0AFD }) {
		HookCall(address, HookedCVehicleAddSingleWheelParticles);
	}

	// Vehicle Damage Particles (Car, Bike)
	for (int address : { 0x6AB34B, 0x6BD40A }) {
		HookCall(address, HookedCVehicleAddDamagedVehicleParticles);
	}
}

void InvisibleVehicles::Enable() {
	oldForceVehicleLightsOff = CVehicle::ms_forceVehicleLightsOff;
}

void InvisibleVehicles::Disable() {
	CVehicle::ms_forceVehicleLightsOff = oldForceVehicleLightsOff;

	TimedEffect::Disable();
}

void InvisibleVehicles::HandleTick() {
	CVehicle::ms_forceVehicleLightsOff = true;
}

void InvisibleVehicles::TryRenderAtomic(RwFrame* frameArray[], int size, int slot) {
	if (frameArray && slot < size && frameArray[slot]) {
		RpAtomic* atomic = (RpAtomic*)GetFirstObject(frameArray[slot]);
		if (atomic) {
			atomic->renderCallBack(atomic);
		}
	}
}

void __fastcall InvisibleVehicles::HookedRenderAutomobile(CAutomobile* thisAutomobile) {
	if (!thisAutomobile) {
		return;
	}

	if (onlyWheels) {
		TryRenderAtomic(thisAutomobile->m_aCarNodes, eCarNodes::CAR_NUM_NODES, eCarNodes::CAR_WHEEL_RF);
		TryRenderAtomic(thisAutomobile->m_aCarNodes, eCarNodes::CAR_NUM_NODES, eCarNodes::CAR_WHEEL_RM);
		TryRenderAtomic(thisAutomobile->m_aCarNodes, eCarNodes::CAR_NUM_NODES, eCarNodes::CAR_WHEEL_RB);

		TryRenderAtomic(thisAutomobile->m_aCarNodes, eCarNodes::CAR_NUM_NODES, eCarNodes::CAR_WHEEL_LF);
		TryRenderAtomic(thisAutomobile->m_aCarNodes, eCarNodes::CAR_NUM_NODES, eCarNodes::CAR_WHEEL_LM);
		TryRenderAtomic(thisAutomobile->m_aCarNodes, eCarNodes::CAR_NUM_NODES, eCarNodes::CAR_WHEEL_LB);
	}
}

void __fastcall InvisibleVehicles::HookedRenderHeli(CHeli* thisHeli) {
	if (!thisHeli) {
		return;
	}

	if (onlyWheels) {
		TryRenderAtomic(thisHeli->m_aCarNodes, eHeliNodes::HELI_NUM_NODES, eHeliNodes::HELI_WHEEL_RF);
		TryRenderAtomic(thisHeli->m_aCarNodes, eHeliNodes::HELI_NUM_NODES, eHeliNodes::HELI_WHEEL_RM);
		TryRenderAtomic(thisHeli->m_aCarNodes, eHeliNodes::HELI_NUM_NODES, eHeliNodes::HELI_WHEEL_RB);

		TryRenderAtomic(thisHeli->m_aCarNodes, eHeliNodes::HELI_NUM_NODES, eHeliNodes::HELI_WHEEL_LF);
		TryRenderAtomic(thisHeli->m_aCarNodes, eHeliNodes::HELI_NUM_NODES, eHeliNodes::HELI_WHEEL_LM);
		TryRenderAtomic(thisHeli->m_aCarNodes, eHeliNodes::HELI_NUM_NODES, eHeliNodes::HELI_WHEEL_LB);
	}
}

void __fastcall InvisibleVehicles::HookedRenderBike(CBike* thisBike) {
	if (!thisBike) {
		return;
	}

	if (onlyWheels) {
		TryRenderAtomic(thisBike->m_aBikeNodes, eBikeNodes::BIKE_NUM_NODES, eBikeNodes::BIKE_WHEEL_FRONT);
		TryRenderAtomic(thisBike->m_aBikeNodes, eBikeNodes::BIKE_NUM_NODES, eBikeNodes::BIKE_WHEEL_REAR);
	}
}

void __fastcall InvisibleVehicles::HookedRenderPlane(CPlane* thisPlane) {
	if (!thisPlane) {
		return;
	}

	if (onlyWheels) {
		TryRenderAtomic(thisPlane->m_aCarNodes, ePlaneNodes::PLANE_NUM_NODES, ePlaneNodes::PLANE_WHEEL_RF);
		TryRenderAtomic(thisPlane->m_aCarNodes, ePlaneNodes::PLANE_NUM_NODES, ePlaneNodes::PLANE_WHEEL_RM);
		TryRenderAtomic(thisPlane->m_aCarNodes, ePlaneNodes::PLANE_NUM_NODES, ePlaneNodes::PLANE_WHEEL_RB);

		TryRenderAtomic(thisPlane->m_aCarNodes, ePlaneNodes::PLANE_NUM_NODES, ePlaneNodes::PLANE_WHEEL_LF);
		TryRenderAtomic(thisPlane->m_aCarNodes, ePlaneNodes::PLANE_NUM_NODES, ePlaneNodes::PLANE_WHEEL_LM);
		TryRenderAtomic(thisPlane->m_aCarNodes, ePlaneNodes::PLANE_NUM_NODES, ePlaneNodes::PLANE_WHEEL_LB);
	}
}

void __fastcall InvisibleVehicles::HookedRenderTrain(CTrain* thisTrain) {
	if (!thisTrain) {
		return;
	}

	if (onlyWheels) {
		TryRenderAtomic(thisTrain->m_aTrainNodes, eTrainNodes::TRAIN_NUM_NODES, eTrainNodes::TRAIN_WHEEL_LB1);
		TryRenderAtomic(thisTrain->m_aTrainNodes, eTrainNodes::TRAIN_NUM_NODES, eTrainNodes::TRAIN_WHEEL_LB2);
		TryRenderAtomic(thisTrain->m_aTrainNodes, eTrainNodes::TRAIN_NUM_NODES, eTrainNodes::TRAIN_WHEEL_LB3);

		TryRenderAtomic(thisTrain->m_aTrainNodes, eTrainNodes::TRAIN_NUM_NODES, eTrainNodes::TRAIN_WHEEL_LF1);
		TryRenderAtomic(thisTrain->m_aTrainNodes, eTrainNodes::TRAIN_NUM_NODES, eTrainNodes::TRAIN_WHEEL_LF2);
		TryRenderAtomic(thisTrain->m_aTrainNodes, eTrainNodes::TRAIN_NUM_NODES, eTrainNodes::TRAIN_WHEEL_LF3);

		TryRenderAtomic(thisTrain->m_aTrainNodes, eTrainNodes::TRAIN_NUM_NODES, eTrainNodes::TRAIN_WHEEL_RB1);
		TryRenderAtomic(thisTrain->m_aTrainNodes, eTrainNodes::TRAIN_NUM_NODES, eTrainNodes::TRAIN_WHEEL_RB2);
		TryRenderAtomic(thisTrain->m_aTrainNodes, eTrainNodes::TRAIN_NUM_NODES, eTrainNodes::TRAIN_WHEEL_RB3);

		TryRenderAtomic(thisTrain->m_aTrainNodes, eTrainNodes::TRAIN_NUM_NODES, eTrainNodes::TRAIN_WHEEL_RF1);
		TryRenderAtomic(thisTrain->m_aTrainNodes, eTrainNodes::TRAIN_NUM_NODES, eTrainNodes::TRAIN_WHEEL_RF2);
		TryRenderAtomic(thisTrain->m_aTrainNodes, eTrainNodes::TRAIN_NUM_NODES, eTrainNodes::TRAIN_WHEEL_RF3);
	}
}

void __fastcall InvisibleVehicles::HookedRenderBoat(CBoat* thisBoat) {}

uint8_t* InvisibleVehicles::HookedRwIm3DTransform(uint8_t* pVerts, signed int numVerts, RwMatrix* ltm, unsigned int flags) {
	return nullptr;
}

void __fastcall InvisibleVehicles::HookedRenderEffects(CEntity* thisEntity) {
	if (!thisEntity) {
		return;
	}

	if (!CModelInfo::IsVehicleModelType(thisEntity->m_nModelIndex)) {
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

void InvisibleVehicles::HookedRenderShadows(CVehicle* thisVehicle, VEH_SHD_TYPE shadowType) {}

void __fastcall InvisibleVehicles::HookedCVehicleDoHeadLightBeam(CVehicle* thisVehicle, void* edx, int a2, CMatrix* matrix, char a4) {}

void __fastcall InvisibleVehicles::HookedCVehicleAddExhaustParticles(CVehicle* thisVehicle) {}

void __fastcall InvisibleVehicles::HookedCVehicleAddWaterSplashParticles(CVehicle* thisVehicle) {}

void __fastcall InvisibleVehicles::HookedCVehicleAddSingleWheelParticles(CVehicle* thisVehicle, void* edx, int wheelState, int a3, float a4, float a5, CColPoint* a6, RwV3d* from, int a8, signed int a9, int _surfaceType, int _bloodState, char a12) {}

void __fastcall InvisibleVehicles::HookedCVehicleAddDamagedVehicleParticles(CVehicle* thisVehicle) {}
