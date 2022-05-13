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

        // CRadar::DrawBlips
        HOOK (inst, Hooked_Empty, void (), 0x58AA2d, 0x575B44);

        // CCoronas::Render
        HOOK (inst, Hooked_Empty, void (), 0x53E18E);

        // C3dMarker::Render
        HOOK_METHOD (inst, Hooked_Empty, void (C3dMarker *), 0x7250B1);

        // CCheckpoint::Render
        HOOK (inst, Hooked_Empty, void (), 0x72606F);
    }

    static void
    Hooked_Empty (auto &&cb)
    {
    }
};

DEFINE_EFFECT (DisableBlipsMarkersPickupsEffect,
               "effect_disable_blips_markers_pickups", GROUP_HUD);