#pragma once

#include "plugin.h"

#include <thread>

#include "DrawHelper.h"
#include "DrawVoting.h"
#include "EffectDatabase.h"
#include "RandomHelper.h"

class NamedPipe
{
private:
	static DWORD WINAPI SendMessageThread(LPVOID lpvParam);

public:
	static void OnAttach();

	static void SendCrowdControlResponse(int effectID, int response);

	static void SetupPipe();

	static void CallFunction(std::string);
};
