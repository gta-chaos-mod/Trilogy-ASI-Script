#include "NamedPipe.h"

void NamedPipe::OnAttach() {
	HANDLE hPipe;
	char buffer[1024] = "";
	char text[1024] = "";
	DWORD dwRead;

	std::string myProcID = "\\\\.\\pipe\\GTATrilogyChaosModPipe";
	std::string To(myProcID.begin(), myProcID.end());

	hPipe = CreateNamedPipe(To.c_str(),
		PIPE_ACCESS_DUPLEX | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
		PIPE_WAIT,
		1,
		1024 * 16,
		1024 * 16,
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL);
	while (hPipe != NULL)
	{
		if (ConnectNamedPipe(hPipe, NULL) != FALSE)
		{
			while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE)
			{
				for (unsigned int i = 0; i < strlen(buffer); i++)
				{
					if (isprint(buffer[i]) == false)
						break;

					text[i] = buffer[i];
				}
				CallFunction(std::string(text));
				memset(text, 0, sizeof(text));
			}
			FlushFileBuffers(hPipe);
		}
		DisconnectNamedPipe(hPipe);
	}
}

void NamedPipe::SetupPipe() {
	std::thread t1([]() { OnAttach(); });
	t1.detach();
}

void NamedPipe::CallFunction(std::string text) {
	char c_state[32] = {};
	char c_rest[512] = {};
	sscanf(text.c_str(), "%[^:]:%[^\t\n]", &c_state, &c_rest);

	std::string state(c_state);
	std::string rest(c_rest);

	if (state == "time") {
		int remaining = 0;
		int cooldown = 0;
		char mode[64] = {};
		sscanf(rest.c_str(), "%d,%d,%[^:]", &remaining, &cooldown, &mode);

		DrawHelper::UpdateCooldown(remaining, cooldown, std::string(mode));
	}
	else if (state == "set_seed") {
		RandomHelper::SetSeed(std::stoi(rest));
	}
	else if (state == "votes") {
		char c_effects[3][128];
		int c_votes[3];
		int pickedChoice = -1;
		sscanf(rest.c_str(), "%[^;];%d;;%[^;];%d;;%[^;];%d;;%d",
			&c_effects[0], &c_votes[0],
			&c_effects[1], &c_votes[1],
			&c_effects[2], &c_votes[2],
			&pickedChoice
		);

		DrawVoting::UpdateVotes(c_effects, c_votes, pickedChoice);
	}
	else {
		EffectDatabase::HandleFunction(state, rest);
	}
}
