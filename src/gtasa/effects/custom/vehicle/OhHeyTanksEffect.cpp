#include "effects/OneTimeEffect.h"
#include "util/GameUtil.h"
#include "util/MathHelper.h"

class OhHeyTanksEffect : public OneTimeEffect
{
public:
    bool
    CanActivate () override
    {
        CPlayerPed *player = FindPlayerPed ();

        return player && !player->m_nAreaCode;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player || player->m_nAreaCode) return;

        for (int x = 0; x < 12; x++)
        {
            float angle     = 360.0f / 12 * x;
            float angle_rad = MathHelper::ToRadians (angle);

            CVector position = player->TransformFromObjectSpace (
                CVector (25.0f * sin (angle_rad), 25.0f * cos (angle_rad),
                         5.0f));
            CVehicle *vehicle = GameUtil::CreateVehicle (
                432, position, MathHelper::ToRadians (180.0f - angle), true);
        }
    }
};

DEFINE_EFFECT (OhHeyTanksEffect, "effect_oh_hey_tanks", 0);