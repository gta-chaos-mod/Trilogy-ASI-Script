#include "effects/OneTimeEffect.h"

#include <CPlayerInfo.h>

using namespace plugin;

class InstantlyHungryEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CPlayerInfo *playerInfo = player->GetPlayerInfoForThisPlayerPed ();
        if (!playerInfo) return;

        playerInfo->m_nNumHoursDidntEat = 60;
        CallMethod<0x56E610, CPlayerInfo *> (playerInfo);

        inst->WriteMemory (0xB9B8F0, true, false); // bHungryMessageShown
    }
};

DEFINE_EFFECT (InstantlyHungryEffect, "effect_instantly_hungry", 0);