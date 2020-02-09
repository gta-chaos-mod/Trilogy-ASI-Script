#include "DisableHUDEffect.h"

DisableHUDEffect::DisableHUDEffect () : EffectBase ("effect_disable_hud")
{
    AddType ("hud");
}

void
DisableHUDEffect::InitializeHooks ()
{
    EffectBase::InitializeHooks ();

    HookCall (0x53E4FF, HookedHUDDraw);
    HookJump (0x58AA2D, HookedBlipsDraw);

    HookJump (0x58261E, HookedCMenuSystemDisplayGridMenu);
    for (int address : {0x582679, 0x5826CF, 0x58274D})
    {
        HookCall (address, HookedCMenuSystemDisplayGridMenu);
    }

    HookJump (0x582627, HookedCMenuSystemDisplayStandardMenu);
    for (int address : {0x582687, 0x5826D9, 0x582757})
    {
        HookCall (address, HookedCMenuSystemDisplayStandardMenu);
    }

    HookCall (0x58D542, HookedCHudDrawAreaName);
}

void
DisableHUDEffect::HookedHUDDraw ()
{
    CRadar::Draw3dMarkers ();

    if (CMenuSystem::num_menus_in_use)
    {
        CMenuSystem::Process (-99);
    }
}

void
DisableHUDEffect::HookedBlipsDraw ()
{
}

tMenuPanel *
DisableHUDEffect::HookedCMenuSystemDisplayGridMenu (unsigned __int8 a1,
                                                    unsigned __int8 a2)
{
    return nullptr;
}

void
DisableHUDEffect::HookedCMenuSystemDisplayStandardMenu (unsigned __int8 panelId,
                                                        bool bBrightFont)
{
}

void
DisableHUDEffect::HookedCHudDrawAreaName ()
{
}
