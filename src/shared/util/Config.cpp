#include "Config.h"

#include "util/FileUpdateListener.h"

#include <efsw/efsw.hpp>

void
Config::Init ()
{
    ReloadConfig ();

    if (!fileWatcherInitialized)
    {
        const std::filesystem::path configPath = GetConfigPath ();

        efsw::FileWatcher  *fileWatcher = new efsw::FileWatcher ();
        FileUpdateListener *listener    = new FileUpdateListener ();

        efsw::WatchID watchID
            = fileWatcher->addWatch (GetConfigPath ().parent_path ().string (),
                                     listener, false);

        fileWatcher->watch ();

        fileWatcherInitialized = true;
    }
}

void
Config::ReloadConfig ()
{
    const std::filesystem::path configPath = GetConfigPath ();

    if (!std::filesystem::exists (configPath))
    {
        // Write default configuration file
        std::ofstream ConfigFile (configPath);

        ConfigFile << configContent;

        ConfigFile.close ();
    }

    if (std::filesystem::exists (configPath))
    {
        try
        {
            config = cpptoml::parse_file (configPath.string ());
        }
        catch (cpptoml::parse_exception &parseException)
        {
            MessageBox (NULL, parseException.what (), "Config Error", NULL);
        }
    }
}