#pragma once

#include "util/EffectBase.h"

#include "CPlayerInfo.h"

class LongLiveTheRichEffect : public EffectBase
{
public:
    static bool  isEnabled;
    static int   storedMoney;
    static float gainedMoney;

public:
    LongLiveTheRichEffect ();

    void InitializeHooks () override;

    void Enable () override;
    void Disable () override;

    void HandleTick () override;

private:
    static void HookedCFontPrintString (float x, float y, char *text);
    static bool __fastcall HookedCPedInflictDamage (
        CPed *thisPed, void *edx, CEntity *source, eWeaponType weapon,
        float damage, ePedPieceTypes pedPiece, uchar unknown);
};
