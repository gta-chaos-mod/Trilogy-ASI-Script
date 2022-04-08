#include "Websocket.h"

void
Websocket::SendCrowdControlResponse (int effectID, int response)
{
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
    std::thread setupThread ([] () { OnWebsocketAttach (); });
    setupThread.detach ();
}

void
Websocket::OnWebsocketAttach ()
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
    char c_state[32] = {};
    char c_rest[512] = {};
    sscanf (text.c_str (), "%[^:]:%[^\t\n]", &c_state, &c_rest);

    std::string state (c_state);
    std::string rest (c_rest);

    if (state == "time")
    {
        int  remaining = 0;
        int  cooldown  = 0;
        char mode[64]  = {};
        sscanf (rest.c_str (), "%d,%d,%[^:]", &remaining, &cooldown, &mode);

        DrawHelper::UpdateCooldown (remaining, cooldown, std::string (mode));
    }
    else if (state == "set_seed")
    {
        RandomHelper::SetSeed (std::stoi (rest));
    }
    else if (state == "votes")
    {
        char c_effects[3][128];
        int  c_votes[3];
        int  pickedChoice = -1;
        sscanf (rest.c_str (), "%[^;];%d;;%[^;];%d;;%[^;];%d;;%d",
                &c_effects[0], &c_votes[0], &c_effects[1], &c_votes[1],
                &c_effects[2], &c_votes[2], &pickedChoice);

        DrawVoting::UpdateVotes (c_effects, c_votes, pickedChoice);
    }
    else
    {
        // EffectDatabase::HandleFunction (state, rest);
    }
}
