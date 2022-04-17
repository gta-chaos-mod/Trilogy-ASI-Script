#include <effects/OneTimeEffect.h>

#include "extensions/ScriptCommands.h"

using namespace plugin;

class DeleteVehicleEffect : public OneTimeEffect
{
public:
    bool
    CanActivate () override
    {
        return FindPlayerVehicle (-1, false) != nullptr;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle)
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

DEFINE_EFFECT (DeleteVehicleEffect, "effect_delete_vehicle", 0);