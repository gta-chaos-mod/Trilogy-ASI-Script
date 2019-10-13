#include "InvisibleVehiclesEffect.h"

InvisibleVehiclesEffect::InvisibleVehiclesEffect()
	: EffectBase("effect_invisible_vehicles")
{
	AddType("invisible_vehicles");
}

void InvisibleVehiclesEffect::InitializeHooks() {
	EffectBase::InitializeHooks();

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

void InvisibleVehiclesEffect::Enable() {
	EffectBase::Enable();

	oldForceVehicleLightsOff = CVehicle::ms_forceVehicleLightsOff;
}

void InvisibleVehiclesEffect::Disable() {
	CVehicle::ms_forceVehicleLightsOff = oldForceVehicleLightsOff;

	EffectBase::Disable();
}

void InvisibleVehiclesEffect::HandleTick() {
	EffectBase::HandleTick();

	CVehicle::ms_forceVehicleLightsOff = true;
}

void InvisibleVehiclesEffect::TryRenderAtomic(RwFrame* frameArray[], int size, int slot) {
	if (frameArray && slot < size && frameArray[slot]) {
		RpAtomic* atomic = (RpAtomic*)GetFirstObject(frameArray[slot]);
		if (atomic) {
			atomic->renderCallBack(atomic);
		}
	}
}

void __fastcall InvisibleVehiclesEffect::HookedRenderAutomobile(CAutomobile* thisAutomobile) {}

void __fastcall InvisibleVehiclesEffect::HookedRenderHeli(CHeli* thisHeli) {}

void __fastcall InvisibleVehiclesEffect::HookedRenderBike(CBike* thisBike) {}

void __fastcall InvisibleVehiclesEffect::HookedRenderPlane(CPlane* thisPlane) {}

void __fastcall InvisibleVehiclesEffect::HookedRenderTrain(CTrain* thisTrain) {}

void __fastcall InvisibleVehiclesEffect::HookedRenderBoat(CBoat* thisBoat) {}

uint8_t* InvisibleVehiclesEffect::HookedRwIm3DTransform(uint8_t* pVerts, signed int numVerts, RwMatrix* ltm, unsigned int flags) {
	return nullptr;
}

void __fastcall InvisibleVehiclesEffect::HookedRenderEffects(CEntity* thisEntity) {
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

void InvisibleVehiclesEffect::HookedRenderShadows(CVehicle* thisVehicle, VEH_SHD_TYPE shadowType) {}

void __fastcall InvisibleVehiclesEffect::HookedCVehicleDoHeadLightBeam(CVehicle* thisVehicle, void* edx, int a2, CMatrix* matrix, char a4) {}

void __fastcall InvisibleVehiclesEffect::HookedCVehicleAddExhaustParticles(CVehicle* thisVehicle) {}

void __fastcall InvisibleVehiclesEffect::HookedCVehicleAddWaterSplashParticles(CVehicle* thisVehicle) {}

void __fastcall InvisibleVehiclesEffect::HookedCVehicleAddSingleWheelParticles(CVehicle* thisVehicle, void* edx, int wheelState, int a3, float a4, float a5, CColPoint* a6, RwV3d* from, int a8, signed int a9, int _surfaceType, int _bloodState, char a12) {}

void __fastcall InvisibleVehiclesEffect::HookedCVehicleAddDamagedVehicleParticles(CVehicle* thisVehicle) {}
