// Copyright (c) 2019 Lordmau5
#include "Ped.h"

void Ped::SetAllOnFire() {
	for (CPed* ped : CPools::ms_pPedPool) {
		gFireManager.StartFire(ped, NULL, 1.0f, 1, 7000, 100);
	}
}

void Ped::ClearWeapons() {
	for (CPed* ped : CPools::ms_pPedPool) {
		ped->ClearWeapons();
	}
}

void Ped::MakeBeachParty() {
	CCheat::BeachPartyCheat();

	RebuildPlayer();
}

void Ped::MakeNinja() {
	CCheat::NinjaCheat();

	RebuildPlayer();
}

void Ped::MakeKinky() {
	CCheat::LoveConquersAllCheat();

	RebuildPlayer();
}

void Ped::MakeFunhouse() {
	CCheat::FunhouseCheat();

	RebuildPlayer();
}

void Ped::MakeCountry() {
	CCheat::CountrysideInvasionCheat();

	RebuildPlayer();
}

void Ped::RebuildPlayer() {
	CPlayerPed* player = FindPlayerPed();
	if (player) {
		ePedState oldState = player->m_nPedState;
		player->m_nPedState = ePedState::PEDSTATE_IDLE;
		CClothes::RebuildPlayer(player, false);
		player->m_nPedState = oldState;
	}
}
