#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include <CCamera.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

// TODO: CJ can't exit a vehicle as a passenger if it's not stopped.
// Maybe some check we can hook?
class WarpPlayerIntoRandomVehicleEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        if (!GameUtil::IsPlayerSafe ())
        {
            inst->ResetTimer ();
            return;
        }

        CPlayerPed *player  = FindPlayerPed ();
        CVehicle   *vehicle = GetRandomVehicle (inst);
        if (!vehicle || !vehicle->CanBeDriven ()
            || vehicle->m_nStatus == STATUS_WRECKED)
            return;

        if (!vehicle->m_pDriver
            || vehicle->m_pDriver && vehicle->m_pDriver != player)
        {
            for (int i = 0; i < vehicle->m_nMaxPassengers; i++)
            {
                if (Command<
                        eScriptCommands::COMMAND_IS_CAR_PASSENGER_SEAT_FREE> (
                        vehicle, i))
                {
                    Command<eScriptCommands::
                                COMMAND_WARP_CHAR_INTO_CAR_AS_PASSENGER> (
                        player, vehicle, i);

                    Command<eScriptCommands::COMMAND_RESTORE_CAMERA_JUMPCUT> ();

                    inst->Disable ();
                }
            }
        }

        CPad *pad = player->GetPadFromPlayer ();
        if (!pad) return;

        pad->bDisablePlayerEnterCar = false;
    }

    CVehicle *
    GetRandomVehicle (EffectInstance *inst, int attempts = 0)
    {
        int randomNumber  = inst->Random (0, CPools::ms_pVehiclePool->m_nSize);
        CVehicle *vehicle = CPools::ms_pVehiclePool->GetAt (randomNumber);

        if (IsVehiclePointerValid (vehicle)) return vehicle;

        attempts += 1;
        if (attempts > 10) return nullptr;

        return GetRandomVehicle (inst, attempts);
    }
};

DEFINE_EFFECT (WarpPlayerIntoRandomVehicleEffect,
               "effect_warp_player_into_random_vehicle", 0);