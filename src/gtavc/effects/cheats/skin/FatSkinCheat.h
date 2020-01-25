#pragma once

#include "effects/EffectPlaceholder.h"

class FatSkinCheat : public EffectPlaceholder
{
private:
	float* bodyWidth = reinterpret_cast<float*>(0x68E058);

public:
	FatSkinCheat();

	void Enable() override;
};
