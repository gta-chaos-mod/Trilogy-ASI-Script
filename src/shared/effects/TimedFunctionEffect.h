#pragma once

#include "util/EffectBase.h"

class TimedFunctionEffect : public EffectBase
{
private:
	void* function = nullptr;
	bool* address = nullptr;

public:
	TimedFunctionEffect(std::string id, void* function, int address);

	void Disable() override;

	void HandleTick() override;
};
