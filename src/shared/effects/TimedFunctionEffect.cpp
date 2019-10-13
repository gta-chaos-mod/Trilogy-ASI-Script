#include "TimedFunctionEffect.h"

TimedFunctionEffect::TimedFunctionEffect(std::string id, void* function, int address)
	: EffectBase(id)
{
	this->function = function;
	if (address) {
		this->address = reinterpret_cast<bool*>(address);
	}
}

void TimedFunctionEffect::Disable() {
	if (function && address && *address) {
		reinterpret_cast<void(*)()> (function) ();
	}

	EffectBase::Disable();
}

void TimedFunctionEffect::HandleTick() {
	EffectBase::HandleTick();

	if (function && address && !*address) {
		reinterpret_cast<void(*)()> (function) ();
	}
}
