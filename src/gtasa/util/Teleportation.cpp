#include "Teleportation.h"

bool
Teleportation::CanTeleport ()
{
    CPlayerPed *player = FindPlayerPed ();
    if (!player || !player->CanSetPedState () || !player->IsAlive ())
    {
        return false;
    }

    switch (TheCamera.m_PlayerWeaponMode.m_nMode)
    {
    case eCamMode::MODE_HELICANNON_1STPERSON:
    case eCamMode::MODE_CAMERA: return false;
    default:
    {
    }
    }

    if (!player->IsPedInControl ())
    {
        return false;
    }

    CPlayerData *data = player->m_pPlayerData;
    if (!data || !data->m_bCanBeDamaged)
    {
        return false;
    }

    CPad *pad = player->GetPadFromPlayer ();
    if (!pad)
    {
        return false;
    }

    if (pad->bPlayerOnInteriorTransition || pad->bPlayerSafe
        || pad->bPlayerSafeForCutscene)
    {
        return false;
    }

    if (CCutsceneMgr::ms_cutsceneProcessing || CCutsceneMgr::ms_running)
    {
        return false;
    }

    if (CEntryExitManager::WeAreInInteriorTransition ())
    {
        return false;
    }

    CVehicle *vehicle = FindPlayerVehicle (-1, false);
    if (vehicle)
    {
        if (!vehicle->IsDriver (player))
        {
            return false;
        }

        if (Command<eScriptCommands::COMMAND_IS_RECORDING_GOING_ON_FOR_CAR> (
                vehicle))
        {
            return false;
        }
    }

    return true;
}

void
Teleportation::Teleport (CVector destination, int interior)
{
    CPhysical *entity = (CPhysical *) FindPlayerEntity (-1);
    if (entity && !CCutsceneMgr::ms_running)
    {
        CVector moveSpeed = entity->m_vecMoveSpeed;
        CVector turnSpeed = entity->m_vecTurnSpeed;

        entity->Teleport (destination, false);

        CGame::currArea     = interior;
        entity->m_nAreaCode = interior;

        CEntryExitManager::ms_entryExitStackPosn = interior;
        CPopulation::bInPoliceStation            = false;
        CStreaming::RemoveBuildingsNotInArea (interior);

        CWorld::Remove (entity);
        CWorld::Add (entity);

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            player->GetPadFromPlayer ()->bDisablePlayerEnterCar = false;
            player->m_nAreaCode                                 = interior;
            if (interior == 0)
            {
                player->m_pEnex = 0;
            }

            CWorld::Remove (player);
            CWorld::Add (player);
        }

        entity->m_vecMoveSpeed = moveSpeed;
        entity->m_vecTurnSpeed = turnSpeed;

        CStreaming::StreamZoneModels (&destination);
        CTimeCycle::StopExtraColour (false);

        CStreaming::LoadScene (&destination);
        CStreaming::LoadAllRequestedModels (false);
    }
}

void
Teleportation::TeleportOutOfMission (std::string missionName)
{
    if (missionName == "SWEET1B")
    { // Cleaning The Hood
        CPed *player;
        Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR> (0, &player);
        if (player
            && Command<eScriptCommands::COMMAND_IS_CHAR_IN_AREA_3D> (
                player, 303.0f, 1112.0f, 1081.0f, 337.0f, 1133.0f, 1087.0f, 0))
        {
            Teleportation::Teleport (CVector (2172.0f, -1677.0f, 16.0f));
        }
    }
    else if (missionName == "CRASH1")
    { // Burning Desire
        CPed *player;
        Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR> (0, &player);
        if (player
            && Command<eScriptCommands::COMMAND_IS_CHAR_IN_AREA_3D> (
                player, 2356.0f, -1191.0f, 1025.0f, 2316.0f, -1169.0f, 1039.0f,
                0))
        {
            Teleportation::Teleport (CVector (2351.0f, -1160.0f, 28.0f));
        }
    }
    else if (missionName == "MUSIC2")
    { // Madd Dogg's Rhymes
        CPed *player;
        Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR> (0, &player);
        if (player
            && Command<eScriptCommands::COMMAND_IS_CHAR_IN_AREA_3D> (
                player, 1304.0f, -841.0f, 1082.0f, 1219.0f, -748.0f, 1102.0f,
                0))
        {
            Teleportation::Teleport (CVector (1300.0f, -804.0f, 85.0f));
        }
    }
    else if (missionName == "CAT2")
    { // Small Town Bank
        CPed *player;
        Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR> (0, &player);
        if (player
            && Command<eScriptCommands::COMMAND_IS_CHAR_IN_AREA_2D> (
                player, 2302.0f, -19.0f, 2321.0f, 2.0f, 0))
        {
            Teleportation::Teleport (CVector (2301.0f, -16.0f, 27.4f));
        }
    }
    else if (missionName == "GARAG1")
    { // Wear Flowers In Your Hair
        CPed *player;
        Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR> (0, &player);
        if (player)
        {
            Teleportation::Teleport (CVector (-2029.0f, 174.0f, 30.0f));
        }
    }
    else if (missionName == "CASINO3")
    { // You've Had Your Chips
        CPed *player;
        Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR> (0, &player);
        if (player
            && Command<eScriptCommands::COMMAND_IS_CHAR_IN_AREA_3D> (
                player, 1054.0f, 2074.0f, 8.0f, 1097.0f, 2148.0f, 22.0f, 0))
        {
            Teleportation::Teleport (CVector (1051.0f, 2087.0f, 12.0f));
        }
    }
    else if (missionName == "MAF4")
    { // Black Project
        CPed *player;
        Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR> (0, &player);
        if (player
            && Command<eScriptCommands::COMMAND_IS_CHAR_IN_AREA_3D> (
                player, 182.0f, 1927.0f, 15.0f, 335.0f, 1767.0f, -42.0f, 0))
        {
            Teleportation::Teleport (CVector (88.0f, 1921.0f, 19.0f));
        }
    }
    else if (missionName == "CASIN10")
    { // Saint Mark's Bistro
        CPed *player;
        Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR> (0, &player);
        if (player
            && Command<eScriptCommands::COMMAND_IS_CHAR_IN_AREA_3D> (
                player, -850.0f, 481.0f, 1349.0f, -777.0f, 543.0f, 1385.0f, 0))
        {
            Teleportation::Teleport (CVector (1704.0f, 1447.0f, 12.0f));
        }
    }
    else if (missionName == "MANSIO1")
    { // A Home In The Hills
        CPed *player;
        Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR> (0, &player);
        if (player && player->GetPosition ().z > 300.0f)
        {
            Teleportation::Teleport (CVector (1255.0f, -779.0f, 94.0f));
        }
    }
    else if (missionName == "FINALEB")
    { // End Of The Line (Part 2)
        CGame::currArea = 0;

        CEntryExitManager::ms_entryExitStackPosn = 0;
        CPopulation::bInPoliceStation            = false;
        CStreaming::RemoveBuildingsNotInArea (0);

        CPed *player = FindPlayerPed ();
        if (player)
        {
            player->m_nAreaCode = 0;
            player->m_pEnex     = 0;
        }

        CStreaming::Update ();
        // plugin::Call<0x40A560> (); // CStreaming::StreamZoneModels
        CTimeCycle::StopExtraColour (false);
    }
}
