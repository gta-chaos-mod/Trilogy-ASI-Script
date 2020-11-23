#include "GameHandler.h"

int GameHandler::lastMissionsPassed = -1;
int GameHandler::lastSaved          = 0;
int GameHandler::lastPressed        = 0;

void
GameHandler::Initialise ()
{
    Config::Init ();
    GameFixes::Initialise ();

    // Check if the mod is already loaded / installed once
    if (injector::ReadMemory<bool> (0xBED000, true))
    {
        MessageBox (NULL,
                    "Chaos Mod is already installed - make sure it isn't "
                    "installed multiple times!",
                    "Chaos Mod Error", 0);
        exit (0);
        return;
    }

    // Write to unused memory space so other mods know that the Chaos mod is
    // installed
    injector::WriteMemory<bool> (0xBED000, true, true);

    patch::RedirectCall (0x5D0D66, HookedOpenFile);

    if (Config::GetOrDefault ("Fixes.DisableReplays", false))
    {
        // Disable Replays
        patch::Nop (0x53C090, 5);
    }

    if (Config::GetOrDefault ("Fixes.DisableInteriorMusic", true))
    {
        // Disable Interior Music
        patch::Nop (0x508450, 6);
        patch::Nop (0x508817, 6);
    }

    if (Config::GetOrDefault ("Fixes.RemoveFrameDelay", false))
    {
        // Fix frame delay so the game runs at proper 30 FPS and not 30 - 5 /
        // "25 FPS"
        injector::WriteMemory<byte> (0x53E94C, 0, true);
    }

    if (Config::GetOrDefault ("Chaos.AutosaveAfterGangWar", true))
    {
        // Trigger autosave when successfully finishing a gangwar (all 3 waves,
        // not 2 and starting a sub-mission!)
        patch::RedirectCall (0x44690B, HookedOnGangWarHoodCaptured);
    }

    // Make sure to disable effects / delete autosave when starting a new game
    patch::RedirectCall (0x5D18F0, HookedGenericLoadTheScriptsLoad);

    // Disable radio volume => -100 if slowmo is active
    patch::Nop (0x4EA044, 8);

    // Fix Reefer w/ Invisible Cars
    patch::Nop (0x6F14DE, 3);

    // Overwrite gang territories check for the finale of the game
    patch::RedirectCall (0x4759B0, HookedFinaleGetGangTerritories);

    // Overwrite "GetStatValue" OpCode for mission checks
    // Right now it can help with Amphibious Assault, Black Project and Green
    // Goo
    patch::RedirectCall (0x49444E, HookedOpCodeGetStatValue);
}

void
GameHandler::ProcessGame ()
{
    // Make sure the player never cheated
    CCheat::m_bHasPlayerCheated = false;

    HandleAutosave ();

    HandleVehicleRadio ();
    HandleVehicleToRealPhysics ();

    HandleNoWeaponRemoval ();
    HandleNoCheatInput ();
    HandleSkipWastedBustedHelpMessages ();
}

int
GameHandler::HookedOpenFile (const char *path, const char *mode)
{
    std::string s_path (path), save_path = "GTASAsf9.b";

    size_t start_pos = s_path.find (save_path);
    if (start_pos != std::string::npos)
    {
        s_path.replace (start_pos, save_path.length (),
                        GameUtil::GetLoadFileName ().c_str ());
    }

    return CFileMgr::OpenFile (s_path.c_str (), mode);
}

void
GameHandler::HandleAutosave ()
{
    if (Config::GetOrDefault ("Chaos.AutosaveAfterMissionPassed", true))
    {
        int missionsPassed = GameUtil::GetRealMissionsPassed ();
        int currentTime    = CTimer::m_snTimeInMilliseconds;

        if (lastMissionsPassed == -1)
        {
            lastMissionsPassed = missionsPassed;
        }
        else if (lastMissionsPassed > missionsPassed)
        {
            lastMissionsPassed = missionsPassed;
        }

        if (missionsPassed > lastMissionsPassed && lastSaved < currentTime
            && !CTheScripts::IsPlayerOnAMission ())
        {
            lastMissionsPassed = missionsPassed;

            EffectDatabase::QueueEffect (new AutosaveEffect (missionsPassed),
                                         true);

            lastSaved = currentTime + 1000;
        }
    }
}

void
GameHandler::HandleVehicleRadio ()
{
    if (Config::GetOrDefault ("Fixes.AllowRadioInEveryVehicle", false))
    {
        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle)
        {
            vehicle->m_vehicleAudio.m_settings.m_nRadioType
                = eRadioType::RADIO_CIVILIAN;
        }
    }
}

void
GameHandler::HandleVehicleToRealPhysics ()
{
    if (Config::GetOrDefault ("Fixes.SwitchAllVehiclesToRealPhysics", true))
    {
        GameUtil::SetVehiclesToRealPhysics ();
    }
}

void
GameHandler::HandleNoWeaponRemoval ()
{
    if (Config::GetOrDefault ("Chaos.PreventLosingWeapons", false))
    {
        injector::WriteMemory<byte> (0x8A5E48, 0); // Lose Stuff After Wasted
        injector::WriteMemory<byte> (0x8A5E49, 0); // Lose Stuff After Busted
    }
}

void
GameHandler::HandleNoCheatInput ()
{
    if (Config::GetOrDefault ("Fixes.DisableCheatInput", false)
        && !KeyPressed (VK_SHIFT))
    {
        CCheat::m_CheatString[0] = 0;
    }
}

void
GameHandler::HandleSkipWastedBustedHelpMessages ()
{
    if (Config::GetOrDefault ("Chaos.SkipWastedBustedMessages", false))
    {
        CPickups::RemovePickUp (CTheScripts::ScriptSpace[669]);
        CPickups::RemovePickUp (CTheScripts::ScriptSpace[670]);
        CPickups::RemovePickUp (CTheScripts::ScriptSpace[671]);
    }
}

void __fastcall GameHandler::HookedGenericLoadTheScriptsLoad ()
{
    CTheScripts::Load ();

    lastMissionsPassed = -1;
    lastSaved          = 0;
    lastPressed        = 0;
}

void __fastcall GameHandler::HookedOnGangWarHoodCaptured ()
{
    Call<0x446400> (); // _onGWHoodCaptured

    if (!CTheScripts::IsPlayerOnAMission ())
    {
        EffectDatabase::QueueEffect (new AutosaveEffect (lastMissionsPassed),
                                     true);
    }
}

__int16 __fastcall GameHandler::HookedFinaleGetGangTerritories (
    CRunningScript *thisScript, void *edx, __int16 count)
{
    if (Config::GetOrDefault ("Chaos.SkipGangTerritoriesCheck", false))
    {
        CTheScripts::ScriptParams[0].iParam
            = std::max (35, CTheScripts::ScriptParams[0].iParam);
    }
    return CallMethodAndReturn<__int16, 0x464370, CRunningScript *> (
        thisScript,
        count); // CRunningScript::StoreParameters
}

double
GameHandler::HookedOpCodeGetStatValue (int statid)
{
    double stat
        = CallAndReturn<double, 0x558E40> (statid); // CStats::GetStatValue
    if (statid == eStats::STAT_FAT
        && Config::GetOrDefault ("Chaos.SkipFatCheck", false))
    {
        stat = std::min (stat, 600.0);
    }
    else if (statid == eStats::STAT_LUNG_CAPACITY
             && Config::GetOrDefault ("Chaos.SkipLungCapacityCheck", false))
    {
        stat = std::max (51.0, stat);
    }
    return stat;
}