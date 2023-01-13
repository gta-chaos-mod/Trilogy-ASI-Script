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
}

std::string
Websocket::GetWebsocketURL ()
{
    return CONFIG_CC_ENABLED ? CC_WEBSOCKET_URL : GetGUIWebsocketURL ();
}

std::string
Websocket::GetGUIWebsocketURL ()
{
    std::string url ("ws://localhost:");
    url.append (std::to_string (GUI_WEBSOCKET_PORT));

    return url;
}

void
Websocket::SetupClientThread ()
{
    while (true)
    {
        if (!wsClient.get ())
        {
            if (IsClientConnectingOrConnected ()) continue;

            try
            {
                using easywsclient::WebSocket;

                std::shared_ptr<WebSocket> newClient (
                    WebSocket::from_url (GetWebsocketURL ()));
                wsClient = newClient;

                if (newClient == nullptr
                    || newClient->getReadyState () == WebSocket::CLOSED)
                {
                    continue;
                }

                while (newClient != nullptr
                       && newClient->getReadyState () == WebSocket::OPEN)
                {
                    newClient->poll (50);

                    newClient->dispatch ([] (const std::string &message)
                                         { CallFunction (message); });
                }

                Cleanup ();
            }
            catch (...)
            {
                // Error connecting to socket
            }
        }
        else
        {
            std::this_thread::sleep_for (std::chrono::seconds (3));

            if (!IsClientConnectingOrConnected ())
            {
                Cleanup ();
            }
        }
    }
}

void
Websocket::SetupConnectionHandler ()
{
    if (connectionHandlerInitialized) return;

#ifdef _WIN32
    INT     rc;
    WSADATA wsaData;

    rc = WSAStartup (MAKEWORD (2, 2), &wsaData);
    if (rc)
    {
        fprintf (stderr, "[GTA Chaos] WSAStartup Failed. Error: %d\n", rc);
        return;
    }
#endif

    std::thread setupThread (SetupClientThread);
    setupThread.detach ();

    connectionHandlerInitialized = true;
}

void
Websocket::Setup ()
{
    Cleanup ();

    SetupConnectionHandler ();
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
                eVoteChoice pickedChoice         = data.at ("pickedChoice");

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
