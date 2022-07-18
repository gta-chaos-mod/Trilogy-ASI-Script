#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/MathHelper.h"
#include "util/Teleportation.h"

#include <CCheat.h>
#include <CStreaming.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class BlowUpRydersCarEffect : public EffectBase
{
    bool      teleported = false;
    CVehicle *rydersCar  = nullptr;
    int       pistolAmmo = 0;

public:
    bool
    CanActivate () override
    {
        return GameUtil::IsPlayerSafe () && Teleportation::CanTeleport ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        if (IsVehiclePointerValid (rydersCar))
            Command<eScriptCommands::COMMAND_DELETE_CAR> (rydersCar);

        rydersCar  = nullptr;
        teleported = false;
        pistolAmmo = 0;

        inst->SetDuration (1000 * 15);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CPad *pad = player->GetPadFromPlayer ();
        if (pad) pad->bDisablePlayerCycleWeapon = false;

        if (!rydersCar || !IsVehiclePointerValid (rydersCar)
            || rydersCar->m_nStatus != STATUS_WRECKED)
        {
            CCheat::SuicideCheat ();
            return;
        }

        if (pistolAmmo > 0)
        {
            CStreaming::RequestModel (MODEL_COLT45, 2); // Colt 45
            CStreaming::LoadAllRequestedModels (false);

            player->GiveWeapon (WEAPON_PISTOL, pistolAmmo, 1);

            CStreaming::SetModelIsDeletable (MODEL_COLT45);

            player->SetCurrentWeapon (player->GetWeaponSlot (WEAPON_PISTOL));
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (teleported)
        {
            if (rydersCar && IsVehiclePointerValid (rydersCar)
                && rydersCar->m_nStatus == STATUS_WRECKED)
            {
                inst->Disable ();
            }
            return;
        }

        if (!CanActivate ())
        {
            inst->ResetTimer ();
            return;
        }

        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CPad *pad = player->GetPadFromPlayer ();
        if (pad) pad->bDisablePlayerCycleWeapon = true;

        CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
        if (playerVehicle)
        {
            Command<eScriptCommands::
                        COMMAND_REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION> (
                player, playerVehicle);
        }

        Teleportation::Teleport (CVector (2476.56f, -1698.14f, 13.52f));
        Command<eScriptCommands::COMMAND_SET_CHAR_ROTATION> (player, 0.0f, 0.0f,
                                                             15.0f);
        Command<eScriptCommands::COMMAND_RESTORE_CAMERA_JUMPCUT> ();

        rydersCar
            = GameUtil::CreateVehicle (600,
                                       CVector (2473.53f, -1690.21f, 13.0f),
                                       0.0f, true);

        // Clear the weapon so the player only has 1 shot
        if (player->DoWeHaveWeaponAvailable (WEAPON_PISTOL))
        {
            pistolAmmo
                = player->m_aWeapons[player->GetWeaponSlot (WEAPON_PISTOL)]
                      .m_nTotalAmmo;
            player->ClearWeapon (WEAPON_PISTOL);
        }

        CStreaming::RequestModel (MODEL_COLT45, 2); // Colt 45
        CStreaming::LoadAllRequestedModels (false);

        player->GiveWeapon (WEAPON_PISTOL, 1, 1);

        CStreaming::SetModelIsDeletable (MODEL_COLT45);

        player->SetCurrentWeapon (player->GetWeaponSlot (WEAPON_PISTOL));

        teleported = true;
    }
};

DEFINE_EFFECT (BlowUpRydersCarEffect, "effect_blow_up_ryders_car", 0);