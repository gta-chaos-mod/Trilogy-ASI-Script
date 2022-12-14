#pragma once

#include <filesystem>

#define CONFIG(_setting, _default) Config::GetOrDefault (_setting, _default)
#define CONFIG_CC_ENABLED CONFIG ("CrowdControl.Enabled", false)

class Config
{
    static inline std::shared_ptr<cpptoml::table> config;
#ifdef GTASA
    static inline std::string configContent
        = R"(########################################################
# Chaos Mod
#######################################################

#######################################################
# Chaos Settings
[Chaos]

# Always count down effects, no matter if it's in a cutscene or the player is currently
# in a specific state (e.g. getting arrested, getting wasted, etc.)
# Default: false
AlwaysCountDownEffects = false

# Autosave after completing a mission
# Default: true
AutosaveAfterMissionPassed = true

# Additionally save the Autosave into Slot 8
# Default: false
SaveToSlot8 = false

# Load the autosave on game load (Can be skipped by holding Left CTRL)
# Default: true
LoadAutosaveOnGameLoad = true

# Whether or not the game should delete the autosave when starting a new game
# This is so when "Reload Autosave" is coming up it won't "wrong-wrap" you to that
# Useful for speedruns, mainly, so they don't get disqualified.
# Default: true
DeleteAutosaveOnNewGame = true

# Whether or not the game should play a simple sound when an effect get's enabled
# Default: true
PlayEffectSound = true

# Whether or not to clear all active effects when a new game is started (Useful for speedruns)
# Default: true
ClearEffectsOnNewGame = true

# Allow Quicksaves at any time by pressing F7
# This is doable every 10 seconds. It will also not save during missions.
# Will be saved to Slot 8.
# Default: false
QuickSave = false

# Switch all vehicles to real game physics every tick
# This will prevent vehicles on highways or other places to go absurdly fast whilst they're on their AI path
# Default: true
SwitchAllVehiclesToRealPhysics = true

#######################################################

#######################################################
# Effect-Specific Settings
[Effects]

# Vehicle One Hit K.O. - Explode Vehicles
# When set to true vehicles will explode the moment they take damage.
# When set to false they will just start burning.
# Default: false
VehicleOneHitKO_ExplodeVehicles = false

#######################################################

#######################################################
# Drawing Settings
[Drawing]

# Whether or not to enable the drawing functionality in the first place
# Default: true
Enabled = true

# Max. number of recent effects
# Min: 3
# Max: 8
# Default: 6
NumRecentEffects = 6

# Whether to draw the effects on the left or right side of the screen
# Default: true
DrawOnLeftSide = true

# Whether to lower the opacity of effect texts when a menu (e.g. tuner or food) is open
# (Only works when DrawOnLeftSide is true)
# Default: true
LowerOpacityWhenMenuOpen = true

# Draw the top bar showing the remaining time until the next effect happens
# Default: true
DrawRemainingTimeBar = true

# Draw the currently active / last effects
# Default: true
DrawActiveEffects = true

# Draw the remaining time of effects as circles instead of a "minute:second" text
# If you don't see circles next to effects, try turning this option off.
# Default: true
DrawCircles = true

# Draw voting for Twitch integration
# Default: true
DrawVoting = true

# Will display the bar and effect circles in rainbow colors
# Default: true
RainbowColors = true

#######################################################

#######################################################
# Crowd Control Settings
[CrowdControl]

# Whether Crowd Control is enabled
# WARNING: THIS HAS TO BE ENABLED WHEN PLAYING WITH CROWD CONTROL!
# Default: false
Enabled = false
#######################################################)";
#else
    static inline std::string configContent = "";
#endif

public:
    static void
    Init ()
    {
        const std::string pluginFilename = std::string (PLUGIN_FILENAME);
        const std::string configFilename
            = pluginFilename.substr (0, pluginFilename.size () - 4) + ".toml";
        const std::filesystem::path configPath
            = PLUGIN_PATH ((char *) configFilename.c_str ());

        std::filesystem::create_directories (configPath.parent_path ());

        if (!std::filesystem::exists (configPath))
        {
            // Write default configuration file
            std::ofstream ConfigFile (configPath);

            ConfigFile << configContent;

            ConfigFile.close ();
        }

        if (std::filesystem::exists (configPath))
        {
            config = cpptoml::parse_file (configPath.string ());
        }
    }

    template <class T>
    static T
    GetOrDefault (std::string key, T defaultValue)
    {
        if (!config) return defaultValue;

        return config->get_qualified_as<T> (key).value_or (defaultValue);
    }
};