#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <C3dMarker.h>
#include <CPickup.h>

using namespace plugin;

class DisableBlipsMarkersPickupsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        // Patch "IsVisible" check in CPickups::Update
        inst->WriteMemory<uint8_t> (0x458E4C, 0xeb);

        HOOK (inst, Hooked_CRadar_DrawBlips, void (), 0x58AA2d, 0x575B44);

        HOOK (inst, Hooked_CCoronas_Render, void (), 0x53E18E);

        HOOK_METHOD (inst, Hooked_C3dMarker_Render, void (C3dMarker *),
                     0x7250B1);

        HOOK (inst, Hooked_CCheckpoint_Render, void (), 0x72606F);
    }

    static void
    Hooked_CRadar_DrawBlips (auto &&cb)
    {
    }

    static void
    Hooked_CCoronas_Render (auto &&cb)
    {
    }

    static void
    Hooked_C3dMarker_Render (auto &&cb)
    {
    }

    static void
    Hooked_CCheckpoint_Render (auto &&cb)
    {
    }
};

DEFINE_EFFECT (DisableBlipsMarkersPickupsEffect,
               "effect_disable_blips_markers_pickups", GROUP_HUD);