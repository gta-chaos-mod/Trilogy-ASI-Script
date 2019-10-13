#pragma once

#include "effects/EffectPlaceholder.h"

#include "CCheat.h"

class GetJetpackCheat : public EffectPlaceholder
{
public:
	GetJetpackCheat();

	void Enable() override;
};
