#include "plugin.h"
#include "common.h"

#include "CHud.h"
#include "CRadar.h"
#include "CWeather.h"

#include "DrawHelper.h"
#include "Gravity.h"
#include "Ped.h"
#include "Player.h"
#include "Teleportation.h"
#include "Vehicle.h"
#include "Wanted.h"
#include "Weapons.h"

#include "CheatHandler.h"
#include "EffectHandler.h"

#include "DisableHUD.h"
#include "DisableRadarBlips.h"

#include "EffectPlaceholder.h"

#include <queue>
#include <thread>

// Version 0.992

using namespace plugin;

enum EffectState {
	WEAPONS = 1,
	WANTED = 2,
	WEATHER = 3,
	SPAWN_VEHICLE = 4,
	GAME_SPEED = 5,
	CHEAT = 6,
	TIMED_CHEAT = 7,
	EFFECT = 8,
	TIMED_EFFECT = 9,
	GRAVITY = 10,
	TELEPORT = 11,
	OTHER = 12,

	TEXT = 20,
	TIME = 21,
};

static CdeclEvent<AddressList<0x53E83C, H_CALL, 0x53EBA2, H_CALL>, PRIORITY_AFTER, ArgPickNone, void()> onDrawAfterFade;

class GTASAChaosMod {
public:
	std::queue<std::function<void()>> queue;
	int remaining;

	std::list<TimedEffect*> activeEffects;

	void ProcessEvents() {
		EmptyQueue();

		for (TimedEffect* effect : activeEffects) {
			effect->TickDown();
		}
		activeEffects.remove_if([](TimedEffect* effect) { return !effect->IsRunning(); });
	}

	void EmptyQueue() {
		if (!queue.empty()) {
			queue.front()();
			queue.pop();
		}
	}

	void QueueEffect(TimedEffect* effect) {
		if (effect == nullptr) {
			return;
		}

		if (effect->isPlaceholder) {
			activeEffects.push_back(effect);
			return;
		}

		auto it = std::find_if(activeEffects.begin(), activeEffects.end(), [effect](TimedEffect* _effect) { return _effect->GetDescription() == effect->GetDescription(); });
		if (it != activeEffects.end()) {
			TimedEffect* _effect = *it;
			if (_effect) {
				_effect->Disable();
			}
			activeEffects.remove(*it);
		}
		else {
			activeEffects.push_back(effect);
		}
	}

	void DrawRemainingTime() {
		DrawHelper::DrawRemainingTimeRects(remaining);
		DrawHelper::DrawRecentEffects(activeEffects);
		DrawHelper::DrawMessages();
	}

	template<typename _Callable, typename... _Args>
	void QueueFunction(_Callable&& __f, _Args&&... __args) {
		queue.push(std::bind(std::forward<_Callable>(__f), std::forward<_Args>(__args)...));
	}

