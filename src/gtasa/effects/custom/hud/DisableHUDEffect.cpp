#include "util/EffectBase.h"

#include <CMenuSystem.h>
#include <CRadar.h>

using namespace plugin;

class DisableHUDEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        injector::MakeCALL (0x53E4FF, Hooked_HUD_Draw);
        injector::MakeJMP (0x58AA2D, Hooked_Blips_Draw);

        injector::MakeJMP (0x58261E, Hooked_CMenuSystem_DisplayGridMenu);
        for (int address : {0x582679, 0x5826CF, 0x58274D})
        {
            injector::MakeCALL (address, Hooked_CMenuSystem_DisplayGridMenu);
        }

        injector::MakeJMP (0x582627, Hooked_CMenuSystem_DisplayStandardMenu);
        for (int address : {0x582687, 0x5826D9, 0x582757})
        {
            injector::MakeCALL (address,
                                Hooked_CMenuSystem_DisplayStandardMenu);
        }

        injector::MakeCALL (0x58D542, Hooked_CHud_DrawAreaName);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        // TODO: Unhook
    }

    static void
    Hooked_HUD_Draw ()
    {
        CRadar::Draw3dMarkers ();

        if (CMenuSystem::num_menus_in_use) CMenuSystem::Process (-99);
    }

    static void
    Hooked_Blips_Draw ()
    {
    }

    static tMenuPanel *
    Hooked_CMenuSystem_DisplayGridMenu (unsigned __int8 a1, unsigned __int8 a2)
    {
        return nullptr;
    }

    static void
    Hooked_CMenuSystem_DisplayStandardMenu (unsigned __int8 panelId,
                                            bool            bBrightFont)
    {
    }

    static void
    Hooked_CHud_DrawAreaName ()
    {
    }
};

DEFINE_EFFECT (DisableHUDEffect, "effect_disable_hud", GROUP_HUD);