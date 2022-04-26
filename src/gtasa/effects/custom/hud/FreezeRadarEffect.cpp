#include "util/EffectBase.h"

#include <CRadar.h>

using namespace plugin;

class FreezeRadarEffect : public EffectBase
{
    static inline CVector position    = {0.0f, 0.0f, 0.0f};
    bool                  positionSet = false;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        position    = {0.0f, 0.0f, 0.0f};
        positionSet = false;

        injector::MakeJMP (0x586D4E, Hooked_CRadar_DrawRadarMap);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        injector::MakeJMP (0x586D4E, 0x586880);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (positionSet) return;

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            position = player->GetPosition ();

            positionSet = true;
        }
    }

    static void
    Hooked_CRadar_DrawRadarMap ()
    {
        CRadar::vec2DRadarOrigin.x = position.x;
        CRadar::vec2DRadarOrigin.y = position.y;

        Call<0x586880> ();
    }
};

DEFINE_EFFECT (FreezeRadarEffect, "effect_freeze_radar", GROUP_HUD);