#include "GameUtil.h"

CPedAcquaintance *
GameUtil::GetPedTypeAcquaintances (int PedType)
{
    return plugin::CallAndReturn<CPedAcquaintance *, 0x6089B0> (PedType);
}

void
GameUtil::BackupAcquaintances ()
{
    SaveAcquaintances (backupAcquaintances);
}

void
GameUtil::RestoreSavedAcquaintances ()
{
    LoadAcquaintances (backupAcquaintances);
}

void
GameUtil::SaveAcquaintances (CPedAcquaintance *acquaintances)
{
    for (int i = 0; i < 32; i++)
    {
        memcpy (&acquaintances[i], GetPedTypeAcquaintances (i),
                sizeof (CPedAcquaintance));
    }
}

void
GameUtil::LoadAcquaintances (CPedAcquaintance *acquaintances)
{
    for (int i = 0; i < 32; i++)
    {
        memcpy (GetPedTypeAcquaintances (i), &acquaintances[i],
                sizeof (CPedAcquaintance));
    }
}

void
GameUtil::DeleteAutoSave ()
{
    std::sprintf (CGenericGameStorage::ms_ValidSaveName,
                  "%s\\chaos_mod\\chaos_autosave.b", gamePath);

    if (std::filesystem::exists (CGenericGameStorage::ms_ValidSaveName))
    {
        std::filesystem::remove (CGenericGameStorage::ms_ValidSaveName);
    }
}

void
GameUtil::SaveToFile (std::string fileName)
{
    std::sprintf (CGenericGameStorage::ms_ValidSaveName, "%s\\%s", gamePath,
                  fileName.c_str ());

    std::filesystem::path p (CGenericGameStorage::ms_ValidSaveName);
    std::filesystem::create_directories (p.parent_path ());

    // Temporarily disable cheats and certain effects so they don't get saved
    for (int i = 0; i < 92; i++)
    {
        CCheat::m_aCheatsActive[i] = false;
    }

    CPedAcquaintance temp_acquaintances[32];
    SaveAcquaintances (temp_acquaintances);
    RestoreSavedAcquaintances ();

    // Ensure player has at least 1.0f health
    CPlayerPed *player = FindPlayerPed ();
    if (player) player->m_fHealth = std::max (1.0f, player->m_fHealth);

    CGenericGameStorage::GenericSave (0);

    LoadAcquaintances (temp_acquaintances);
}

bool
GameUtil::LoadFromFile (std::string fileName)
{
    std::sprintf (CGenericGameStorage::ms_LoadFileName, "%s\\%s", gamePath,
                  fileName.c_str ());

    if (std::filesystem::exists (CGenericGameStorage::ms_LoadFileName))
    {
        FrontEndMenuManager.m_bLoadingData = true;
        FrontEndMenuManager.m_bMenuActive  = false;

        byte gameState = injector::ReadMemory<byte> (0xC8D4C0); // GameState

        if (gameState == 9)
        {
            CGame::ShutDownForRestart ();
            CGame::InitialiseWhenRestarting ();
        }

        return true;
    }

    return false;
}

std::string
GameUtil::GetLoadFileName ()
{
    return loadFilePath;
}

void
GameUtil::SetVehiclesToRealPhysics ()
{
    for (CVehicle *vehicle : CPools::ms_pVehiclePool)
    {
        if (!vehicle->m_pDriver) continue;
        if (!vehicle->CanBeDriven ()) continue;
        if (vehicle->m_nStatus == STATUS_WRECKED) continue;
        if (vehicle->m_nStatus != STATUS_SIMPLE) continue;
        if (vehicle->IsDriver (FindPlayerPed ())) continue;

        CCarCtrl::SwitchVehicleToRealPhysics (vehicle);
    }
}

