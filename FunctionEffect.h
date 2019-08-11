#pragma once

#include "EffectPlaceholder.h"

class FunctionEffect : public EffectPlaceholder
{
private:
	void* function = nullptr;

public:
	FunctionEffect(void* _function, int _duration, std::string _description);
	FunctionEffect(void* _function, int _duration, std::string _description, std::string _type);

	void Enable() override;
};
