#include "effects/OneTimeEffect.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

class DeleteAllVehiclesEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            RemovePassengers (vehicle);

            Command<eScriptCommands::COMMAND_DELETE_CAR> (vehicle);
        }
    }

    void
    RemovePassengers (CVehicle *vehicle)
    {
        if (vehicle->m_pDriver)
        {
            Command<eScriptCommands::
                        COMMAND_REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION> (
                vehicle->m_pDriver, vehicle);
        }

        for (CPed *ped : vehicle->m_apPassengers)
        {
            if (ped)
            {
                Command<eScriptCommands::
                            COMMAND_REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION> (
                    ped, vehicle);
            }
        }
    }
};

DEFINE_EFFECT (DeleteAllVehiclesEffect, "effect_delete_all_vehicles", 0);