#include "LongLiveTheRichEffect.h"

bool LongLiveTheRichEffect::isEnabled = false;
int LongLiveTheRichEffect::storedMoney = 0;
float LongLiveTheRichEffect::gainedMoney = 0.0f;

LongLiveTheRichEffect::LongLiveTheRichEffect()
	: EffectBase("effect_long_live_the_rich")
{
	AddType("health");

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		storedMoney = player->GetPlayerInfoForThisPlayerPed()->m_nMoney;
	}
}

void LongLiveTheRichEffect::InitializeHooks() {
	EffectBase::InitializeHooks();

	// Health
	HookCall(0x558C10, HookedCFontPrintString);
	HookCall(0x558CF4, HookedCFontPrintString);

	// Armor
	HookCall(0x558E80, HookedCFontPrintString);
	HookCall(0x558F64, HookedCFontPrintString);

	for (int address : {
		0x48E787, 0x48E7AD, 0x4AC800, 0x4D4EDE, 0x4D81EE, 0x4FD248, 0x5053E7, 0x505465, 0x5064F9,
			0x509776, 0x50997A, 0x5245D5, 0x524741, 0x527BAB, 0x599F48, 0x599F98, 0x5A0E0B, 0x5B49AA,
			0x5C4089, 0x5C9DBE, 0x5CBC95, 0x5CE361, 0x5CF34B, 0x5CF54A, 0x5CF54A, 0x5D3352, 0x6137BD,
			0x613887, 0x614C49, 0x614CC0
	}) {
		HookCall(address, HookedCPedInflictDamage);
	}
}

void LongLiveTheRichEffect::Enable() {
	EffectBase::Enable();

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		gainedMoney = player->m_fHealth;
		player->m_fHealth = 100.0f;
	}
}

void LongLiveTheRichEffect::Disable() {
	isEnabled = false;

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->m_fHealth = min(gainedMoney, 100.0f);

		player->GetPlayerInfoForThisPlayerPed()->m_nMoney = min((int)gainedMoney * 100, 100000);
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney += storedMoney;
		player->GetPlayerInfoForThisPlayerPed()->m_nDisplayMoney = player->GetPlayerInfoForThisPlayerPed()->m_nMoney;
	}

	EffectBase::Disable();
}

void LongLiveTheRichEffect::HandleTick() {
	EffectBase::HandleTick();

	isEnabled = true;

	CPlayerPed* player = FindPlayerPed();
	if (player) {
		player->GetPlayerInfoForThisPlayerPed()->m_nMoney = (int)gainedMoney;
		player->GetPlayerInfoForThisPlayerPed()->m_nDisplayMoney = (int)gainedMoney;
	}
}

void LongLiveTheRichEffect::HookedCFontPrintString(float x, float y, char* text) {}

bool __fastcall LongLiveTheRichEffect::HookedCPedInflictDamage(CPed* thisPed, void* edx, CEntity* source, eWeaponType weapon, float damage, ePedPieceTypes pedPiece, uchar unknown) {
	float maxDamage = min(thisPed->m_fHealth, damage);

	CPlayerPed* player = FindPlayerPed();
	CEntity* playerEntity = FindPlayerEntity();
	if (source == playerEntity && thisPed != playerEntity) {
		gainedMoney += maxDamage / 10.0f;
	}
	else if (thisPed == player) {
		gainedMoney -= damage;
		gainedMoney = max(0.0f, gainedMoney);

		if (gainedMoney == 0.0f) {
			player->m_fHealth = 0.0f;
			return CallMethodAndReturn<bool, 0x525B20, CPed*>(thisPed, source, weapon, damage, pedPiece, unknown);
		}

		return false;
	}

	return CallMethodAndReturn<bool, 0x525B20, CPed*>(thisPed, source, weapon, damage, pedPiece, unknown);
}
