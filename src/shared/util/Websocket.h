#pragma once

#include "util/Config.h"
#include "util/DrawHelper.h"
#include "util/DrawVoting.h"
#include "util/RandomHelper.h"

#include <thread>

class Websocket
{
    static inline uWS::App  *globalApp;
    static inline uWS::Loop *loop;

    struct EmptySocketData
    {
    };

    static void SetupWebsocketThread ();

public:
    static void Setup ();

    static void CallFunction (std::string text);

    static void SendWebsocketMessage (nlohmann::json data);
    static void SendCrowdControlResponse (int effectID, int response);
};
