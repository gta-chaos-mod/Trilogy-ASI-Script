#pragma once

#include "TimedEffect.h"

#include "CModelInfo.h"
#include "CVehicleModelInfo.h"

#include "ColorHelper.h"

#include <map>

class RainbowCars : public TimedEffect
{
public:
	static bool isEnabled;
	static float hueShift;
	static std::map<RpMaterial*, RwRGBA> RainbowCars::resetMaterials;

public:
	RainbowCars(int _duration, std::string _description);

	void Enable() override;
	void Disable() override;

	void HandleTick() override;

	static void ModifyCarPaint(CVehicle* vehicle);

	static RpMaterial* MaterialCallback(RpMaterial* material, void* color);
	static RpAtomic* AtomicCallback(RpAtomic* atomic, void* color);
};

