#pragma once

#include "common.h"
#include "plugin.h"

class CPedDamageResponseCalculator
{
public:
	DWORD m_pDamager;
	float m_fDamageFactor;
	unsigned int m_pedPieceType;
	eWeaponType m_weaponType;
	byte m_bUnk;
	char _padding[3];

	unsigned int AccountForPedArmour(CPed* a2, int cDamageResponseInfo);
	void ComputeWillKillPed(CPed* a2, float* a3, char a4);
};
