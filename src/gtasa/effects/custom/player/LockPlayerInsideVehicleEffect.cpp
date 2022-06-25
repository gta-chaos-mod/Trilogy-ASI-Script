#include "util/EffectBase.h"

class LockPlayerInsideVehicleEffect : public EffectBase
{
public:
    bool
    CanActivate () override
    {
        return FindPlayerVehicle (-1, false);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player) player->m_nPedFlags.CantBeKnockedOffBike = 0;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle) vehicle->m_nDoorLock = eCarLock::CARLOCK_UNLOCKED;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CVehicle *vehicle = FindPlayerVehicle (-1, false);

        if (vehicle && vehicle->CanBeDriven ()
            && vehicle->m_nStatus != STATUS_WRECKED)
        {
            vehicle->m_nDoorLock = eCarLock::CARLOCK_LOCKED_PLAYER_INSIDE;

            CPlayerPed *player = FindPlayerPed ();
            if (player) player->m_nPedFlags.CantBeKnockedOffBike = 1;
        }

        inst->SetTimerVisible (vehicle != nullptr);
    }
};

DEFINE_EFFECT (LockPlayerInsideVehicleEffect,
               "effect_lock_player_inside_vehicle", 0);