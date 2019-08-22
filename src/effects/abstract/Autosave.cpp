// Copyright (c) 2019 Lordmau5
#include "Autosave.h"

Autosave::Autosave()
	: TimedEffect(1000 * 10, "Autosave (Get On Foot)") {
	immuneToCryptic = true;
	effectColor = CRGBA(255, 50, 50, 230);
}

void Autosave::HandleTick() {
	if (!didSave && !FindPlayerVehicle(-1, false) && FindPlayerPed()) {
		std::sprintf(CGenericGameStorage::ms_ValidSaveName, "%s\\chaos_autosave.b", gamePath);

		// Temporarily disable cheats and certain effects so they don't get saved
		for (int i = 0; i < 92; i++) {
			CCheat::m_aCheatsActive[i] = false;
		}
		CClock::ms_nMillisecondsPerGameMinute = 1000;

		CPedAcquaintance temp_acquaintances[32];
		GenericUtil::SaveAcquaintances(temp_acquaintances);
		GenericUtil::RestoreSavedAcquaintances();

		CGenericGameStorage::GenericSave(0);

		GenericUtil::LoadAcquaintances(temp_acquaintances);

		didSave = true;

		effectColor = CRGBA(40, 200, 40, 230);

		Disable();

		description = "Autosave Completed";
	}
}
