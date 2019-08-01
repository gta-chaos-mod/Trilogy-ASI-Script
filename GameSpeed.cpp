#include "GameSpeed.h"

GameSpeed::GameSpeed(float _gameSpeed, int _duration, std::string _description)
	: TimedEffect(_duration, _description, "gamespeed") {
	gameSpeed = _gameSpeed;
}

void GameSpeed::Enable() {
	CTimer::ms_fTimeScale = gameSpeed;
}

void GameSpeed::Disable() {
	CTimer::ms_fTimeScale = 1.0f;
}