	void CallFunction(std::string text) {
		char c_state[32];
		char c_function[64];
		int duration;
		char c_description[128];
		sscanf(text.c_str(), "%[^:]:%[^:]:%d:%[^:]", &c_state, &c_function, &duration, &c_description);

		std::string state(c_state);
		std::string function(c_function);
		std::string description(c_description);

		EffectState currentState;
		if (state == "weapons") {
			currentState = EffectState::WEAPONS;
		}
		else if (state == "wanted") {
			currentState = EffectState::WANTED;
		}
		else if (state == "weather") {
			currentState = EffectState::WEATHER;
		}
		else if (state == "spawn_vehicle") {
			currentState = EffectState::SPAWN_VEHICLE;
		}
		else if (state == "game_speed") {
			currentState = EffectState::GAME_SPEED;
		}
		else if (state == "cheat") {
			currentState = EffectState::CHEAT;
		}
		else if (state == "timed_cheat") {
			currentState = EffectState::TIMED_CHEAT;
		}
		else if (state == "effect") {
			currentState = EffectState::EFFECT;
		}
		else if (state == "timed_effect") {
			currentState = EffectState::TIMED_EFFECT;
		}
		else if (state == "gravity") {
			currentState = EffectState::GRAVITY;
		}
		else if (state == "other") {
			currentState = EffectState::OTHER;
		}
		else if (state == "teleport") {
			currentState = EffectState::TELEPORT;
		}
		else if (state == "text") {
			currentState = EffectState::TEXT;
		}
		else if (state == "time") {
			currentState = EffectState::TIME;
		}
		else {
			return;
		}

		switch (currentState) {
			case EffectState::WEAPONS: {
				int id = std::stoi(function);
				QueueFunction(Weapons::GiveByID, id);
				QueueEffect(new EffectPlaceholder(duration, description));

				break;
			}
			case EffectState::WANTED: {
				if (function == "plus_two") {
					QueueFunction(Wanted::IncreaseWantedLevel);
				}
				else if (function == "clear") {
					QueueFunction(Wanted::ClearWantedLevel);
				}
				else if (function == "six_stars") {
					QueueFunction(Wanted::SixWantedStars);
				}
				QueueEffect(new EffectPlaceholder(duration, description));

				break;
			}
			case EffectState::WEATHER: {
				QueueFunction(CWeather::ForceWeatherNow, std::stoi(function));
				QueueEffect(new EffectPlaceholder(duration, description));

				break;
			}
			case EffectState::SPAWN_VEHICLE: {
				int modelID = std::stoi(function);
				QueueFunction(Vehicle::SpawnForPlayer, modelID);
				QueueEffect(new EffectPlaceholder(duration, description));

				break;
			}
			case EffectState::GAME_SPEED: {
				float speed;
				sscanf(function.c_str(), "%f", &speed);

				QueueFunction([speed] { CTimer::ms_fTimeScale = speed; });
				QueueEffect(new EffectPlaceholder(duration, description));

				break;
			}
			case EffectState::CHEAT: {
				QueueFunction([function] { CheatHandler::HandleCheat(function); });
				QueueEffect(new EffectPlaceholder(duration, description));

				break;
			}
			case EffectState::TIMED_CHEAT: {
				QueueEffect(CheatHandler::HandleTimedCheat(std::string(function), duration, description));

				break;
			}
			case EffectState::EFFECT: {
				QueueFunction([function] { EffectHandler::HandleEffect(function); });
				QueueEffect(new EffectPlaceholder(duration, description));

				break;
			}
			case EffectState::TIMED_EFFECT: {
				QueueEffect(EffectHandler::HandleTimedEffect(std::string(function), duration, description));

				break;
			}
			case EffectState::GRAVITY: {
				float gravity = std::stof(function);

				QueueEffect(new Gravity(gravity, duration, description));

				break;
			}
			case EffectState::TELEPORT: {
				int x, y, z;
				sscanf(function.c_str(), "%d,%d,%d", &x, &y, &z);

				QueueFunction(Teleportation::Teleport, CVector((float) x, (float) y, (float) z));
				QueueEffect(new EffectPlaceholder(duration, description));

				break;
			}
			case EffectState::OTHER: {
				if (function == "explode_cars") {
					QueueFunction(Vehicle::BlowUpAllCars);
				}
				else if (function == "clear_weapons") {
					QueueFunction(Weapons::Clear);
				}
				QueueEffect(new EffectPlaceholder(duration, description));

				break;
			}
			case EffectState::TEXT: {
				QueueFunction(DrawHelper::DrawHelpMessage, description, 5000);

				break;
			}
			case EffectState::TIME: {
				remaining = std::stoi(function);

				break;
			}
			default: {
				break;
			}
		}

		if (currentState != EffectState::TEXT && currentState != EffectState::TIME) {
			QueueFunction(DrawHelper::DrawHelpMessage, description, 5000);
		}
		return;
	}

	void OnAttach() {
		HANDLE hPipe;
		char buffer[1024] = "";
		char text[1024] = "";
		DWORD dwRead;

		std::string myProcID = "\\\\.\\pipe\\GTASAChaosPipe";
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

	void SetupPipe() {
		std::thread t1([](GTASAChaosMod* chaos) { chaos->OnAttach(); }, this);
		t1.detach();
	}

	GTASAChaosMod() {
		SetupPipe();

		Events::gameProcessEvent.Add([this] { this->ProcessEvents(); });

		onDrawAfterFade.AddAfter([this] { this->DrawRemainingTime(); });
	}
} gtaSAChaosMod;
