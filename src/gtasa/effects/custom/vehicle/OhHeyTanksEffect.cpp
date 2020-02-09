#include "OhHeyTanksEffect.h"

OhHeyTanksEffect::OhHeyTanksEffect ()
    : EffectPlaceholder ("effect_oh_hey_tanks")
{
}

void
OhHeyTanksEffect::Enable ()
{
    EffectPlaceholder::Enable ();

    SpawnTanks ();
}

bool
OhHeyTanksEffect::CanActivate ()
{
    CPlayerPed *player = FindPlayerPed ();

    return player && !player->m_nAreaCode;
}

void
OhHeyTanksEffect::SpawnTanks ()
{
    CPlayerPed *player = FindPlayerPed ();
    if (player && !player->m_nAreaCode)
    {
        for (int x = 0; x < 12; x++)
        {
            float angle     = 360.0f / 12 * x;
            float angle_rad = ToRadians (angle);

            CVector position = player->TransformFromObjectSpace (
                CVector (25.0f * sin (angle_rad), 25.0f * cos (angle_rad),
                         5.0f));
            CVehicle *vehicle
                = GameUtil::CreateVehicle (432, position,
                                           ToRadians (180.0f - angle));
        }
    }
}

float
OhHeyTanksEffect::ToRadians (float angle)
{
    return (angle * (float) M_PI) / 180.0f;
}
