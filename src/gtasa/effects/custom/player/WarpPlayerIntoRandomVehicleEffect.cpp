#include <util/EffectBase.h>

#include "CCamera.h"

#include "extensions/ScriptCommands.h"

using namespace plugin;

class WarpPlayerIntoRandomVehicleEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            if (vehicle->m_pDriver && vehicle->m_pDriver != player)
            {
                for (int i = 0; i < vehicle->m_nMaxPassengers; i++)
                {
                    if (Command<eScriptCommands::
                                    COMMAND_IS_CAR_PASSENGER_SEAT_FREE> (
                            vehicle, i))
                    {
                        Command<eScriptCommands::
                                    COMMAND_WARP_CHAR_INTO_CAR_AS_PASSENGER> (
                            player, vehicle, i);

                        Command<
                            eScriptCommands::COMMAND_RESTORE_CAMERA_JUMPCUT> ();

                        return;
                    }
                }
            }
        }
    }
};

DEFINE_EFFECT (WarpPlayerIntoRandomVehicleEffect,
               "effect_warp_player_into_random_vehicle", 0);