#include "TunnelVisionEffect.h"

TunnelVisionEffect::TunnelVisionEffect()
	: EffectBase("effect_tunnel_vision")
{
	AddType("hud");
}

EffectBase* TunnelVisionEffect::SetEffectDuration(int duration) {
	EffectBase::SetEffectDuration(duration / 3);
	return this;
}

void TunnelVisionEffect::Enable() {
	EffectBase::Enable();

	Events::drawHudEvent.before += DrawTunnelVision;
}

void TunnelVisionEffect::Disable() {
	Events::drawHudEvent.before -= DrawTunnelVision;

	EffectBase::Disable();
}

void TunnelVisionEffect::DrawTunnelVision() {
	if (FrontendMenuManager.m_bMenuVisible) {
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
