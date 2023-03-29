#include "util/EffectBase.h"
#include "util/GenericUtil.h"
#include <extensions/ScriptCommands.h>

enum class FakeEffectType
{
    WASTED,
    BUSTED
};

constexpr int FADE_IN_TIME       = 5000;
constexpr float FADE_IN_TIME_FLOAT     = FADE_IN_TIME * 0.001f;
constexpr float FADE_OUT_TIME_FLOAT    = 1.0f;
constexpr int   WAIT_TO_FADE_OUT_START = FADE_IN_TIME + 500;

using namespace plugin;

class GetWastedBustedFake : public EffectBase
{
    FakeEffectType type;
    int            wait = 0;

public:
    GetWastedBustedFake () = delete;

    GetWastedBustedFake (FakeEffectType effectType) : type (effectType) {}

    void
    OnStart (EffectInstance *inst) override
    {
        inst->SetIsOneTimeEffect ();
        inst->SetTimerVisible (false);

        std::string msg (type == FakeEffectType::WASTED ? "DEAD" : "BUSTED");
        Command<Commands::CLEAR_SMALL_PRINTS> ();
        Command<eScriptCommands::COMMAND_PRINT_BIG> (msg.data (), FADE_IN_TIME,
                                                     3);

        if (CTheScripts::IsPlayerOnAMission ())
        {
            Command<eScriptCommands::COMMAND_PRINT_BIG> ("M_FAIL", FADE_IN_TIME,
                                                         1);
        }

        TheCamera.Fade (FADE_IN_TIME_FLOAT, 0);
        
        auto *player = FindPlayerPed ();
        if (!player) return;

        int mode = (type == FakeEffectType::WASTED ? 29 : 32);
        Command<eScriptCommands::COMMAND_POINT_CAMERA_AT_CHAR> (player, mode,
                                                                2);

        if (type == FakeEffectType::BUSTED)
        {
            int res        = 0;
            int speechBank = 15;
            Command<eScriptCommands::COMMAND_SET_CHAR_SAY_CONTEXT> (player,
                                                                    speechBank,
                                                                    &res);
        }
    }

    void
    OnTick (EffectInstance *inst)
    {
        auto *player = FindPlayerPed ();
        if (!player) return;

        auto *pad = player->GetPadFromPlayer ();
        if (!pad) return;
        
        pad->DisablePlayerControls = true;

        wait += int (GenericUtil::CalculateTick ());

        if (wait >= WAIT_TO_FADE_OUT_START)
        {
            if (CTheScripts::IsPlayerOnAMission ())
            {
                Command<eScriptCommands::COMMAND_CLEAR_THIS_PRINT_BIG_NOW> (1);
            }
            Command<eScriptCommands::COMMAND_CLEAR_THIS_PRINT_BIG_NOW> (3);

            Command<eScriptCommands::COMMAND_RESTORE_CAMERA> ();

            TheCamera.Fade (FADE_OUT_TIME_FLOAT, 1);            

            pad->DisablePlayerControls = false;            

            wait = 0;

            inst->OverrideName (std::string (inst->GetName ()) + "?");
            inst->Disable ();
        }
    }
};

DEFINE_EFFECT (GetWastedBustedFake, "effect_get_busted_fake", GROUP_VISION,
               FakeEffectType::BUSTED);
DEFINE_EFFECT (GetWastedBustedFake, "effect_get_wasted_fake", GROUP_VISION,
               FakeEffectType::WASTED);
