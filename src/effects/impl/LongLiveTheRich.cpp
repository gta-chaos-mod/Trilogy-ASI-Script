// Copyright (c) 2019 Lordmau5
#include "LongLiveTheRich.h"

bool LongLiveTheRich::isEnabled = false;
int LongLiveTheRich::storedMoney = 0;
float LongLiveTheRich::gainedMoney = 0.0f;

LongLiveTheRich::LongLiveTheRich(int _duration, const std::string& _description)
	: TimedEffect(_duration, _description, "health") {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		storedMoney = player->GetPlayerInfoForThisPlayerPed()->m_nMoney;
	}
}

void LongLiveTheRich::InitializeHooks() {
	patch::RedirectCall(0x4B5B27, HookedComputeWillKillPed);

	for (int address : { 0x45902E, 0x459095 }) {
		patch::RedirectCall(address, HookedPickupUpdate);
	}
}

void LongLiveTheRich::Enable() {
	*neverHungryCheat = true;

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		gainedMoney = player->m_fHealth;
		player->m_fHealth = player->m_fMaxHealth;
	}
}

void LongLiveTheRich::Disable() {
	isEnabled = false;

	*neverHungryCheat = false;

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney = min((int)gainedMoney * 100, 100000);
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney += storedMoney;
		player->GetPlayerInfoForThisPlayerPed()->m_nDisplayMoney = player->GetPlayerInfoForThisPlayerPed()->m_nMoney;
	}

	TimedEffect::Disable();
}

void LongLiveTheRich::HandleTick() {
	isEnabled = true;

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney = (int)gainedMoney;
		player->GetPlayerInfoForThisPlayerPed()->m_nDisplayMoney = (int)gainedMoney;
	}
}

void __fastcall LongLiveTheRich::HookedComputeWillKillPed(CPedDamageResponseCalculator* thisCalc, void* edx, CPed* ped, uint8_t* cDamageResponseInfo, char a4) {
	if (isEnabled) {
		float maxDamage = min(ped->m_fHealth, thisCalc->m_fDamageFactor);
		maxDamage = thisCalc->m_pedPieceType == 9 ? ped->m_fHealth : maxDamage;

		CPlayerPed* player = FindPlayerPed();
		if (thisCalc->m_pDamager == player && ped != player) {
			gainedMoney += maxDamage / 10.0f;
		}
		else if (ped == player) {
			gainedMoney -= thisCalc->m_fDamageFactor;
			gainedMoney = max(0.0f, gainedMoney);

			if (gainedMoney == 0.0f) {
				player->m_fHealth = 0.0f;
				thisCalc->ComputeWillKillPed(ped, cDamageResponseInfo, a4);
			}

			return;
		}
	}

	thisCalc->ComputeWillKillPed(ped, cDamageResponseInfo, a4);
}

bool __fastcall LongLiveTheRich::HookedPickupUpdate(CPickup* thisPickup, void* edx, CPlayerPed* playerPed, CVehicle* vehicle, int playerId) {
	bool isMoneyPickup =
		thisPickup->m_nPickupType == ePickupType::PICKUP_MONEY ||
		thisPickup->m_nPickupType == ePickupType::PICKUP_MONEY_DOESNTDISAPPEAR ||
		thisPickup->m_nPickupType == ePickupType::PICKUP_ASSET_REVENUE;

	if (isEnabled && isMoneyPickup && thisPickup->m_nAmmo > 0) {
		return false;
	}

	return plugin::CallMethodAndReturn<bool, 0x457410, CPickup*, CPlayerPed*, CVehicle*, int>(thisPickup, playerPed, vehicle, playerId);
}
