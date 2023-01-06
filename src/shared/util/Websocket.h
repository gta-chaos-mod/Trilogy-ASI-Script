#pragma once

#include "util/Config.h"
#include "util/DrawHelper.h"
#include "util/DrawVoting.h"
#include "util/RandomHelper.h"
#include "util/easywsclient/easywsclient.hpp"

#include <thread>

#define GUI_WEBSOCKET_PORT                                                     \
    std::max (1025, std::min (65535, CONFIG ("Chaos.GUIWebsocketPort", 42069)))

class Websocket
{
    static inline bool connectionHandlerInitialized = false;

    static inline std::string CC_WEBSOCKET_URL = "ws://localhost:42070";

    // Websocket Client
    static inline std::atomic_bool                         stopClient = false;
    static inline std::shared_ptr<easywsclient::WebSocket> wsClient   = NULL;

    static void SetupConnectionHandler ();

    static void        Cleanup ();
    static std::string GetWebsocketURL ();
    static void        SetupClientThread ();

public:
    static void Setup ();

    static std::string GetGUIWebsocketURL ();

    static bool IsClientConnected ();
    static bool IsClientConnectingOrConnected ();
    static void ReconnectClient ();

    static void CallFunction (std::string text);

    static void SendWebsocketMessage (nlohmann::json data);
    static void SendCrowdControlResponse (int effectID, int status);
};
