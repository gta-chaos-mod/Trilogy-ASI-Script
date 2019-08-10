#pragma once

#include "plugin.h"
#include "common.h"

#define _USE_MATH_DEFINES

#include <math.h>

#define deg2rad(angleDegrees) ((angleDegrees) * M_PI / 180.0)

#include "GenericUtil.h"
#include "TimedEffect.h"

#include "CFont.h"
#include "CTimer.h"

class DrawHelper
{
public:
	static void DrawHelper::DrawRemainingTimeRects(int remaining);

	static void DrawHelper::DrawRecentEffects(std::list<TimedEffect*> activeEffects);

	static void DrawHelper::DrawMessages();
	static void DrawHelper::DrawBigMessages();
	static void DrawHelper::DrawHelpMessage(std::string message, int duration);
	static void DrawHelper::DrawBigMessage(std::string message, int duration);

	static void DrawHelper::DrawCircle(CVector2D position, float radius, float angle, CRGBA color);
	static void DrawHelper::AppendPie(RwIm2DVertex* vertices, int numCount, float radius, CVector2D center,
		float pie, CRGBA color, float baseRotation);
	static void DrawHelper::Transform(RwIm2DVertex* vertices, int numCount, CVector2D transformation);
	static void DrawHelper::Append(RwIm2DVertex* vertices, int index, CVector2D coord, CRGBA color);
	static void DrawHelper::Rotate(RwIm2DVertex* vertices, int numCount, CVector2D origin, float angle);
};
