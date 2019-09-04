// Copyright (c) 2019 Lordmau5
#pragma once

#include "effects/abstract/TimedEffect.h"

#include "util/ColorHelper.h"

#include "CModelInfo.h"
#include "CVehicleModelInfo.h"

class RainbowCars : public TimedEffect
{
public:
	static bool isEnabled;
	static float hueShift;
	static std::list<std::pair<unsigned int*, unsigned int>> RainbowCars::resetEntries;

public:
	RainbowCars(int _duration, std::string _description);

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

	static void RenderVehicleEventBefore(CVehicle* vehicle);
	static void RenderVehicleEventAfter(CVehicle* vehicle);
	static void ModifyCarPaint(CVehicle* vehicle);

	static RpMaterial* MaterialCallback(RpMaterial* material, void* color);
	static RpAtomic* AtomicCallback(RpAtomic* atomic, void* color);
};
