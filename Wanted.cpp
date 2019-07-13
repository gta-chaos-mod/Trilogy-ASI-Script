#include "Wanted.h"

void Wanted::IncreaseWantedLevel() {
	CWanted* wanted = FindPlayerWanted(-1);
	if (wanted) {
		int targetWanted = min(wanted->m_nWantedLevel + 2, 6);
		wanted->CheatWantedLevel(targetWanted);
	}
}

void Wanted::ClearWantedLevel() {
	CWanted* wanted = FindPlayerWanted(-1);
	if (wanted) {
		wanted->CheatWantedLevel(0);
	}
}

void Wanted::SixWantedStars() {
	CWanted* wanted = FindPlayerWanted(-1);
	if (wanted) {
		wanted->CheatWantedLevel(6);
	}
}