int
GameUtil::GetRealMissionsPassed ()
{
    int passed = 0;

    // Los Santos
    passed += injector::ReadMemory<byte> (0xA4A060); // Intro
    passed += injector::ReadMemory<byte> (0xA4A070); // Sweet
    passed += injector::ReadMemory<byte> (0xA4A07C); // OG Loc
    passed += injector::ReadMemory<byte> (0xA4A080); // Crash
    passed += injector::ReadMemory<byte> (0xA4A074); // Ryder
    passed += injector::ReadMemory<byte> (0xA4A078); // Smoke
    passed += injector::ReadMemory<byte> (0xA4A084); // Lowrider
    passed += injector::ReadMemory<byte> (0xA4A088); // LS Final

    // Badlands
    passed += injector::ReadMemory<byte> (0xA4A114); // Badlands
    passed += injector::ReadMemory<byte> (0xA4A10C); // The Truth
    passed += injector::ReadMemory<byte> (0xA4A110)
              / 5; // Cesar (both races increase throughout the race - we are
                   // interested in 5 and 10)
    passed += injector::ReadMemory<byte> (
        0xA4A488); // Catalina (Local Liquor Store)
    passed
        += injector::ReadMemory<byte> (0xA4A48C); // Catalina (Small Town Bank)
    passed
        += injector::ReadMemory<byte> (0xA4A490); // Catalina (Tanker Commander)
    passed
        += injector::ReadMemory<byte> (0xA4A494); // Catalina (Against All Odds)
    passed += injector::ReadMemory<byte> (0xA4BB2C); // King in Exile

    // San Fierro
    passed += injector::ReadMemory<byte> (0xA4A1D4); // Garage
    passed += injector::ReadMemory<byte> (0xA4A1DC); // Wuzimu
    passed += injector::ReadMemory<byte> (0xA4A1E4); // Syndicate
    passed += injector::ReadMemory<byte> (0xA4A1E8); // Crash
    passed += injector::ReadMemory<byte> (0xA4A1D8); // Zero
    passed += injector::ReadMemory<byte> (0xA4A1E0); // Steal

    // Las Venturas
    passed += injector::ReadMemory<byte> (0xA4A2A4); // Toreno
    passed += injector::ReadMemory<byte> (0xA4A2B4); // Casino
    passed += injector::ReadMemory<byte> (0xA4A2B8); // Crash
    passed += injector::ReadMemory<byte> (0xA4A2BC); // Madd Dogg
    passed += injector::ReadMemory<byte> (0xA4A2C0); // Heist

    // Return to Los Santos
    passed += injector::ReadMemory<byte> (0xA4A328); // Mansion
    passed += injector::ReadMemory<byte> (0xA4A32C); // Grove
    passed += injector::ReadMemory<byte> (0xA4A334); // Riot

    return passed;
}

void
GameUtil::RebuildPlayer ()
{
    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        ePedState oldState  = player->m_nPedState;
        player->m_nPedState = PEDSTATE_IDLE;
        CClothes::RebuildPlayer (player, false);
        player->m_nPedState = oldState;
    }
}

void
GameUtil::RemovePlayerBalaclava ()
{
    CPlayerPed *player = FindPlayerPed ();
    if (player)
    {
        CPedClothesDesc *clothes = player->m_pPlayerData->m_pPedClothesDesc;
        if (clothes && clothes->GetIsWearingBalaclava ())
        {
            clothes->SetTextureAndModel ((unsigned int) 0, (unsigned int) 0,
                                         17);
            RebuildPlayer ();
        }
    }
}

