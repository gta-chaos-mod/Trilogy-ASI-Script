// Copyright (c) 2019 Lordmau5
#include "LongLiveTheRich.h"

bool LongLiveTheRich::isEnabled = false;

LongLiveTheRich::LongLiveTheRich(int _duration, std::string _description)
	: TimedEffect(_duration, _description, "health") {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		storedMoney = player->GetPlayerInfoForThisPlayerPed()->m_nMoney;
	}
}

void LongLiveTheRich::InitializeHooks() {
	patch::RedirectCall(0x4B5B19, HookedAccountForPedArmour);
	patch::RedirectCall(0x4B5B27, HookedComputeWillKillPed);

	for (int address : {0x45902E, 0x459095}) {
		patch::RedirectCall(address, HookedPickupUpdate);
	}
}

void LongLiveTheRich::Enable() {
	isEnabled = true;

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney = (int)player->m_fHealth;
		player->GetPlayerInfoForThisPlayerPed()->m_nDisplayMoney = (int)player->m_fHealth;
	}
}

void LongLiveTheRich::Disable() {
	isEnabled = false;

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney = min(player->GetPlayerInfoForThisPlayerPed()->m_nMoney * 100, 100000);
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney += storedMoney;
		player->GetPlayerInfoForThisPlayerPed()->m_nDisplayMoney = player->GetPlayerInfoForThisPlayerPed()->m_nMoney;
	}

	TimedEffect::Disable();
}

void LongLiveTheRich::HandleTick() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_fHealth = player->m_fMaxHealth;
	}
}

void __fastcall LongLiveTheRich::HookedAccountForPedArmour(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, int cDamageResponseInfo) {
	if (isEnabled) {
		float maxDamage = min(ped->m_fArmour, thisCalc->m_fDamageFactor);
		maxDamage = thisCalc->m_pedPieceType == 9 ? ped->m_fHealth : maxDamage;

		CPlayerPed* player = FindPlayerPed();
		if (thisCalc->m_pDamager == player && ped != player) {
			if (ped->m_fArmour == 0.0f) {
				return;
			}

			player->GetPlayerInfoForThisPlayerPed()->m_nMoney += (int)(maxDamage / 10.0f);
		}
		else if (thisCalc->m_pDamager != player && ped == player) {
			player->GetPlayerInfoForThisPlayerPed()->m_nMoney -= (int)thisCalc->m_fDamageFactor;
			player->GetPlayerInfoForThisPlayerPed()->m_nMoney = max(0, player->GetPlayerInfoForThisPlayerPed()->m_nMoney);

			if (player->GetPlayerInfoForThisPlayerPed()->m_nMoney == 0) {
				player->m_fHealth = 0.0f;
			}

			return;
		}
	}

	thisCalc->AccountForPedArmour(ped, cDamageResponseInfo);
}

void __fastcall LongLiveTheRich::HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, float* a3, char a4) {
	if (isEnabled) {
		float maxDamage = min(ped->m_fHealth, thisCalc->m_fDamageFactor);
		maxDamage = thisCalc->m_pedPieceType == 9 ? ped->m_fHealth : maxDamage;

		CPlayerPed* player = FindPlayerPed();
		if (thisCalc->m_pDamager == player && ped != player) {
			player->GetPlayerInfoForThisPlayerPed()->m_nMoney += (int)(maxDamage / 10.0f);
		}
		else if (thisCalc->m_pDamager != player && ped == player) {
			player->GetPlayerInfoForThisPlayerPed()->m_nMoney -= (int)thisCalc->m_fDamageFactor;
			player->GetPlayerInfoForThisPlayerPed()->m_nMoney = max(0, player->GetPlayerInfoForThisPlayerPed()->m_nMoney);

			if (player->GetPlayerInfoForThisPlayerPed()->m_nMoney == 0) {
				player->m_fHealth = 0.0f;
			}

			return;
		}
	}

	thisCalc->ComputeWillKillPed(ped, a3, a4);
}

bool __fastcall LongLiveTheRich::HookedPickupUpdate(CPickup* thisPickup, void* edx, CPlayerPed* playerPed, CVehicle* vehicle, int playerId) {
	bool isMoneyPickup =
		thisPickup->m_nPickupType == ePickupType::PICKUP_MONEY ||
		thisPickup->m_nPickupType == ePickupType::PICKUP_MONEY_DOESNTDISAPPEAR ||
		thisPickup->m_nPickupType == ePickupType::PICKUP_ASSET_REVENUE;

	if (isEnabled && isMoneyPickup) {
		return false;
	}

	return plugin::CallMethodAndReturn<bool, 0x457410, CPickup*, CPlayerPed*, CVehicle*, int>(thisPickup, playerPed, vehicle, playerId);
}
