#include "Autosave.h"

Autosave::Autosave()
	: TimedEffect(1000 * 10, "Autosave (Get On Foot)") {
	immuneToCryptic = true;
	effectColor = CRGBA(255, 50, 50, 230);
}

void Autosave::HandleTick() {
	if (!didSave && !FindPlayerVehicle(-1, false) && FindPlayerPed()) {
		std::sprintf(CGenericGameStorage::ms_ValidSaveName, "%s\\chaos_autosave.b", gamePath);

		CGenericGameStorage::GenericSave(0);

		didSave = true;

		effectColor = CRGBA(40, 200, 40, 230);

		Disable();

		description = "Autosave Completed";
	}
}
