#include "GameSpeed.h"

GameSpeed::GameSpeed(float _gameSpeed, int _duration, std::string _description)
	: TimedEffect(_duration, _description, "game_speed") {
	gameSpeed = _gameSpeed;
}

void GameSpeed::Disable() {
	CTimer::ms_fTimeScale = 1.0f;

	TimedEffect::Disable();
}

void GameSpeed::HandleTick() {
	CTimer::ms_fTimeScale = gameSpeed;
}
