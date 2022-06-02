#include "util/EffectBase.h"
#include "util/Variables.h"
#include "util/hooks/HookMacros.h"

#include <CMenuSystem.h>
#include <CWorld.h>

class TheFlashEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD_ARGS (inst, Hooked_CEventDamage_AffectsPed,
                          bool (CEventDamage *, CPed *), 0x5E2F57, 0x5E3020);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        injector::WriteMemory (0x8D2458, 5.0f);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        // Reset sprint energy
        player->ResetSprintEnergy ();

        // Infinite Lung Capacity
        player->ResetPlayerBreath ();

        CPad *pad = player->GetPadFromPlayer ();
        if (!pad) return;

        // Auto Super Sprint
        bool canFastSprint
            = pad->GetSprint ()
              && !CMenuSystem::MenuInUse[CMenuSystem::CurrentMenuInUse];

        injector::WriteMemory (0x8D2458, canFastSprint ? 0.25f : 5.0f);

        if (!canFastSprint) return;

        pad->NewState.ButtonCross = 0;

        if (player->m_pIntelligence->GetTaskJetPack ()) return;

        if (player->m_pIntelligence->GetTaskSwim ()
            || player->m_nPhysicalFlags.bTouchingWater)
            return;

        // Update Z Pos To Ground Pos
        CVector pos    = player->GetMatrix ()->pos;
        bool    worked = false;
        float   newZ   = CWorld::FindGroundZFor3DCoord (pos.x, pos.y, pos.z,
                                                        &worked, nullptr);

        if (!worked) return;

        if (Variables::isWalkOnWaterEffectEnabled) newZ = std::max (0.0f, newZ);

        player->GetMatrix ()->pos.z = newZ + 0.5f;
    }

    static bool
    Hooked_CEventDamage_AffectsPed (auto &&cb, CEventDamage *thisEventDamage,
                                    CPed *ped)
    {
        return false;
    }
};

DEFINE_EFFECT (TheFlashEffect, "effect_the_flash", 0);