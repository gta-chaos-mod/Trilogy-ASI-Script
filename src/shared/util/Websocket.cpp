#include "Websocket.h"

#include "util/Config.h"
#include "util/EffectHandler.h"

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
Websocket::Setup ()
{
    ix::initNetSystem ();

    wsClient.setUrl (GetWebsocketURL ());

    wsClient.setOnMessageCallback (
        [] (const ix::WebSocketMessagePtr &msg)
        {
            if (msg->type == ix::WebSocketMessageType::Message)
            {
                CallFunction (msg->str);
                // std::cout << "received message: " << msg->str << std::endl;
                // std::cout << "> " << std::flush;
            }
            else if (msg->type == ix::WebSocketMessageType::Open)
            {
                // std::cout << "Connection established" << std::endl;
                // std::cout << "> " << std::flush;
            }
            else if (msg->type == ix::WebSocketMessageType::Error)
            {
                // std::cout << "Connection error: " << msg->errorInfo.reason <<
                // std::endl; std::cout << "> " << std::flush;
            }
        });

    wsClient.start ();
}

bool
Websocket::IsClientConnected ()
{
    return wsClient.getReadyState () == ix::ReadyState::Open;
}

bool
Websocket::IsClientConnectingOrConnected ()
{
    if (IsClientConnected ()) return true;

    return wsClient.getReadyState () == ix::ReadyState::Connecting;
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
    wsClient.send (json.dump ());
}

void
Websocket::SendCrowdControlResponse (int effectID, int status)
{
    nlohmann::json json;

    json["id"]     = effectID;
    json["status"] = status;

    SendWebsocketMessage (json);
}
