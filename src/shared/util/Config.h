#pragma once

#include <filesystem>

class Config
{
private:
    inline static std::shared_ptr<cpptoml::table> config;
#ifdef GTASA
    inline static std::string configContent
        = R"(########################################################
# Chaos Mod
#######################################################

#######################################################
# Chaos Settings
[Chaos]

# Autosave after completing a mission
# Default: true
AutosaveAfterMissionPassed = true

# Additionally save the Autosave into Slot 8
# Default: false
SaveToSlot8 = false

# Load the autosave on game load (Can be skipped by holding Left CTRL)
# Default: true
LoadAutosaveOnGameLoad = true

# Autosave after successfully finishing a gangwar
# Default: true
AutosaveAfterGangWar = true

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

#######################################################

#######################################################
# Drawing Settings
[Drawing]

# Whether or not to enable the drawing functionality in the first place
# Default: true
Enabled = true

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

#######################################################

#######################################################
# Crowd Control Settings
[CrowdControl]

# Whether or not to enable the Crowd Control mode
# WARNING: THIS IS MANDATORY TO BE ENABLED WHEN PLAYING WITH CROWD CONTROL!
# Default: false
Enabled = false

#######################################################)";
#else
    inline static std::string configContent = "";
#endif

public:
    static void
    Init ()
    {
        const std::string pluginFilename = std::string (PLUGIN_FILENAME);
        const std::string configFilename
            = "/" + pluginFilename.substr (0, pluginFilename.size () - 4)
              + ".toml";
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
        if (!config)
        {
            return defaultValue;
        }

        return config->get_qualified_as<T> (key).value_or (defaultValue);
    }
};