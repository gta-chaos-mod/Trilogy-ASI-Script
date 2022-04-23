#include "util/BoneHelper.h"
#include "util/Config.h"
#include "util/GameUtil.h"

#include <CFileMgr.h>
#include <CTheScripts.h>
#include <CTimer.h>

using namespace plugin;

class GameHandler
{
private:
    static inline int lastMissionsPassed = -1;
    static inline int lastSaved          = 0;
    static inline int lastQuickSave      = 0;

public:
    static void
    Initialise ()
    {
        Config::Init ();
        BoneHelper::Initialise ();
        // GameFixes::Initialise();

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

        patch::RedirectCall (0x5D0D66, Hooked_OpenFile);

        // if (Config::GetOrDefault ("Chaos.AutosaveAfterGangWar", true))
        // {
        //     // Trigger autosave when successfully finishing a gangwar (all 3
        //     // waves, not 2 and starting a sub-mission!)
        //     patch::RedirectCall (0x44690B, Hooked_OnGangWarHoodCaptured);
        // }

        // Make sure to disable effects / delete autosave when starting a new
        // game
        patch::RedirectCall (0x5D18F0, Hooked_CTheScripts_Load);

        // Disable radio volume => -100 if slowmo is active
        patch::Nop (0x4EA044, 8);

        // Fix Reefer w/ Invisible Cars
        patch::Nop (0x6F14DE, 3);
    }

    static void
    ProcessGame ()
    {
        HandleAutoSave ();
        HandleQuickSave ();

        HandleVehicleToRealPhysics ();
    }

private:
    static void
    HandleAutoSave ()
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

                // EffectDatabase::QueueEffect (new AutosaveEffect (
                //                                  missionsPassed),
                //                              true);

                lastSaved = currentTime + 1000;
            }
        }
    }

    // TODO: Bring this into Chaos Mod Complementaries?
    static void
    HandleQuickSave ()
    {
        if (Config::GetOrDefault ("Chaos.QuickSave", false))
        {
            int currentTime = CTimer::m_snTimeInMilliseconds;
            if (KeyPressed (VK_F7) && lastQuickSave < currentTime)
            {
                lastQuickSave = currentTime + 10000;
                // EffectDatabase::QueueEffect (new QuickSaveEffect (), true);
            }
        }
    }

    static void
    HandleVehicleToRealPhysics ()
    {
        if (Config::GetOrDefault ("Fixes.SwitchAllVehiclesToRealPhysics", true))
        {
            GameUtil::SetVehiclesToRealPhysics ();
        }
    }

    static int
    Hooked_OpenFile (const char *path, const char *mode)
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

    static void __fastcall Hooked_CTheScripts_Load ()
    {
        CTheScripts::Load ();

        lastMissionsPassed = -1;
        lastSaved          = 0;
    }

    static void __fastcall Hooked_OnGangWarHoodCaptured ()
    {
        Call<0x446400> (); // _onGWHoodCaptured

        if (!CTheScripts::IsPlayerOnAMission ())
        {
            // EffectDatabase::QueueEffect (new AutosaveEffect (
            //                                  lastMissionsPassed),
            //                              true);
        }
    }
};
