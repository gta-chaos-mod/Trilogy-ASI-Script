#include "Websocket.h"

void
Websocket::SendCrowdControlResponse (int effectID, int response)
{
    // TODO: JSONify
    std::string message (std::to_string (effectID));
    message.append (":");
    message.append (std::to_string (response));

    std::thread sendMessageThread (
        [message] () {
            globalApp->publish ("broadcast", message, uWS::OpCode::TEXT, true);
        });
    sendMessageThread.detach ();
}

void
Websocket::Setup ()
{
    std::thread setupThread ([] () { SetupWebsocketThread (); });
    setupThread.detach ();
}

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

    app.listen (9001, [] (auto *listen_socket) {});

    globalApp = &app;

    app.run ();
}

void
Websocket::CallFunction (std::string text)
{
    // Empty try-catch to make sure the game doesn't crash if we get invalid
    // JSON data that can't be parsed
    try
    {
        auto json = nlohmann::json::parse (text);

        std::string type = json["type"];

        if (type == "time")
        {
            auto data = json["data"];

            int         remaining = data["remaining"];
            int         cooldown  = data["cooldown"];
            std::string mode      = data["mode"];

            DrawHelper::UpdateCooldown (remaining, cooldown, mode);
        }
        else if (type == "seed")
        {
            int seed = json["data"];

            RandomHelper::SetSeed (seed);
        }
        else if (type == "votes")
        {
            auto data = json["data"];

            std::vector<std::string> effects      = data["effects"];
            std::vector<int>         votes        = data["votes"];
            int                      pickedChoice = data["pickedChoice"];

            DrawVoting::UpdateVotes (effects, votes, pickedChoice);
        }
        else
        {
            // EffectDatabase::HandleFunction (state, rest);
        }
    }
    catch (...)
    {
        // Wrong JSON data received, do nothing
    }
}
