// Copyright (c) 2019 Lordmau5
#include "GameSpeed.h"

GameSpeed::GameSpeed(float _gameSpeed, int _duration, std::string _description)
	: TimedEffect(_duration, _description, "game_speed") {
	gameSpeed = _gameSpeed;
}

void GameSpeed::Disable() {
	CTimer::ms_fTimeScale = 1.0f;
	*audioSpeed = 1.0f;

	TimedEffect::Disable();
}

void GameSpeed::HandleTick() {
	CTimer::ms_fTimeScale = gameSpeed;
	float speed = gameSpeed;
	if (speed > 1.0f) {
		speed = 1.0f + ((speed - 1.0f) * 0.175f);
	}
	*audioSpeed = speed;

	for (CVehicle* vehicle : CPools::ms_pVehiclePool) {
		if (vehicle->m_pDriver && !vehicle->IsDriver(FindPlayerPed())) {
			CCarCtrl::SwitchVehicleToRealPhysics(vehicle);
		}
	}
}
