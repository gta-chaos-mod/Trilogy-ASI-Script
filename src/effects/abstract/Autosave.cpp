// Copyright (c) 2019 Lordmau5
#include "Autosave.h"

Autosave::Autosave()
	: TimedEffect(1000 * 10, "Autosave (Get On Foot)") {
	immuneToCryptic = true;
	effectColor = CRGBA(255, 50, 50, 230);
}

void Autosave::HandleTick() {
	if (!didSave && !FindPlayerVehicle(-1, false) && FindPlayerPed()) {
		GenericUtil::SaveToFile("chaos_autosave.b");

		didSave = true;

		effectColor = CRGBA(40, 200, 40, 230);

		Disable();

		description = "Autosave Completed";
	}
}
