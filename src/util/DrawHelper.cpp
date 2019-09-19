// Copyright (c) 2019 Lordmau5
#include "DrawHelper.h"

static std::string message;
static int message_remainingDuration;

static std::string bigMessage;
static int bigMessage_remainingDuration;

void DrawHelper::DrawRemainingTimeBar(int remaining) {
	float maxWidth = SCREEN_WIDTH - SCREEN_COORD(8.0f);
	float barWidth = (SCREEN_WIDTH / 1000.0f * remaining) - SCREEN_COORD(8.0f);

	barWidth = max(0.0f, min(barWidth, maxWidth));

	CRect rect = CRect(SCREEN_COORD_LEFT(0.0f), SCREEN_COORD_TOP(0.0f), SCREEN_WIDTH, SCREEN_COORD_TOP(24.0f));
	CSprite2d::DrawRect(rect, CRGBA(0, 0, 0, 225));

	rect = CRect(SCREEN_COORD_LEFT(4.0f), SCREEN_COORD_TOP(4.0f), SCREEN_WIDTH - SCREEN_COORD(4.0f), SCREEN_COORD_TOP(20.0f));
	CSprite2d::DrawRect(rect, CRGBA(25, 75, 128, 200));

	rect = CRect(SCREEN_COORD_LEFT(4.0f), SCREEN_COORD_TOP(4.0f), barWidth + SCREEN_COORD(4.0f), SCREEN_COORD_TOP(20.0f));
	CSprite2d::DrawRect(rect, CRGBA(50, 150, 255, 200));
}

void DrawHelper::DrawVersion() {
	if (KeyPressed(VK_F7) && FrontEndMenuManager.m_bMenuActive) {
		float x = SCREEN_COORD_LEFT(20.0f);
		float y = SCREEN_COORD_BOTTOM(45.0f);

		CFont::SetScaleForCurrentlanguage(SCREEN_MULTIPLIER(1.0f), SCREEN_MULTIPLIER(1.8f));

		CFont::SetOrientation(eFontAlignment::ALIGN_LEFT);
		CFont::SetJustify(false);
		CFont::SetFontStyle(FONT_SUBTITLES);
		CFont::SetDropColor(CRGBA(0, 0, 0, 255));
		CFont::SetDropShadowPosition(0);
		CFont::SetEdge(2);
		CFont::SetBackground(false, false);

		CFont::SetColor(CRGBA(255, 255, 255, 255));
		CFont::PrintString(x, y, GenericUtil::GetModVersion());
	}
}

void DrawHelper::DrawMessages() {
	if (message_remainingDuration > 0) {
		message_remainingDuration -= (int)GenericUtil::CalculateTick();

		float x = SCREEN_COORD_LEFT(5.0f);
		float y = SCREEN_COORD_TOP(27.0f);

		char* helpMessage = (char*)message.c_str();

		CFont::SetCentreSize(SCREEN_WIDTH);
		CFont::SetScaleForCurrentlanguage(SCREEN_MULTIPLIER(1.0f), SCREEN_MULTIPLIER(1.8f));

		CFont::SetOrientation(eFontAlignment::ALIGN_LEFT);
		CFont::SetJustify(false);
		CFont::SetWrapx(SCREEN_WIDTH);
		CFont::SetFontStyle(FONT_SUBTITLES);
		CFont::SetBackground(true, true);
		CFont::SetBackgroundColor(CRGBA(13, 38, 64, 200));
		CFont::SetDropShadowPosition(0);

		CFont::SetColor(CRGBA(255, 255, 255, 200));
		CFont::SetWrapx(SCREEN_COORD(420.0f));
		CFont::PrintString(x, y, helpMessage);
	}
}

void DrawHelper::DrawBigMessages() {
	if (bigMessage_remainingDuration > 0) {
		bigMessage_remainingDuration -= (int)GenericUtil::CalculateTick();

		float x = SCREEN_COORD_CENTER_LEFT(0.0f);
		float y = SCREEN_COORD_CENTER_UP(150.0f);

		char* helpMessage = (char*)bigMessage.c_str();

		CFont::SetCentreSize(SCREEN_WIDTH);
		CFont::SetScaleForCurrentlanguage(SCREEN_MULTIPLIER(2.0f), SCREEN_MULTIPLIER(4.0f));

		CFont::SetOrientation(eFontAlignment::ALIGN_CENTER);
		CFont::SetJustify(false);
		CFont::SetWrapx(SCREEN_WIDTH);
		CFont::SetFontStyle(FONT_MENU);
		CFont::SetDropColor(CRGBA(0, 0, 0, 200));
		CFont::SetDropShadowPosition(0);
		CFont::SetEdge(2);
		CFont::SetBackground(false, false);

		CFont::SetColor(CRGBA(255, 255, 255, 200));
		CFont::SetWrapx(SCREEN_COORD(420.0f));
		CFont::PrintString(x, y, helpMessage);
	}
}

void DrawHelper::DrawHelpMessage(std::string _message, int duration, bool playSound) {
	message = _message;
	message_remainingDuration = duration;

	if (playSound) {
		plugin::CallMethod<0x506EA0, void*, int, float, float>((void*)0xB6BC90, 0x20, 0.0f, 1.0f);
	}
}

void DrawHelper::DrawBigMessage(std::string _message, int duration, bool playSound) {
	bigMessage = _message;
	bigMessage_remainingDuration = duration;

	if (playSound) {
		plugin::CallMethod<0x506EA0, void*, int, float, float>((void*)0xB6BC90, 0x20, 0.0f, 1.0f);
	}
}

