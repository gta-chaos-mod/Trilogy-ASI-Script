#include "InvertedControlsEffect.h"

InvertedControlsEffect::InvertedControlsEffect ()
    : EffectBase ("effect_inverted_controls")
{
    AddType ("controls");
}

void
InvertedControlsEffect::InitializeHooks ()
{
    EffectBase::InitializeHooks ();

    HookCall (0x57C676, HookedOpenFile);

    HookCall (0x577244, HookedCMenuManagerProcessPCMenuOptions);
}

void
InvertedControlsEffect::Enable ()
{
    EffectBase::Enable ();

    for (int i = 0; i < 59; i++)
    {
        origActions[i] = invertedActions[i] = ControlsManager.m_actions[i];
    }

    // TODO: Convert to CPad calls
    SwapControls (e_ControllerAction::CA_PED_FIREWEAPON,
                  e_ControllerAction::CA_PED_LOCK_TARGET);
    SwapControls (e_ControllerAction::CA_GO_FORWARD,
                  e_ControllerAction::CA_GO_BACK);
    SwapControls (e_ControllerAction::CA_GO_LEFT,
                  e_ControllerAction::CA_GO_RIGHT);
    SwapControls (e_ControllerAction::CA_PED_SNIPER_ZOOM_IN,
                  e_ControllerAction::CA_PED_SNIPER_ZOOM_OUT);
    SwapControls (e_ControllerAction::CA_PED_SPRINT,
                  e_ControllerAction::CA_PED_JUMPING);
    SwapControls (e_ControllerAction::CA_PED_CYCLE_TARGET_LEFT,
                  e_ControllerAction::CA_PED_CYCLE_TARGET_RIGHT);
    SwapControls (e_ControllerAction::CA_CONVERSATION_YES,
                  e_ControllerAction::CA_CONVERSATION_NO);
    SwapControls (e_ControllerAction::CA_GROUP_CONTROL_FWD,
                  e_ControllerAction::CA_GROUP_CONTROL_BWD);

    SwapControls (e_ControllerAction::CA_VEHICLE_ACCELERATE,
                  e_ControllerAction::CA_VEHICLE_BRAKE);
    SwapControls (e_ControllerAction::CA_VEHICLE_STEERLEFT,
                  e_ControllerAction::CA_VEHICLE_STEERRIGHT);
    SwapControls (e_ControllerAction::CA_VEHICLE_STEERUP,
                  e_ControllerAction::CA_VEHICLE_STEERDOWN);
    SwapControls (e_ControllerAction::CA_VEHICLE_LOOKLEFT,
                  e_ControllerAction::CA_VEHICLE_LOOKRIGHT);
    SwapControls (e_ControllerAction::CA_VEHICLE_TURRETUP,
                  e_ControllerAction::CA_VEHICLE_TURRETDOWN);
    SwapControls (e_ControllerAction::CA_VEHICLE_TURRETLEFT,
                  e_ControllerAction::CA_VEHICLE_TURRETRIGHT);
    SwapControls (e_ControllerAction::CA_VEHICLE_HANDBRAKE,
                  e_ControllerAction::CA_VEHICLE_HORN);
}

void
InvertedControlsEffect::Disable ()
{
    for (int i = 0; i < 59; i++)
    {
        ControlsManager.m_actions[i] = origActions[i];
    }

    EffectBase::Disable ();
}

void
InvertedControlsEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    if (wait > 0)
    {
        wait -= CalculateTick ();
        return;
    }

    for (int i = 0; i < 59; i++)
    {
        ControlsManager.m_actions[i] = invertedActions[i];
    }

    wait = 1000;
}

void
InvertedControlsEffect::SwapControls (e_ControllerAction target,
                                      e_ControllerAction source)
{
    invertedActions[(int) target] = origActions[(int) source];
    invertedActions[(int) source] = origActions[(int) target];
}

FILESTREAM
InvertedControlsEffect::HookedOpenFile (const char *file, const char *mode)
{
    return 0;
}

void __fastcall InvertedControlsEffect::HookedCMenuManagerProcessPCMenuOptions (
    CMenuManager *thisManager, void *edx, eMenuPage page)
{
    if (page == eMenuPage::MENUPAGE_REDEFINE_CONTROLS)
    {
        return;
    }

    GameFixes::HookedProcessMenuOptions (thisManager, edx, page);
}
