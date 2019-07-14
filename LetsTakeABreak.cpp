#include "LetsTakeABreak.h"

LetsTakeABreak::LetsTakeABreak(int _duration, std::string _description) : TimedEffect(_duration, _description) {}

void LetsTakeABreak::Enable() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_nPedType = 1;
	}
}

void LetsTakeABreak::Disable() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_nPedType = 0;
	}
}