#pragma once

#include <thread>

#include "Config.h"
#include "DrawHelper.h"
#include "DrawVoting.h"
// #include "EffectDatabase.h"
#include "RandomHelper.h"

class Websocket
{
private:
    static inline uWS::App *globalApp;

    struct EmptySocketData
    {
    };

    static void SetupWebsocketThread ();

public:
    static void Setup ();

    static void SendCrowdControlResponse (int effectID, int response);

    static void CallFunction (std::string text);
};
