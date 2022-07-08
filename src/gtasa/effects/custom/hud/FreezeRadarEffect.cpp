#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CRadar.h>

class FreezeRadarEffect : public EffectBase
{
    static inline CVector   position     = {0.0f, 0.0f, 0.0f};
    static inline float     orientation  = 0.0f;
    static inline CVector2D cachedSinCos = {0.0f, 0.0f};
    bool                    positionSet  = false;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        position     = {0.0f, 0.0f, 0.0f};
        orientation  = 0.0f;
        cachedSinCos = {0.0f, 0.0f};
        positionSet  = false;

        HOOK (inst, Hooked_CRadar_DrawRadarMap, void (), 0x586D4E);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (positionSet) return;

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            position    = player->GetPosition ();
            orientation = player->GetHeading ();

            CRadar::CalculateCachedSinCos ();
            cachedSinCos = {CRadar::cachedSin, CRadar::cachedCos};

            positionSet = true;
        }
    }

    static void
    Hooked_CRadar_DrawRadarMap (auto &&cb)
    {
        CRadar::vec2DRadarOrigin.x = position.x;
        CRadar::vec2DRadarOrigin.y = position.y;

        CRadar::m_fRadarOrientation = orientation;

        CRadar::cachedSin = cachedSinCos.x;
        CRadar::cachedCos = cachedSinCos.y;

        cb ();
    }
};

DEFINE_EFFECT (FreezeRadarEffect, "effect_freeze_radar", GROUP_HUD);