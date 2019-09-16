// Copyright (c) 2019 Lordmau5
#pragma once

#include <vector>
#include <utility>

#include "effects/abstract/TimedEffect.h"

#include "util/ColorHelper.h"

#include "CModelInfo.h"
#include "CVehicleModelInfo.h"

class RainbowCars : public TimedEffect
{
private:
	static float hueShift;
	static std::vector<std::pair<RwRGBA*, RwRGBA>> resetMaterialColors;

public:
	RainbowCars(int _duration, std::string _description);

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

private:
	static void SetupRenderEvent(CVehicle* vehicle);
	static void ResetAfterRenderEvent(CVehicle* vehicle);
	static void ModifyCarPaint(CVehicle* vehicle);

	static RpMaterial* MaterialCallback(RpMaterial* material, void* color);
	static RpAtomic* AtomicCallback(RpAtomic* atomic, void* color);
};
