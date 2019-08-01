#include "plugin.h"
#include "common.h"

#include "CHud.h"
#include "CRadar.h"
#include "CWeather.h"
#include "CCheat.h"

#include "DrawHelper.h"
#include "Gravity.h"
#include "Ped.h"
#include "Player.h"
#include "Teleportation.h"
#include "Vehicle.h"
#include "Wanted.h"

#include "CheatHandler.h"
#include "EffectHandler.h"

#include "DisableHUD.h"
#include "DisableRadarBlips.h"
#include "GameSpeed.h"

#include "EffectPlaceholder.h"
#include "FunctionEffect.h"
#include "HookHandler.h"
#include "RandomHelper.h"

#include <queue>
#include <thread>

// Version 0.998

using namespace plugin;

enum EffectState {
	WANTED,
	WEATHER,
	SPAWN_VEHICLE,
	GAME_SPEED,
	CHEAT,
	TIMED_CHEAT,
	EFFECT,
	TIMED_EFFECT,
	GRAVITY,
	TELEPORT,
	OTHER,

	TEXT,
	TIME,
	BIG_TEXT,
	SET_SEED,
};

static CdeclEvent<AddressList<0x53E83C, H_CALL, 0x53EBA2, H_CALL>, PRIORITY_AFTER, ArgPickNone, void()> onDrawAfterFade;

class GTASAChaosMod {
public:
	std::queue<std::function<void()>> queue;
	int remaining = 0;

	std::list<TimedEffect*> activeEffects;

	void ProcessEvents() {
		EmptyQueue();

		for (TimedEffect* effect : activeEffects) {
			effect->TickDown();
		}
		activeEffects.remove_if([](TimedEffect* effect) { return !effect->IsRunning(); });

		CCheat::m_bHasPlayerCheated = false;
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

		// If it's a placeholder, just add it (mostly one-time effects)
		if (effect->isPlaceholder) {
			activeEffects.push_front(effect);
			return;
		}

		// If an effect with the same type or description is found, disable it, remove it and add a fresh copy of it
		auto it = std::find_if(activeEffects.begin(), activeEffects.end(), [effect](TimedEffect* _effect) { return effect->IsEqualType(_effect) || effect->IsEqualDescription(_effect); });
		if (it != activeEffects.end()) {
			TimedEffect* _effect = *it;
			if (_effect) {
				_effect->Disable();
			}
			activeEffects.remove(*it);
		}
		activeEffects.push_front(effect);
	}

	void DrawRemainingTime() {
		DrawHelper::DrawRemainingTimeRects(remaining);
		DrawHelper::DrawRecentEffects(activeEffects);
		DrawHelper::DrawMessages();
		DrawHelper::DrawBigMessages();
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
		if (state == "wanted") {
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
		else if (state == "big_text") {
			currentState = EffectState::BIG_TEXT;
		}
		else if (state == "set_seed") {
			currentState = EffectState::SET_SEED;
		}
		else {
			return;
		}

		switch (currentState) {
			case EffectState::WANTED: {
				if (function == "plus_two") {
					QueueEffect(new FunctionEffect(Wanted::IncreaseWantedLevel, duration, description, "wanted"));
				}
				else if (function == "clear") {
					QueueEffect(new FunctionEffect(Wanted::ClearWantedLevel, duration, description, "wanted"));
				}
				else if (function == "six_stars") {
					QueueEffect(new FunctionEffect(Wanted::SixWantedStars, duration, description, "wanted"));
				}

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

				QueueEffect(new GameSpeed(speed, duration, description));

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
					QueueFunction(Ped::ClearWeapons);
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
			case EffectState::BIG_TEXT: {
				QueueFunction(DrawHelper::DrawBigMessage, function, 10000);

				break;
			}
			case EffectState::SET_SEED: {
				RandomHelper::SetSeed(std::stoi(function));

				break;
			}
			default: {
				break;
			}
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

		HookHandler::Initialize();

		Events::gameProcessEvent.Add([this] { this->ProcessEvents(); });

		onDrawAfterFade.AddAfter([this] { this->DrawRemainingTime(); });
	}
} gtaSAChaosMod;
