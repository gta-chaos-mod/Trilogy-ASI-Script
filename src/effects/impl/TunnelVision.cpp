// Copyright (c) 2019 Lordmau5
#include "TunnelVision.h"

TunnelVision::TunnelVision(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "drawing") {}

void TunnelVision::Enable() {
	Events::drawHudEvent.before += DrawTunnelVision;
}

void TunnelVision::Disable() {
	Events::drawHudEvent.before -= DrawTunnelVision;

	TimedEffect::Disable();
}

void TunnelVision::DrawTunnelVision() {
	if (FrontEndMenuManager.m_bMenuActive) {
		return;
	}

	CRect rect = CRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_COORD_CENTER_Y - SCREEN_COORD(200.0f));
	CSprite2d::DrawRect(rect, CRGBA(0, 0, 0, 255));

	rect = CRect(0.0f, SCREEN_COORD_CENTER_Y + SCREEN_COORD(200.0f), SCREEN_WIDTH, SCREEN_HEIGHT);
	CSprite2d::DrawRect(rect, CRGBA(0, 0, 0, 255));

	rect = CRect(0.0f, 0.0f, SCREEN_COORD_CENTER_X - SCREEN_COORD(200.0f), SCREEN_HEIGHT);
	CSprite2d::DrawRect(rect, CRGBA(0, 0, 0, 255));

	rect = CRect(SCREEN_COORD_CENTER_X + SCREEN_COORD(200.0f), 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
	CSprite2d::DrawRect(rect, CRGBA(0, 0, 0, 255));
}
