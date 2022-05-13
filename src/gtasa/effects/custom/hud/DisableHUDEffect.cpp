#include "util/EffectBase.h"
#include "util/Globals.h"
#include "util/hooks/HookMacros.h"

#include <CMenuSystem.h>
#include <CRadar.h>

using namespace plugin;

class DisableHUDEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        Globals::isDisableHUDEffectEnabled = true;

        HOOK (inst, Hooked_CHud_Draw, void (), 0x53E4FF);

        HOOK (inst, Hooked_CMenuSystem_DisplayGridMenu,
              tMenuPanel * (unsigned __int8, unsigned __int8), 0x58261E,
              0x582679, 0x5826CF, 0x58274D);

        // CRadar::DrawBlips
        HOOK (inst, Hooked_Empty, void (), 0x58AA2D);

        // CMenuSystem::DisplayStandardMenu
        HOOK (inst, Hooked_Empty, void (unsigned __int8, bool), 0x582627,
              0x582687, 0x5826D9, 0x582757);

        // CHud::DrawAreaName
        HOOK (inst, Hooked_Empty, void (), 0x58D542);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Globals::isDisableHUDEffectEnabled = false;
    }

    static void
    Hooked_CHud_Draw (auto &&cb)
    {
        CRadar::Draw3dMarkers ();

        if (CMenuSystem::num_menus_in_use) CMenuSystem::Process (-99);
    }

    static tMenuPanel *
    Hooked_CMenuSystem_DisplayGridMenu (auto &&cb)
    {
        return nullptr;
    }

    static void
    Hooked_Empty (auto &&cb)
    {
    }
};

DEFINE_EFFECT (DisableHUDEffect, "effect_disable_hud", GROUP_HUD);