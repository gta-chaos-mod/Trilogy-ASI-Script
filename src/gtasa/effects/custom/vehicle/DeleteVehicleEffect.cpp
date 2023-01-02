#include "util/EffectBase.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

class DeleteVehicleEffect : public EffectBase
{
    CVehicle *vehicle = nullptr;

public:
    bool
    CanActivate () override
    {
        return FindPlayerVehicle (-1, false);
    }

    void
    OnStart (EffectInstance *inst) override
    {
        inst->SetIsOneTimeEffect ();

        vehicle = FindPlayerVehicle (-1, false);
        if (!vehicle)
        {
            inst->Disable ();
            return;
        }

        RemovePassengers (vehicle);

        vehicle->m_nStatus = eEntityStatus::STATUS_WRECKED;
    }

    void
    OnProcessScripts (EffectInstance *inst) override
    {
        Command<eScriptCommands::COMMAND_DELETE_CAR> (vehicle);

        inst->Disable ();
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