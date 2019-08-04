#include "Autosave.h"

Autosave::Autosave() : TimedEffect(1000 * 10, "Autosave (Get On Foot)") {}

void Autosave::HandleTick() {
	if (!didSave && !FindPlayerVehicle(-1, false) && FindPlayerPed()) {
		//std::sprintf(CGenericGameStorage::ms_ValidSaveName, "%s\\chaos_autosave.b", gamePath);
		std::sprintf(CGenericGameStorage::ms_ValidSaveName, "%s\\GTASAsf8.b", gamePath); // Slot 8 until custom loading works

		CGenericGameStorage::GenericSave(0);

		didSave = true;
		
		Disable();

		description = "Autosave Completed";
	}
}
