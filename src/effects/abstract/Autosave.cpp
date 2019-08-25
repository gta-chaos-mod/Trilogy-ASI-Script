// Copyright (c) 2019 Lordmau5
#include "Autosave.h"

Autosave::Autosave(int _missionsPassed)
	: TimedEffect(1000 * 10, "Autosave (Get On Foot)") {
	missionsPassed = _missionsPassed;
	immuneToCryptic = true;
	effectColor = CRGBA(255, 50, 50, 230);
}

void Autosave::HandleTick() {
	if (!didSave && !FindPlayerVehicle(-1, false) && FindPlayerPed()) {
		GenericUtil::SaveToFile("chaos_mod\\chaos_autosave.b");

		std::string missionSave;
		missionSave
			.append("chaos_mod\\chaos_autosave.mission_")
			.append(std::to_string(missionsPassed))
			.append(".b");
		GenericUtil::SaveToFile(missionSave);

		didSave = true;

		effectColor = CRGBA(40, 200, 40, 230);

		Disable();

		description = "Autosave Completed";
	}
}
