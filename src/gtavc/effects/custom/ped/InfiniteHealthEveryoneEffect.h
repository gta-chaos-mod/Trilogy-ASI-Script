#pragma once

#include "util/EffectBase.h"

class InfiniteHealthEveryoneEffect : public EffectBase
{
public:
    InfiniteHealthEveryoneEffect ();

    void InitializeHooks () override;

    void HandleTick () override;

private:
    static bool __fastcall HookedCPedInflictDamage (
        CPed *thisPed, void *edx, CEntity *source, eWeaponType weapon,
        float damage, ePedPieceTypes pedPiece, uchar unknown);
};
