// Copyright (c) 2019 Lordmau5
#pragma once

#include "plugin.h"
#include "common.h"

#define _USE_MATH_DEFINES

#include <math.h>

#define deg2rad(angleDegrees) ((angleDegrees) * M_PI / 180.0)

#include "GenericUtil.h"
#include "effects/abstract/TimedEffect.h"

#include "CFont.h"
#include "CTimer.h"

class DrawHelper
{
public:
	static void DrawRemainingTimeRects(int remaining);

	static void DrawRecentEffects(std::list<TimedEffect*> activeEffects);

	static void DrawMessages();
	static void DrawBigMessages();
	static void DrawHelpMessage(std::string message, int duration);
	static void DrawBigMessage(std::string message, int duration);

	static void DrawCircle(CVector2D position, float radius, float angle, CRGBA color);
	static void AppendPie(RwIm2DVertex* vertices, int numCount, float radius, CVector2D center,
		float pie, CRGBA color, float baseRotation);
	static void Transform(RwIm2DVertex* vertices, int numCount, CVector2D transformation);
	static void Append(RwIm2DVertex* vertices, int index, CVector2D coord, CRGBA color);
	static void Rotate(RwIm2DVertex* vertices, int numCount, CVector2D origin, float angle);
};
