#pragma once

#include <thread>

#include "DrawHelper.h"
#include "DrawVoting.h"
// #include "EffectDatabase.h"
#include "RandomHelper.h"

class Websocket
{
private:
    static DWORD WINAPI SendMessageThread (LPVOID lpvParam);

    struct PerSocketData
    {
    };

public:
    static void Setup ();

    static void OnWebsocketAttach ();

    static void SendCrowdControlResponse (int effectID, int response);

    static void CallFunction (std::string);
};
