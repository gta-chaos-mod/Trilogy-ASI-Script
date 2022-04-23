#pragma once

#include <util/Config.h>
#include <util/DrawHelper.h>
#include <util/DrawVoting.h>
#include <util/RandomHelper.h>

#include <thread>

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
