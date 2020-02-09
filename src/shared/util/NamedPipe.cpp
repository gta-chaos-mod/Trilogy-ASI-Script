#include "NamedPipe.h"

#include "npipe.h"

void
NamedPipe::OnAttach ()
{
    LPCTSTR pipeName = TEXT ("\\\\.\\pipe\\GTATrilogyChaosModPipe");

    char  buffer[1024] = "";
    char  text[1024]   = "";
    DWORD dwRead;

    CNamedPipe pipeHandle;
    pipeHandle.Create (pipeName,
                       PIPE_ACCESS_DUPLEX | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
                       PIPE_TYPE_BYTE | PIPE_TYPE_MESSAGE | PIPE_WAIT,
                       PIPE_UNLIMITED_INSTANCES, 1024 * 16, 1024 * 16,
                       NMPWAIT_USE_DEFAULT_WAIT);

    while (pipeHandle != NULL)
    {
        if (pipeHandle.Connect () != FALSE)
        {
            while (pipeHandle.Read (buffer, sizeof (buffer) - 1, &dwRead)
                   != FALSE)
            {
                for (unsigned int i = 0; i < strlen (buffer); i++)
                {
                    if (isprint (buffer[i]) == false)
                        break;

                    text[i] = buffer[i];
                }
                CallFunction (std::string (text));
                memset (text, 0, sizeof (text));
            }
            pipeHandle.Flush ();
        }
        pipeHandle.Disconnect ();
    }
}

void
NamedPipe::SendCrowdControlResponse (int effectID, int response)
{
    std::string message (std::to_string (effectID));
    message.append (":");
    message.append (std::to_string (response));

    DWORD dwThreadId = 0;

    char cstr[1024];
    strcpy (cstr, message.c_str ());

    HANDLE hThread = CreateThread (NULL, 0, SendMessageThread, (LPVOID) cstr, 0,
                                   &dwThreadId);

    if (hThread == NULL)
    {
        return;
    }
    else
    {
        CloseHandle (hThread);
    }
}

DWORD WINAPI
NamedPipe::SendMessageThread (LPVOID lpvParam)
{
    if (lpvParam == NULL)
    {
        return -1;
    }

    char *message = (char *) lpvParam;

    LPCTSTR pipeName = TEXT ("\\\\.\\pipe\\GTASA_CC_SERVER");

    if (!WaitNamedPipe (pipeName, 500))
    {
        return -1;
    }

    CNamedPipe pipe;
    if (!pipe.Open (pipeName, GENERIC_READ | GENERIC_WRITE | FILE_SHARE_READ,
                    0))
    {
        return -1;
    }

    if (!pipe.Write (message, strlen (message)))
    {
        return -1;
    }

    pipe.Flush ();

    return 1;
}

void
NamedPipe::SetupPipe ()
{
    std::thread t1 ([] () { OnAttach (); });
    t1.detach ();
}

void
NamedPipe::CallFunction (std::string text)
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
        EffectDatabase::HandleFunction (state, rest);
    }
}
