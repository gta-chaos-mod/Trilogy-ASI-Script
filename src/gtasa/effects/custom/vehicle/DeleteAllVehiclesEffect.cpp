#include "util/EffectBase.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

class DeleteAllVehiclesEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        inst->SetIsOneTimeEffect ();

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            RemovePassengers (vehicle);

            vehicle->m_nStatus = eEntityStatus::STATUS_WRECKED;
        }
    }

    void
    OnProcessScripts (EffectInstance *inst) override
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            Command<eScriptCommands::COMMAND_DELETE_CAR> (vehicle);
        }

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

DEFINE_EFFECT (DeleteAllVehiclesEffect, "effect_delete_all_vehicles", 0);