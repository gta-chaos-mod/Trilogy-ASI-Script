#pragma once

#include "util/EffectBase.h"
#include "util/CPedDamageResponseCalculator.h"

#include "CPickup.h"
#include "CPlayerInfo.h"

class LongLiveTheRichEffect : public EffectBase
{
public:
    static bool  isEnabled;
    static int   storedMoney;
    static float gainedMoney;

    bool *neverHungryCheat = reinterpret_cast<bool *> (0x969174);

public:
    LongLiveTheRichEffect ();

    void InitializeHooks () override;

    void Enable () override;
    void Disable () override;

    void HandleTick () override;

private:
    static void __fastcall HookedComputeWillKillPed (
        CPedDamageResponseCalculator *thisCalc, void *edx, CPed *ped,
        uint8_t *cDamageResponseInfo, char a4);
    static bool __fastcall HookedPickupUpdate (CPickup *thisPickup, void *edx,
                                               CPlayerPed *ped,
                                               CVehicle *vehicle, int playerId);
    static void HookedCHudRenderHealthBar (int playerId, signed int x,
                                           signed int y);
};
