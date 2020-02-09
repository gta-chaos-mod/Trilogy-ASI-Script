#include "Config.h"

std::shared_ptr<cpptoml::table> Config::config;

void
Config::Init ()
{
    const std::filesystem::path config_path (
        GAME_PATH ("/chaos_mod/config.toml"));

    std::filesystem::create_directories (config_path.parent_path ());

    if (std::filesystem::exists (config_path))
    {
        config = cpptoml::parse_file (config_path.string ());
    }
}
