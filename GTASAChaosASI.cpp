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

// Version 0.99

using namespace plugin;

enum EffectState {
	NOTHING = 0,

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
	enum EffectState state = EffectState::NOTHING;
	std::queue<std::function<void()>> queue;
	int keyPressTime = 0;
	std::string helpText = "";
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

	void CallFunction(std::string func) {
		char cheat[64];
		int duration;
		char description[128];
		if (state != EffectState::NOTHING && state != EffectState::TEXT && state != EffectState::TIME) {
			sscanf(func.c_str(), "%[^:]:%d:%[^:]", &cheat, &duration, description);
		}

		switch (state) {
			case EffectState::NOTHING: {
				if (func == "weapons") {
					state = EffectState::WEAPONS;
				}
				else if (func == "wanted") {
					state = EffectState::WANTED;
				}
				else if (func == "weather") {
					state = EffectState::WEATHER;
				}
				else if (func == "spawn_vehicle") {
					state = EffectState::SPAWN_VEHICLE;
				}
				else if (func == "game_speed") {
					state = EffectState::GAME_SPEED;
				}
				else if (func == "cheat") {
					state = EffectState::CHEAT;
				}
				else if (func == "timed_cheat") {
					state = EffectState::TIMED_CHEAT;
				}
				else if (func == "effect") {
					state = EffectState::EFFECT;
				}
				else if (func == "timed_effect") {
					state = EffectState::TIMED_EFFECT;
				}
				else if (func == "gravity") {
					state = EffectState::GRAVITY;
				}
				else if (func == "other") {
					state = EffectState::OTHER;
				}
				else if (func == "teleport") {
					state = EffectState::TELEPORT;
				}
				else if (func == "text") {
					state = EffectState::TEXT;
				}
				else if (func == "time") {
					state = EffectState::TIME;
				}
				break;
			}
			case EffectState::WEAPONS: {
				int id = std::stoi(cheat);
				QueueFunction(Weapons::GiveByID, id);
				QueueEffect(new EffectPlaceholder(duration, description));

				state = EffectState::NOTHING;
				break;
			}
			case EffectState::WANTED: {
				if (cheat == "plus_two") {
					QueueFunction(Wanted::IncreaseWantedLevel);
				}
				else if (cheat == "clear") {
					QueueFunction(Wanted::ClearWantedLevel);
				}
				else if (cheat == "six_stars") {
					QueueFunction(Wanted::SixWantedStars);
				}
				QueueEffect(new EffectPlaceholder(duration, description));

				state = EffectState::NOTHING;
				break;
			}
			case EffectState::WEATHER: {
				QueueFunction(CWeather::ForceWeatherNow, std::stoi(cheat));
				QueueEffect(new EffectPlaceholder(duration, description));

				state = EffectState::NOTHING;
				break;
			}
			case EffectState::SPAWN_VEHICLE: {
				int modelID = std::stoi(cheat);
				QueueFunction(Vehicle::SpawnForPlayer, modelID);
				QueueEffect(new EffectPlaceholder(duration, description));

				state = EffectState::NOTHING;
				break;
			}
			case EffectState::GAME_SPEED: {
				float speed;
				sscanf(cheat, "%f", &speed);

				QueueFunction([speed] { CTimer::ms_fTimeScale = speed; });
				QueueEffect(new EffectPlaceholder(duration, description));

				state = EffectState::NOTHING;
				break;
			}
			case EffectState::CHEAT: {
				QueueFunction([cheat] { CheatHandler::HandleCheat(cheat); });
				QueueEffect(new EffectPlaceholder(duration, description));

				state = EffectState::NOTHING;
				break;
			}
			case EffectState::TIMED_CHEAT: {
				QueueEffect(CheatHandler::HandleTimedCheat(std::string(cheat), duration, description));

				state = EffectState::NOTHING;
				break;
			}
			case EffectState::EFFECT: {
				QueueFunction([cheat] { EffectHandler::HandleEffect(cheat); });
				QueueEffect(new EffectPlaceholder(duration, description));

				state = EffectState::NOTHING;
				break;
			}
			case EffectState::TIMED_EFFECT: {
				QueueEffect(EffectHandler::HandleTimedEffect(std::string(cheat), duration, description));

				state = EffectState::NOTHING;
				break;
			}
			case EffectState::GRAVITY: {
				float gravity = std::stof(cheat);

				QueueEffect(new Gravity(gravity, duration, description));

				state = EffectState::NOTHING;
				break;
			}
			case EffectState::TELEPORT: {
				int x, y, z;
				sscanf(cheat, "%d,%d,%d", &x, &y, &z);

				QueueFunction(Teleportation::Teleport, CVector((float) x, (float) y, (float) z));
				QueueEffect(new EffectPlaceholder(duration, description));

				state = EffectState::NOTHING;
				break;
			}
			case EffectState::OTHER: {
				if (cheat == "explode_cars") {
					QueueFunction(Vehicle::BlowUpAllCars);
				}
				else if (cheat == "clear_weapons") {
					QueueFunction(Weapons::Clear);
				}
				QueueEffect(new EffectPlaceholder(duration, description));

				state = EffectState::NOTHING;
				break;
			}
			case EffectState::TEXT: {
				helpText = func.c_str();
				QueueFunction(DrawHelper::DrawHelpMessage, (char*)helpText.c_str(), 5000);

				state = EffectState::NOTHING;
				break;
			}
			case EffectState::TIME: {
				remaining = std::stoi(func);

				state = EffectState::NOTHING;
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

		Events::gameProcessEvent.Add([this] { this->ProcessEvents(); });

		onDrawAfterFade.AddAfter([this] { this->DrawRemainingTime(); });
	}
} gtaSAChaosMod;
