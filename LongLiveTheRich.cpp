#include "LongLiveTheRich.h"

bool LongLiveTheRich::isEnabled = false;

LongLiveTheRich::LongLiveTheRich(int _duration, std::string _description) : TimedEffect(_duration, _description) {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		storedMoney = player->GetPlayerInfoForThisPlayerPed()->m_nMoney;
	}
}

void LongLiveTheRich::Enable() {
	isEnabled = true;

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_fArmour = 0.0f;
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney = (int) player->m_fHealth;
	}
}

void LongLiveTheRich::Disable() {
	isEnabled = false;

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney += storedMoney;
	}
}

void LongLiveTheRich::HandleArmour(CPedDamageResponseCalculator* damageResponseCalc, CPed* ped, int cDamageResponseInfo) {
	CPlayerPed* player = FindPlayerPed();
	if (damageResponseCalc->m_pDamager == player && ped != player) {
		if (ped->m_fArmour == 0.0f) {
			return;
		}

		bool isHeadshot = damageResponseCalc->m_pedPieceType == 9;

		player->GetPlayerInfoForThisPlayerPed()->m_nMoney += isHeadshot ? 4 : 1;

		ped->m_fArmour -= damageResponseCalc->m_fDamageFactor;
		ped->m_fArmour = max(0.0f, ped->m_fArmour);

		if (isHeadshot) {
			ped->m_nMoneyCount = 0;
			ped->m_fHealth = 0.0f;
		}
		return;
	}
	else if (damageResponseCalc->m_pDamager != player && ped == player) {
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney -= damageResponseCalc->m_fDamageFactor;
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney = max(0, player->GetPlayerInfoForThisPlayerPed()->m_nMoney);

		if (player->GetPlayerInfoForThisPlayerPed()->m_nMoney == 0) {
			player->m_fHealth = 0.0f;
		}

		return;
	}
}

void LongLiveTheRich::HandleHealth(CPedDamageResponseCalculator* damageResponseCalc, CPed* ped, float* a3, char a4) {
	CPlayerPed* player = FindPlayerPed();
	if (damageResponseCalc->m_pDamager == player && ped != player) {
		bool isHeadshot = damageResponseCalc->m_pedPieceType == 9;

		player->GetPlayerInfoForThisPlayerPed()->m_nMoney += isHeadshot ? 4 : 1;

		ped->m_fHealth -= damageResponseCalc->m_fDamageFactor;
		ped->m_fHealth = max(0.0f, ped->m_fHealth);

		if (isHeadshot) {
			ped->m_nMoneyCount = 0;
			ped->m_fHealth = 0.0f;
		}
		
		return;
	}
	else if (damageResponseCalc->m_pDamager != player && ped == player) {
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney -= damageResponseCalc->m_fDamageFactor;
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney = max(0, player->GetPlayerInfoForThisPlayerPed()->m_nMoney);

		if (player->GetPlayerInfoForThisPlayerPed()->m_nMoney == 0) {
			player->m_fHealth = 0.0f;
		}

		return;
	}
}