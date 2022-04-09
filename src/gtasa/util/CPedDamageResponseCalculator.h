#pragma once

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
    CEntity       *m_pDamager;
    float          m_fDamageFactor;
    ePedPieceTypes m_pedPieceType;
    eWeaponType    m_weaponType;
    byte           m_bUnk;
    char           _padding[3];

    void AccountForPedArmour (CPed *ped, uint8_t *cDamageResponseInfo);
    void ComputeWillKillPed (CPed *ped, uint8_t *cDamageResponseInfo, char a4);
};
