#include "ForceVehicleMouseSteering.h"

bool ForceVehicleMouseSteering::overrideMouseSteering = true;

ForceVehicleMouseSteering::ForceVehicleMouseSteering ()
    : EffectBase ("effect_force_vehicle_mouse_steering")
{
    AddType ("controls");
}

void
ForceVehicleMouseSteering::InitializeHooks ()
{
    EffectBase::InitializeHooks ();

    HookCall (0x57C676, HookedOpenFile);

    HookCall (0x577244, HookedCMenuManagerProcessPCMenuOptions);
}

void
ForceVehicleMouseSteering::Enable ()
{
    EffectBase::Enable ();

    for (int address : {0x52565D + 2, // Mouse Steering
                        0x6AD7AC + 1, 0x6BE39C + 1, 0x6CE03D + 1, 0x6F0AFA + 1,

                        0x525665 + 2, // Mouse Flying
                        0x6C4880 + 1, 0x6CAE07 + 1})
    {
        injector::WriteMemory<bool *> (address, &overrideMouseSteering);
    }

    for (int i = 0; i < 59; i++)
    {
        origActions[i] = ControlsManager.m_actions[i];
    }
}

void
ForceVehicleMouseSteering::Disable ()
{
    for (int i = 0; i < 59; i++)
    {
        ControlsManager.m_actions[i] = origActions[i];
    }

    for (int address : {
             0x52565D + 2, // Mouse Steering
             0x6AD7AC + 1,
             0x6BE39C + 1,
             0x6CE03D + 1,
             0x6F0AFA + 1,
         })
    {
        injector::WriteMemory<bool *> (address,
                                       &CVehicle::m_bEnableMouseSteering);
    }

    for (int address : {0x525665 + 2, // Mouse Flying
                        0x6C4880 + 1, 0x6CAE07 + 1})
    {
        injector::WriteMemory<bool *> (address,
                                       &CVehicle::m_bEnableMouseFlying);
    }

    EffectBase::Disable ();
}

void
ForceVehicleMouseSteering::HandleTick ()
{
    EffectBase::HandleTick ();

    ControlsManager.m_actions[e_ControllerAction::CA_VEHICLE_STEERUP]
        = CControllerAction ();
    ControlsManager.m_actions[e_ControllerAction::CA_VEHICLE_STEERDOWN]
        = CControllerAction ();
    ControlsManager.m_actions[e_ControllerAction::CA_VEHICLE_STEERLEFT]
        = CControllerAction ();
    ControlsManager.m_actions[e_ControllerAction::CA_VEHICLE_STEERRIGHT]
        = CControllerAction ();
}

FILESTREAM
ForceVehicleMouseSteering::HookedOpenFile (const char *file, const char *mode)
{
    return 0;
}

void __fastcall ForceVehicleMouseSteering::
    HookedCMenuManagerProcessPCMenuOptions (CMenuManager *thisManager,
                                            void *edx, eMenuPage page)
{
    if (page == eMenuPage::MENUPAGE_REDEFINE_CONTROLS)
    {
        return;
    }

    GameFixes::HookedProcessMenuOptions (thisManager, edx, page);
}
