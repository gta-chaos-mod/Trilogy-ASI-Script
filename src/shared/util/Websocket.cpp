#include "Websocket.h"

// void
// Websocket::OnAttach ()
// {
//     LPCTSTR pipeName = TEXT ("\\\\.\\pipe\\GTATrilogyChaosModPipe");

//     char  buffer[1024] = "";
//     char  text[1024]   = "";
//     DWORD dwRead;

//     CNamedPipe pipeHandle;
//     pipeHandle.Create (pipeName,
//                        PIPE_ACCESS_DUPLEX | PIPE_TYPE_BYTE |
//                        PIPE_READMODE_BYTE, PIPE_TYPE_BYTE | PIPE_TYPE_MESSAGE
//                        | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 1024 * 16, 1024
//                        * 16, NMPWAIT_USE_DEFAULT_WAIT);

//     while (pipeHandle != NULL)
//     {
//         if (pipeHandle.Connect () != FALSE)
//         {
//             while (pipeHandle.Read (buffer, sizeof (buffer) - 1, &dwRead)
//                    != FALSE)
//             {
//                 for (unsigned int i = 0; i < strlen (buffer); i++)
//                 {
//                     if (isprint (buffer[i]) == false)
//                         break;

//                     text[i] = buffer[i];
//                 }
//                 CallFunction (std::string (text));
//                 memset (text, 0, sizeof (text));
//             }
//             pipeHandle.Flush ();
//         }
//         pipeHandle.Disconnect ();
//     }
// }

void
Websocket::SendCrowdControlResponse (int effectID, int response)
{
    std::string message (std::to_string (effectID));
    message.append (":");
    message.append (std::to_string (response));

    std::thread t1 ([message] () { SendCCMessage (message); });
    t1.detach ();
}

void
Websocket::SendCCMessage (std::string message)
{
    // LPCTSTR pipeName = TEXT ("\\\\.\\pipe\\GTASA_CC_SERVER");

    // if (!WaitNamedPipe (pipeName, 500))
    // {
    //     return -1;
    // }

    // CNamedPipe pipe;
    // if (!pipe.Open (pipeName, GENERIC_READ | GENERIC_WRITE | FILE_SHARE_READ,
    //                 0))
    // {
    //     return -1;
    // }

    // if (!pipe.Write (message, strlen (message)))
    // {
    //     return -1;
    // }

    // pipe.Flush ();
}

void
Websocket::Setup ()
{
    std::thread t1 ([] () { OnWebsocketAttach (); });
    t1.detach ();
}

void
Websocket::OnWebsocketAttach ()
{
    auto app = uWS::App ();

    auto socketConfig = uWS::App::WebSocketBehavior<PerSocketData> ();
    socketConfig.open = [] (auto *ws)
    {
        ws->subscribe ("broadcast");
        globalApp->publish ("broadcast", "Hello!", uWS::OpCode::TEXT, true);
    };
    socketConfig.message
        = [] (auto *ws, std::string_view message, uWS::OpCode opCode)
    {
        auto        msg = std::string (message);
        std::thread messagebox (
            [msg] () { MessageBox (NULL, msg.c_str (), NULL, NULL); });
        messagebox.detach ();
    };

    app.ws<PerSocketData> ("/*", std::move (socketConfig));

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