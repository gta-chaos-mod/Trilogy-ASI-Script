#include "DVDScreensaverEffect.h"

bool DVDScreensaverEffect::goingDown = false;
bool DVDScreensaverEffect::goingRight = false;

float DVDScreensaverEffect::x = 0.0f;
float DVDScreensaverEffect::y = 0.0f;

DVDScreensaverEffect::DVDScreensaverEffect()
	: EffectBase("effect_dvd_screensaver")
{
	AddType("hud");
}

EffectBase* DVDScreensaverEffect::SetEffectDuration(int duration) {
	EffectBase::SetEffectDuration(duration / 3);
	return this;
}

void DVDScreensaverEffect::Enable() {
	EffectBase::Enable();

	x = RandomHelper::Random(0.0f, SCREEN_WIDTH - SCREEN_COORD(400.0f));
	y = RandomHelper::Random(0.0f, SCREEN_HEIGHT - SCREEN_COORD(400.0f));

	Events::drawHudEvent.before += DrawScreensaver;
}

void DVDScreensaverEffect::Disable() {
	Events::drawHudEvent.before -= DrawScreensaver;

	EffectBase::Disable();
}

void DVDScreensaverEffect::HandleTick() {
	EffectBase::HandleTick();

	if (goingRight) {
		x += CalculateTick(0.2f);
		if (SCREEN_COORD(x) >= SCREEN_WIDTH - SCREEN_COORD(400.0f)) {
			goingRight = false;
		}
	}
	else {
		x -= CalculateTick(0.2f);
		if (x < 0.0f) {
			goingRight = true;
		}
	}

	if (goingDown) {
		y += CalculateTick(0.2f);
		if (SCREEN_COORD(y) >= SCREEN_HEIGHT - SCREEN_COORD(400.0f)) {
			goingDown = false;
		}
	}
	else {
		y -= CalculateTick(0.2f);
		if (y < 0.0f) {
			goingDown = true;
		}
	}
}

std::pair<float, float> DVDScreensaverEffect::CalculateStartingXY(int boxNumber) {
	switch (boxNumber) {
		case 0:
		case 1:
		default: {
			return std::make_pair(0.0f, 0.0f);
		}
		case 2: {
			return std::make_pair(SCREEN_COORD(x) + SCREEN_COORD(400.0f), SCREEN_COORD(y));
		}
		case 3: {
			return std::make_pair(SCREEN_COORD(x), SCREEN_COORD(y) + SCREEN_COORD(400.0f));
		}
	}
}

std::pair<float, float> DVDScreensaverEffect::CalculateWidthHeight(int boxNumber) {
	switch (boxNumber) {
		case 0:
		default: {
			return std::make_pair(SCREEN_WIDTH, SCREEN_COORD(y));
		}
		case 1: {
			return std::make_pair(SCREEN_COORD(x), SCREEN_HEIGHT);
		}
		case 2:
		case 3: {
			return std::make_pair(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
	}
}

void DVDScreensaverEffect::DrawScreensaver() {
	if (FrontEndMenuManager.m_bMenuActive) {
		return;
	}

	for (int i = 0; i < 4; i++) {
		std::pair<float, float> start = CalculateStartingXY(i);
		std::pair<float, float> end = CalculateWidthHeight(i);

		CRect rect = CRect(start.first, start.second, end.first, end.second);
		CSprite2d::DrawRect(rect, CRGBA(0, 0, 0, 255));
	}
}