void DrawHelper::DrawRecentEffects(std::list<TimedEffect*> activeEffects) {
	int i = 1;
	for (TimedEffect* effect : activeEffects) {
		if (i > 5) {
			return;
		}

		bool shouldDrawCircle = !effect->isPlaceholder && effect->IsRunning() && effect->enabled;

		float position = shouldDrawCircle ? 90.0f : 25.0f;

		// Draw main text
		CFont::SetCentreSize(SCREEN_WIDTH);
		CFont::SetScaleForCurrentlanguage(SCREEN_MULTIPLIER(1.0f), SCREEN_MULTIPLIER(2.0f));

		CFont::SetOrientation(eFontAlignment::ALIGN_RIGHT);
		CFont::SetJustify(false);
		CFont::SetProportional(!GenericUtil::areEffectsCryptic || effect->immuneToCryptic);
		CFont::SetFontStyle(FONT_SUBTITLES);
		CFont::SetDropColor(CRGBA(0, 0, 0, 200));
		CFont::SetDropShadowPosition(0);
		CFont::SetEdge(1);
		CFont::SetBackground(false, false);

		float stringWidth = CFont::GetStringWidth((char*)effect->GetDescription().c_str(), true, false) - position;
		float offsetWidth = effect->CalculateFadeInOffset(stringWidth);

		float x = SCREEN_COORD_RIGHT(position) + SCREEN_COORD(stringWidth - offsetWidth);
		float y = SCREEN_COORD_BOTTOM(((i + 1) * 70.0f) + 260.0f);

		CFont::SetColor(effect->textColor);
		CFont::PrintString(x, y, (char*)effect->GetDescription().c_str());

		// Draw voter
		if (effect->HasVoter()) {
			CFont::SetCentreSize(SCREEN_WIDTH);
			CFont::SetScaleForCurrentlanguage(SCREEN_MULTIPLIER(0.6f), SCREEN_MULTIPLIER(1.4f));

			CFont::SetOrientation(eFontAlignment::ALIGN_RIGHT);
			CFont::SetJustify(false);
			CFont::SetProportional(true);
			CFont::SetFontStyle(FONT_SUBTITLES);
			CFont::SetDropColor(CRGBA(0, 0, 0, 200));
			CFont::SetDropShadowPosition(0);
			CFont::SetEdge(1);
			CFont::SetBackground(false, false);

			CFont::SetColor(CRGBA(255, 255, 255, 200));
			CFont::PrintString(x, y + SCREEN_COORD(35.0f), (char*)effect->GetVoter().c_str());
		}

		// Draw timed effect circle
		if (shouldDrawCircle) {
			CVector2D center = CVector2D(x + SCREEN_COORD(50.0f), y + SCREEN_COORD(22.0f));

			RwTextureFilterMode filter = rwFILTERLINEAR;
			int alphaBlending = true;

			RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, &alphaBlending);
			RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)(filter));
			RwRenderStateSet(rwRENDERSTATETEXTURERASTER, NULL);

			float angle = (float)effect->GetRemaining() / (float)effect->GetDuration() * 360.0f;

			DrawHelper::DrawCircle(center, SCREEN_MULTIPLIER(24.0f), 360.0f, CRGBA(255, 255, 255, 200));

			DrawHelper::DrawCircle(center, SCREEN_MULTIPLIER(20.0f), 360.0f, CRGBA(13, 38, 64, 200));

			DrawHelper::DrawCircle(center, SCREEN_MULTIPLIER(20.0f), angle, effect->effectColor);
		}

		i++;
	}
}

static const int numVertices = 60;
static RwIm2DVertex vertices[numVertices];

void DrawHelper::DrawCircle(CVector2D position, float radius, float angle, CRGBA color) {
	AppendPie(vertices, numVertices, radius, position, angle, color, 0);
	RwIm2DRenderPrimitive(rwPRIMTYPETRIFAN, vertices, numVertices);
}

void DrawHelper::AppendPie(RwIm2DVertex* vertices, int numCount, float radius, CVector2D center,
	float pie, CRGBA color, float baseRotation)
{
	numCount--;
	float step = ((float)deg2rad(pie)) / (numCount - 1);
	Append(vertices, 0, CVector2D(0, 0), color);
	for (int i = 0; i < numCount; i++)
	{
		float rotation = baseRotation + step * i;
		Append(vertices + 1, i, CVector2D(0, -radius), color);
		Rotate(vertices + i + 1, 1, CVector2D(0, 0), rotation);
	}
	Transform(vertices, numCount + 1, center);
}

///////////////////////////////////////////////////////
void DrawHelper::Transform(RwIm2DVertex* vertices, int numCount, CVector2D transformation)
{
	for (int i = 0; i < numCount; i++)
	{
		vertices[i].x += transformation.x;
		vertices[i].y += transformation.y;
	}
}

///////////////////////////////////////////////////////
void DrawHelper::Append(RwIm2DVertex* vertices, int index, CVector2D coord, CRGBA color)
{
	vertices[index].u = 0; vertices[index].v = 0;
	RwIm2DVertexSetRealRGBA(&vertices[index], color.r, color.g, color.b, color.a);
	vertices[index].x = coord.x;
	vertices[index].y = coord.y;
	vertices[index].z = 0;
}

///////////////////////////////////////////////////////
void DrawHelper::Rotate(RwIm2DVertex* vertices, int numCount, CVector2D origin, float angle)
{
	for (int i = 0; i < numCount; i++)
	{
		float tempx = vertices[i].x - origin.x;
		float tempy = vertices[i].y - origin.y;

		vertices[i].x = origin.x + tempx * cos(angle) - tempy * sin(angle);
		vertices[i].y = origin.y + tempx * sin(angle) + tempy * cos(angle);
	}
}
