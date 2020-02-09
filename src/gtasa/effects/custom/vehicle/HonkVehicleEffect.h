#pragma once

#include "util/EffectBase.h"

class HonkVehicleEffect : public EffectBase
{
public:
    HonkVehicleEffect ();

    void InitializeHooks () override;

    void Disable () override;

    void HandleTick () override;

    static char __fastcall HookedPlayHornOrSiren (
        CAEVehicleAudioEntity *thisAudioEntity, void *edx, char counter,
        char sirenOrAlarm, char mrWhoopie, cVehicleParams *data);
};
