#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CMenuSystem.h>
#include <CWorld.h>

/*
    TODO: Doesn't seem to work with "Walk On Water" - tries to set player to
   water position
*/

class TheFlashEffect : public EffectBase
{
    bool oldInfiniteRun = false;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD_ARGS (inst, Hooked_CEventDamage_AffectsPed,
                          bool (CEventDamage *, CPed *), 0x5E2F57, 0x5E3020);

        this->oldInfiniteRun = injector::ReadMemory<bool> (0xB7CEE4);
        injector::WriteMemory (0xB7CEE4, true);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        injector::WriteMemory (0x8D2458, 5.0f);
        injector::WriteMemory (0xB7CEE4, this->oldInfiniteRun);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            // Infinite Lung Capacity
            player->ResetPlayerBreath ();

            CPad *pad = player->GetPadFromPlayer ();
            if (pad)
            {
                // Auto Super Sprint
                bool canFastSprint
                    = pad->GetSprint ()
                      && !CMenuSystem::MenuInUse[CMenuSystem::CurrentMenuInUse];

                if (canFastSprint)
                {
                    pad->NewState.ButtonCross = 0;

                    if (player->m_pIntelligence->GetTaskSwim () == nullptr
                        && !player->m_nPhysicalFlags.bTouchingWater)
                    {
                        // Update Z Pos To Ground Pos
                        CVector pos    = player->GetMatrix ()->pos;
                        bool    worked = false;
                        float   newZ
                            = CWorld::FindGroundZFor3DCoord (pos.x, pos.y,
                                                             pos.z, &worked,
                                                             nullptr);
                        if (worked)
                        {
                            player->GetMatrix ()->pos.z
                                = std::max (0.0f, newZ + 0.5f);
                        }
                    }
                }

                injector::WriteMemory (0x8D2458, canFastSprint ? 0.25f : 5.0f);
            }
        }
    }

    static bool
    Hooked_CEventDamage_AffectsPed (auto &&cb, CEventDamage *thisEventDamage,
                                    CPed *ped)
    {
        return false;
    }
};

DEFINE_EFFECT (TheFlashEffect, "effect_the_flash", 0);