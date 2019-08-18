// Copyright (c) 2019 Lordmau5
#pragma once

#include "common.h"
#include "plugin.h"

// ePedPieceTypes
/*
3 - Torso
4 - Ass?
5 - Left Arm
6 - Right Arm
7 - Left Leg
8 - Right Leg
9 - Head
*/

class CPedDamageResponseCalculator
{
public:
	CEntity* m_pDamager;
	float m_fDamageFactor;
	ePedPieceTypes m_pedPieceType;
	eWeaponType m_weaponType;
	byte m_bUnk;
	char _padding[3];

	unsigned int AccountForPedArmour(CPed* a2, int cDamageResponseInfo);
	void ComputeWillKillPed(CPed* a2, float* a3, char a4);
};
