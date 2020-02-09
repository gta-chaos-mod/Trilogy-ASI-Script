#include "HaveABountyOnYourHeadCheat.h"

HaveABountyOnYourHeadCheat::HaveABountyOnYourHeadCheat ()
    : EffectBase ("cheat_have_a_bounty_on_your_head")
{
    AddType ("peds_attack");
    AddType ("ped_spawns");
    SetDisabledForMissions ();
}

void
HaveABountyOnYourHeadCheat::Enable ()
{
    EffectBase::Enable ();

    GameUtil::BackupAcquaintances ();

    if (!*haveABountyOnYourHeadCheat)
    {
        CCheat::EverybodyAttacksPlayerCheat ();
    }
}

void
HaveABountyOnYourHeadCheat::Disable ()
{
    if (*haveABountyOnYourHeadCheat)
    {
        CCheat::EverybodyAttacksPlayerCheat ();
    }

    GameUtil::RestoreSavedAcquaintances ();

    EffectBase::Disable ();
}