CVehicle *
GameUtil::CreateVehicle (int vehicleID, CVector position, float orientation,
                         bool clearSpace)
{
    if (vehicleID == 569)
    {
        vehicleID = 537; // 569 crashes the game when spawned in apparently
    }

    unsigned char oldFlags = CStreaming::ms_aInfoForModel[vehicleID].m_nFlags;
    CStreaming::RequestModel (vehicleID, GAME_REQUIRED);
    CStreaming::LoadAllRequestedModels (false);
    CStreaming::SetModelIsDeletable (vehicleID);
    if (CStreaming::ms_aInfoForModel[vehicleID].m_nLoadState
        == LOADSTATE_LOADED)
    {
        if (!(oldFlags & GAME_REQUIRED))
        {
            CStreaming::SetModelIsDeletable (vehicleID);
            CStreaming::SetModelTxdIsDeletable (vehicleID);
        }
        CVehicle *vehicle = nullptr;
        switch (reinterpret_cast<CVehicleModelInfo *> (
                    CModelInfo::ms_modelInfoPtrs[vehicleID])
                    ->m_nVehicleType)
        {
            case VEHICLE_MTRUCK:
                vehicle = new CMonsterTruck (vehicleID, 1);
                break;
            case VEHICLE_QUAD: vehicle = new CQuadBike (vehicleID, 1); break;
            case VEHICLE_HELI: vehicle = new CHeli (vehicleID, 1); break;
            case VEHICLE_PLANE: vehicle = new CPlane (vehicleID, 1); break;
            case VEHICLE_BIKE:
                vehicle = new CBike (vehicleID, 1);
                reinterpret_cast<CBike *> (vehicle)->m_nDamageFlags |= 0x10;
                break;
            case VEHICLE_BMX:
                vehicle = new CBmx (vehicleID, 1);
                reinterpret_cast<CBmx *> (vehicle)->m_nDamageFlags |= 0x10;
                break;
            case VEHICLE_TRAILER: vehicle = new CTrailer (vehicleID, 1); break;
            case VEHICLE_BOAT:
            case VEHICLE_TRAIN: // Thank you Rockstar, very cool
                vehicle = new CBoat (vehicleID, 1);
                break;
            default: vehicle = new CAutomobile (vehicleID, 1, true); break;
        }
        if (vehicle)
        {
            vehicle->SetPosn (position);
            vehicle->SetOrientation (0.0f, 0.0f, orientation);
            vehicle->m_nStatus   = STATUS_ABANDONED;
            vehicle->m_nDoorLock = CARLOCK_UNLOCKED;
            if (clearSpace)
            {
                CTheScripts::ClearSpaceForMissionEntity (position, vehicle);
            }
            CWorld::Add (vehicle);
            if (vehicle->m_nVehicleClass == VEHICLE_BIKE)
                reinterpret_cast<CBike *> (vehicle)->PlaceOnRoadProperly ();
            else if (vehicle->m_nVehicleClass != VEHICLE_BOAT)
                reinterpret_cast<CAutomobile *> (vehicle)
                    ->PlaceOnRoadProperly ();

            return vehicle;
        }
    }
    return nullptr;
}

void
GameUtil::ClearWeapons (CPed *ped, bool keepParachute)
{
    if (!ped) return;

    // Clear tasks if the ped is currently parachuting so they don't get stuck
    // in a "falling" animation without the parachute
    if (ped->m_pIntelligence->GetUsingParachute ())
        ped->m_pIntelligence->ClearTasks (true, false);

    for (int i = WEAPON_BRASSKNUCKLE; i < WEAPON_FLARE; i++)
    {
        eWeaponType type = static_cast<eWeaponType> (i);
        if (type != WEAPON_PARACHUTE || !keepParachute) ped->ClearWeapon (type);
    }
}

bool
GameUtil::IsCutsceneProcessing ()
{
    return CCutsceneMgr::ms_cutsceneProcessing || CCutsceneMgr::ms_running;
}

bool
GameUtil::IsPlayerSafe ()
{
    CPlayerPed *player = FindPlayerPed ();
    if (!player || !player->CanSetPedState () || !player->IsAlive ())
    {
        return false;
    }

    switch (player->m_nPedState)
    {
        case PEDSTATE_ARRESTED:
        case PEDSTATE_ARREST_PLAYER:
        case PEDSTATE_DEAD:
        case PEDSTATE_DIE:
        case PEDSTATE_DIE_BY_STEALTH: return false;
        default:
        {
        }
    }

    switch (TheCamera.m_PlayerWeaponMode.m_nMode)
    {
        case MODE_HELICANNON_1STPERSON:
        case MODE_CAMERA: return false;
        default:
        {
        }
    }

    CPlayerData *data = player->m_pPlayerData;
    if (!data || !data->m_bCanBeDamaged) return false;

    CPad *pad = player->GetPadFromPlayer ();
    if (!pad) return false;

    if (pad->bPlayerOnInteriorTransition || pad->bPlayerSafe
        || pad->bPlayerSafeForCutscene)
    {
        return false;
    }

    if (GameUtil::IsCutsceneProcessing ())
    {
        return false;
    }

    if (CEntryExitManager::WeAreInInteriorTransition ()) return false;

    return true;
}
