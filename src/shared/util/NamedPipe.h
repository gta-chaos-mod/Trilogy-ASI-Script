#pragma once

#include "plugin.h"

#include <thread>

#include "DrawHelper.h"
#include "DrawVoting.h"
#include "EffectDatabase.h"
#include "RandomHelper.h"

class NamedPipe
{
public:
	static void OnAttach();

	static void SetupPipe();

	static void CallFunction(std::string text);
};
