#include "util/Config.h"
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
        bool lock = false;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle)
        {
            lock
                = Config::GetOrDefault ("Chaos.LockPlayerInVehicleAfterDisable",
                                        true);
        }
        else
        {
            lock = false;
        }

        if (vehicle)
        {
            vehicle->m_nDoorLock = lock ? eCarLock::CARLOCK_LOCKED_PLAYER_INSIDE
                                        : eCarLock::CARLOCK_UNLOCKED;

            CPlayerPed *player = FindPlayerPed ();
            if (player)
            {
                player->m_nPedFlags.CantBeKnockedOffBike = lock ? 1 : 0;
            }
        }

        inst->SetTimerVisible (lock);
    }
};

DEFINE_EFFECT (LockPlayerInsideVehicleEffect,
               "effect_lock_player_inside_vehicle", 0);