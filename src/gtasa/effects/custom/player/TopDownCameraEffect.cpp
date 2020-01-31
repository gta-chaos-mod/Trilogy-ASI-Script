#include "TopDownCameraEffect.h"

TopDownCameraEffect::TopDownCameraEffect()
	: EffectBase("effect_top_down_camera") {}

bool TopDownCameraEffect::CanActivate() {
	return Teleportation::CanTeleport();
}

void TopDownCameraEffect::Disable() {
	Command<eScriptCommands::COMMAND_RESTORE_CAMERA_JUMPCUT>();

	EffectBase::Disable();
}

void TopDownCameraEffect::HandleTick() {
	EffectBase::HandleTick();

	CPlayerPed* player = FindPlayerPed();
	CVector pos = player->GetPosition();
	float offset = 40.0f;

	CVehicle* vehicle = FindPlayerVehicle(-1, false);
	if (vehicle) {
		float speed = vehicle->m_vecMoveSpeed.Magnitude();
		if (speed > 1.2f) {
			speed = 1.2f;
		}

		offset += std::max(0.0f, std::min(speed * 40.0f, 40.0f));
	}

	CVector playerOffset = CVector(pos.x, pos.y, pos.z + 2.0f);
	CVector cameraPos = CVector(playerOffset.x, playerOffset.y, playerOffset.z + offset);

	CColPoint outColPoint;
	CEntity* outEntity;

	// TODO: Which variable? X, Y or Z for the look direction?

	if (CWorld::ProcessLineOfSight(playerOffset, cameraPos, outColPoint, outEntity, true, true, true, true, true, true, true, true)) {
		Command<eScriptCommands::COMMAND_SET_FIXED_CAMERA_POSITION>(outColPoint.m_vecPoint.x, outColPoint.m_vecPoint.y, outColPoint.m_vecPoint.z, 0.0f, 0.0f, 0.0f);
	}
	else {
		Command<eScriptCommands::COMMAND_SET_FIXED_CAMERA_POSITION>(cameraPos.x, cameraPos.y, cameraPos.z, 0.0f, 0.0f, 0.0f);
	}

	Command<eScriptCommands::COMMAND_POINT_CAMERA_AT_POINT>(pos.x, pos.y, pos.z, 2);

	TheCamera.m_fGenerationDistMultiplier = 10.0f;
	TheCamera.m_fLODDistMultiplier = 10.0f;
}
