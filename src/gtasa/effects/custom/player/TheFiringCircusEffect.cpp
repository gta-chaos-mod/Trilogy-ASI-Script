// Inspiration from Zolika's Chaos Mod - "Sacrificial Circle"

#include <effects/OneTimeEffect.h>
#include <util/MathHelper.h>

#include "extensions/ScriptCommands.h"
#include "CStreaming.h"

using namespace plugin;

class TheFiringCircusEffect : public OneTimeEffect
{
public:
    bool
    CanActivate () override
    {
        return FindPlayerPed () != nullptr
               && FindPlayerVehicle (-1, false) != nullptr;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            for (int x = 0; x < 6; x++)
            {
                float angle     = 360.0f / 6 * x;
                float angle_rad = MathHelper::ToRadians (angle);

                CVector position      = player->GetPosition ();
                CVector spawnPosition = player->TransformFromObjectSpace (
                    CVector (5.0f * sin (angle_rad), 5.0f * cos (angle_rad),
                             0.25f));

                int modelId = 264;

                CStreaming::RequestModel (modelId, 2);
                CStreaming::LoadAllRequestedModels (0);
                CStreaming::SetModelIsDeletable (modelId);

                CPed *createdPed;
                Command<eScriptCommands::COMMAND_CREATE_CHAR> (
                    ePedType::PED_TYPE_CIVMALE, modelId, spawnPosition.x,
                    spawnPosition.y, spawnPosition.z, &createdPed);

                Command<eScriptCommands::COMMAND_SET_CHAR_RELATIONSHIP> (
                    createdPed, 4, ePedType::PED_TYPE_PLAYER1);

                CStreaming::RequestModel (MODEL_M4, 2);
                CStreaming::LoadAllRequestedModels (0);
                CStreaming::SetModelIsDeletable (MODEL_M4);

                Command<eScriptCommands::COMMAND_GIVE_WEAPON_TO_CHAR> (
                    createdPed, eWeaponType::WEAPON_M4, 9999);
                Command<eScriptCommands::COMMAND_SET_CURRENT_CHAR_WEAPON> (
                    createdPed, eWeaponType::WEAPON_M4);

                Command<eScriptCommands::COMMAND_TASK_KILL_CHAR_ON_FOOT> (
                    createdPed, player);
            }
        }
    }
};

DEFINE_EFFECT (TheFiringCircusEffect, "effect_the_firing_circus", 0);
