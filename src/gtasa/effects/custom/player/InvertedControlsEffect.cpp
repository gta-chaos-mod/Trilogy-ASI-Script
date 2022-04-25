#include "util/EffectBase.h"

class InvertedControlsEffect : public EffectBase
{
public:
    void
    OnProcessScripts (EffectInstance *inst) override
    {
        // TODO: Convert to CPad overrides
        // SwapControls (e_ControllerAction::CA_PED_FIREWEAPON,
        //             e_ControllerAction::CA_PED_LOCK_TARGET);
        // SwapControls (e_ControllerAction::CA_GO_FORWARD,
        //             e_ControllerAction::CA_GO_BACK);
        // SwapControls (e_ControllerAction::CA_GO_LEFT,
        //             e_ControllerAction::CA_GO_RIGHT);
        // SwapControls (e_ControllerAction::CA_PED_SNIPER_ZOOM_IN,
        //             e_ControllerAction::CA_PED_SNIPER_ZOOM_OUT);
        // SwapControls (e_ControllerAction::CA_PED_SPRINT,
        //             e_ControllerAction::CA_PED_JUMPING);
        // SwapControls (e_ControllerAction::CA_PED_CYCLE_TARGET_LEFT,
        //             e_ControllerAction::CA_PED_CYCLE_TARGET_RIGHT);
        // SwapControls (e_ControllerAction::CA_CONVERSATION_YES,
        //             e_ControllerAction::CA_CONVERSATION_NO);
        // SwapControls (e_ControllerAction::CA_GROUP_CONTROL_FWD,
        //             e_ControllerAction::CA_GROUP_CONTROL_BWD);

        // SwapControls (e_ControllerAction::CA_VEHICLE_ACCELERATE,
        //             e_ControllerAction::CA_VEHICLE_BRAKE);
        // SwapControls (e_ControllerAction::CA_VEHICLE_STEERLEFT,
        //             e_ControllerAction::CA_VEHICLE_STEERRIGHT);
        // SwapControls (e_ControllerAction::CA_VEHICLE_STEERUP,
        //             e_ControllerAction::CA_VEHICLE_STEERDOWN);
        // SwapControls (e_ControllerAction::CA_VEHICLE_LOOKLEFT,
        //             e_ControllerAction::CA_VEHICLE_LOOKRIGHT);
        // SwapControls (e_ControllerAction::CA_VEHICLE_TURRETUP,
        //             e_ControllerAction::CA_VEHICLE_TURRETDOWN);
        // SwapControls (e_ControllerAction::CA_VEHICLE_TURRETLEFT,
        //             e_ControllerAction::CA_VEHICLE_TURRETRIGHT);
        // SwapControls (e_ControllerAction::CA_VEHICLE_HANDBRAKE,
        //             e_ControllerAction::CA_VEHICLE_HORN);

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPad *pad = player->GetPadFromPlayer ();
            if (pad)
            {
                pad->NewState.LeftStickX *= -1;
                pad->NewState.LeftStickY *= -1;
                pad->NewState.RightStickX *= -1;
                pad->NewState.RightStickY *= -1;

                pad->NewMouseControllerState.X *= -1;
                pad->NewMouseControllerState.Y *= -1;

                std::swap (pad->NewState.ButtonCross,
                           pad->NewState.ButtonSquare);
                std::swap (pad->NewState.ButtonCircle,
                           pad->NewState.RightShoulder1);

                std::swap (pad->NewState.DPadUp, pad->NewState.DPadDown);
                std::swap (pad->NewState.DPadLeft, pad->NewState.DPadRight);

                std::swap (pad->NewState.Start, pad->NewState.Select);

                std::swap (pad->NewState.ShockButtonL,
                           pad->NewState.ShockButtonR);
            }
        }
    }
};

DEFINE_EFFECT (InvertedControlsEffect, "effect_inverted_controls",
               GROUP_CONTROLS);