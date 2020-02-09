#include "SmashNBoomCheat.h"

SmashNBoomCheat::SmashNBoomCheat ()
    : TimedAddressEffect ("cheat_smash_n_boom", 0x969164)
{
}

void
SmashNBoomCheat::Disable ()
{
    CPlayerPed *player = FindPlayerPed ();
    for (CVehicle *vehicle : CPools::ms_pVehiclePool)
    {
        vehicle->m_nPhysicalFlags.bInvulnerable   = false;
        vehicle->m_nPhysicalFlags.bExplosionProof = false;
        vehicle->m_nPhysicalFlags.bFireProof      = false;
        vehicle->m_nPhysicalFlags.bCollisionProof = false;
    }

    TimedAddressEffect::Disable ();
}

void
SmashNBoomCheat::HandleTick ()
{
    TimedAddressEffect::HandleTick ();

    CPlayerPed *player = FindPlayerPed ();
    for (CVehicle *vehicle : CPools::ms_pVehiclePool)
    {
        bool proof = (player && player->m_pVehicle == vehicle
                      && player->m_pVehicle->IsDriver (player));
        vehicle->m_nPhysicalFlags.bInvulnerable   = proof;
        vehicle->m_nPhysicalFlags.bExplosionProof = proof;
        vehicle->m_nPhysicalFlags.bFireProof      = proof;
        vehicle->m_nPhysicalFlags.bCollisionProof = proof;
    }
}
