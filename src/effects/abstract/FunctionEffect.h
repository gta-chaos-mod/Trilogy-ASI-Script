// Copyright (c) 2019 Lordmau5
#pragma once

#include "EffectPlaceholder.h"

class FunctionEffect : public EffectPlaceholder
{
private:
	void* function = nullptr;

public:
	FunctionEffect(void* _function, int _duration, const std::string& _description);
	FunctionEffect(void* _function, int _duration, const std::string& _description, const char* _type);

	void Enable() override;
};
