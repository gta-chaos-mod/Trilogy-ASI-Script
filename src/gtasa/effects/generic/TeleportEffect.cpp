#include "TeleportEffect.h"

TeleportEffect::TeleportEffect(CVector destination)
	: EffectPlaceholder("effect_teleport")
{
	this->destination = destination;
}

void TeleportEffect::Enable() {
	EffectPlaceholder::Enable();

	Teleportation::Teleport(this->destination);
}
