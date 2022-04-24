#include "Websocket.h"

#include "util/EffectHandler.h"

void
Websocket::SetupWebsocketThread ()
{
    auto app = uWS::App ();

    auto socketConfig = uWS::App::WebSocketBehavior<EmptySocketData> ();
    socketConfig.open = [] (auto *ws)
    {
        ws->subscribe ("broadcast");
        globalApp->publish ("broadcast", "Hello!", uWS::OpCode::TEXT, true);
    };
    socketConfig.message
        = [] (auto *ws, std::string_view message, uWS::OpCode opCode)
    { CallFunction (std::string (message)); };

    app.ws<EmptySocketData> ("/*", std::move (socketConfig));

    app.listen (9001, [] (auto *listenSocket) {});

    globalApp = &app;
    loop      = uWS::Loop::get ();

    app.run ();
}

void
Websocket::Setup ()
{
    std::thread setupThread ([] () { SetupWebsocketThread (); });
    setupThread.detach ();
}

void
Websocket::CallFunction (std::string text)
{
    // Empty try-catch to make sure the game doesn't crash if we get invalid
    // JSON data that can't be parsed
    try
    {
        auto json = nlohmann::json::parse (text);

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

            std::vector<std::string> effects      = data.at ("effects");
            std::vector<int>         votes        = data.at ("votes");
            int                      pickedChoice = data.at ("pickedChoice");

            DrawVoting::UpdateVotes (effects, votes, pickedChoice);
        }
        else if (type == "effect")
        {
            auto data = json.at ("data");

            EffectHandler::HandleFunction (data);
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
    loop->defer (
        [json] () {
            globalApp->publish ("broadcast", json.dump (), uWS::OpCode::TEXT,
                                true);
        });
}

void
Websocket::SendCrowdControlResponse (int effectID, int response)
{
    nlohmann::json json;

    json["type"]             = "CrowdControl";
    json["data"]["id"]       = effectID;
    json["data"]["response"] = response;

    SendWebsocketMessage (json);
}
