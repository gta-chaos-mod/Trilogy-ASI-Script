#pragma once

#include "plugin.h"

#include <map>

using namespace plugin;

class HookDatabase
{
private:
	struct HookElement {
		std::string id = "";
		int address = 0;
		injector::memory_pointer_raw pointer = nullptr;
		bool isCall = false;

		HookElement() {};
		HookElement(std::string id, int address, injector::memory_pointer_raw pointer, bool isCall) {
			this->id = std::move(id);
			this->address = address;
			this->pointer = pointer;
			this->isCall = isCall;
		}
	};

	// TODO: Turn into map<int, vecto<HookElement>>
	// Scenario:
	// - Normal cooldown Pitch Shifter
	// - Rapid Fire turns 2x Game Speed on
	// - It unhooks Pitch Shifter
	// - 2x Game Speed runs out in 15 seconds
	// - Once it runs out, it unhooks
	// - Pitch Shifter still "running" but no audio effects
	static std::unordered_map<int, HookElement>& registeredHooks() {
		static std::unordered_map<int, HookElement> hooks;
		return hooks;
	};

public:
	static void HookCall(std::string id, int address, void* func, bool vp = true);

	static void HookJump(std::string id, int address, void* func, bool vp = true);

	static void RestoreHook(HookElement hook);

	static void RestoreHooks(std::string id);
};
