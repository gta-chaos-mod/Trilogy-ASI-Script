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

    static void SendCCMessage (std::string message);

    struct PerSocketData
    {
    };

public:
    static void Setup ();

    static void OnWebsocketAttach ();

    static void SendCrowdControlResponse (int effectID, int response);

    static void CallFunction (std::string);
};
