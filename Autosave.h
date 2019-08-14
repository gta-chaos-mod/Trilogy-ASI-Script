#pragma once

#include "TimedEffect.h"

#include "CGenericGameStorage.h"

class Autosave : public TimedEffect
{
private:
	char* gamePath = reinterpret_cast<char*>(0xC92368);
	bool didSave = false;

public:
	Autosave();

	void HandleTick() override;
};
