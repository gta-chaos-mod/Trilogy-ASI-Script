#pragma once

#include "util/Config.h"
#include "util/DrawHelper.h"
#include "util/DrawVoting.h"
#include "util/RandomHelper.h"
#include "util/easywsclient/easywsclient.hpp"

#include <thread>

class Websocket
{
    static inline std::atomic_bool reconnectionHandlerInitialized = false;

    static inline std::string GUI_WEBSOCKET_URL = "ws://localhost:9001";
    static inline std::string CC_WEBSOCKET_URL  = "ws://localhost:9002";

    // Websocket Client
    static inline std::atomic_bool                         stopClient = false;
    static inline std::unique_ptr<easywsclient::WebSocket> wsClient   = NULL;

    static void SetupReconnectionHandler ();

    static void        Cleanup ();
    static std::string GetWebsocketURL ();
    static void        SetupClientThread ();

public:
    static void Setup ();

    static bool IsClientConnected ();
    static bool IsClientConnectingOrConnected ();
    static void ReconnectClient ();

    static void CallFunction (std::string text);

    static void SendWebsocketMessage (nlohmann::json data);
    static void SendCrowdControlResponse (int effectID, int status);
};
