#include "EffectPlaceholder.h"

EffectPlaceholder::EffectPlaceholder(std::string id)
	: EffectBase(id)
{
	SetPlaceholder();
}

void EffectPlaceholder::Enable() {
	EffectBase::Enable();

	EffectBase::Disable();
}
