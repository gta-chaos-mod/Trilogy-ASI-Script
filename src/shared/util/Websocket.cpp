#include "Websocket.h"

#include "util/Config.h"
#include "util/EffectHandler.h"

#ifdef _WIN32
#pragma comment(lib, "ws2_32")
#include <WinSock2.h>
#endif

void
Websocket::Cleanup ()
{
    if (wsClient.get () != nullptr)
    {
        wsClient->close ();
    }

    wsClient.reset ();

#ifdef _WIN32
    WSACleanup ();
#endif
}

std::string
Websocket::GetWebsocketURL ()
{
    return CONFIG_CC_ENABLED ? CC_WEBSOCKET_URL : GUI_WEBSOCKET_URL;
}

void
Websocket::SetupClientThread ()
{
    try
    {
        using easywsclient::WebSocket;

#ifdef _WIN32
        INT     rc;
        WSADATA wsaData;

        rc = WSAStartup (MAKEWORD (2, 2), &wsaData);
        if (rc)
        {
            printf ("WSAStartup Failed.\n");
            return;
        }
#endif

        std::unique_ptr<WebSocket> newClient (
            WebSocket::from_url (GetWebsocketURL ()));
        wsClient = std::move (newClient);

        if (wsClient.get () == nullptr
            || wsClient->getReadyState () == WebSocket::CLOSED)
        {
            return;
        }

        while (wsClient.get () != nullptr
               && wsClient->getReadyState () != WebSocket::CLOSED)
        {
            if (!wsClient.get ()) break;
            wsClient->poll ();

            if (!wsClient.get ()) break;
            wsClient->dispatch ([] (const std::string &message)
                                { CallFunction (message); });
        }
    }
    catch (...)
    {
        // Error connecting to socket
    }
}

void
Websocket::SetupReconnectionHandler ()
{
    if (reconnectionHandlerInitialized) return;

    std::thread reconnectionThread (
        [] ()
        {
            while (true)
            {
                std::this_thread::sleep_for (std::chrono::seconds (3));

                if (!Websocket::IsClientConnectingOrConnected ())
                    Websocket::Setup ();
            }
        });
    reconnectionThread.detach ();

    reconnectionHandlerInitialized = true;
}

void
Websocket::Setup ()
{
    SetupReconnectionHandler ();

    Cleanup ();

    std::thread setupThread ([] () { SetupClientThread (); });
    setupThread.detach ();
}

bool
Websocket::IsClientConnected ()
{
    using easywsclient::WebSocket;

    return wsClient.get () != nullptr
           && wsClient->getReadyState () == WebSocket::OPEN;
}

bool
Websocket::IsClientConnectingOrConnected ()
{
    if (IsClientConnected ()) return true;

    using easywsclient::WebSocket;

    return wsClient.get () != nullptr
           && wsClient->getReadyState () == WebSocket::CONNECTING;
}

void
Websocket::ReconnectClient ()
{
    Setup ();
}

void
Websocket::CallFunction (std::string text)
{
    // Empty try-catch to make sure the game doesn't crash if we get invalid
    // JSON data that can't be parsed
    try
    {
        auto json = nlohmann::json::parse (text);

        if (json.value ("IsCrowdControl", false) && CONFIG_CC_ENABLED)
        {
            int type = json.at ("type");
            int id   = json.at ("id");

            // Request Type 1 == Start
            if (type != 1) return;

            std::string effectID = json.at ("effectID");
            std::string name     = json.value ("name", effectID);

            int         duration = json.value ("realDuration", 1000 * 30);
            std::string viewer   = json.value ("viewer", "The Crowd");

            // Mods
            json["crowdControlID"] = id;
            json["displayName"]    = name;
            json["subtext"]        = viewer;
            json["duration"]       = duration;

            EffectHandler::HandleFunction (json);
        }
        else
        {
            std::string type = json.at ("type");

            if (type == "time")
            {
                auto data = json.at ("data");

                int         remaining = data.at ("remaining");
                int         cooldown  = data.at ("cooldown");
                std::string mode      = data.at ("mode");

                DrawHelper::UpdateCooldown (remaining, cooldown, mode);
            }
            else if (type == "votes")
            {
                auto data = json.at ("data");

                std::vector<std::string> effects = data.at ("effects");
                std::vector<int>         votes   = data.at ("votes");
                int pickedChoice                 = data.at ("pickedChoice");

                DrawVoting::UpdateVotes (effects, votes, pickedChoice);
            }
            else if (type == "effect")
            {
                auto data = json.at ("data");

                EffectHandler::HandleFunction (data);
            }
        }
    }
    catch (...)
    {
        // Wrong JSON data received, do nothing
    }
}

void
Websocket::SendWebsocketMessage (nlohmann::json json)
{
    if (wsClient.get () == nullptr) return;

    wsClient->send (json.dump ());
}

void
Websocket::SendCrowdControlResponse (int effectID, int status)
{
    nlohmann::json json;

    json["id"]     = effectID;
    json["status"] = status;

    SendWebsocketMessage (json);
}
