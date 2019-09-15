// Copyright (c) 2019 Lordmau5
#include "Autosave.h"

Autosave::Autosave(int _missionsPassed)
	: TimedEffect(1000 * 10, "Autosaving...") {
	missionsPassed = _missionsPassed;
	immuneToCryptic = true;
	effectColor = CRGBA(255, 50, 50, 200);
}

void Autosave::HandleTick() {
	CPlayerPed* player = FindPlayerPed();
	if (!didSave && player) {
		bool wasInVehicle = player->m_nPedFlags.bInVehicle;
		player->m_nPedFlags.bInVehicle = false;

		if (Config::GetOrDefault("Chaos.SaveToSlot8", false)) {
			GenericUtil::SaveToFile("GTASAsf8.b");
		}

		GenericUtil::SaveToFile("chaos_mod\\chaos_autosave.b");

		std::string missionSave;
		missionSave
			.append("chaos_mod\\chaos_autosave.mission_")
			.append(std::to_string(missionsPassed))
			.append(".b");
		GenericUtil::SaveToFile(missionSave);

		player->m_nPedFlags.bInVehicle = wasInVehicle;

		didSave = true;

		effectColor = CRGBA(40, 200, 40, 200);

		Disable();

		description = "Autosave Completed";

		textColorTick = 2400;
	}
}
