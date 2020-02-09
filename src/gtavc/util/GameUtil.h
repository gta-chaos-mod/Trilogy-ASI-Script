#pragma once

#include "plugin.h"

#include <filesystem>

#include "util/Config.h"

#include "CCarCtrl.h"
#include "CClock.h"
#include "CFileMgr.h"
#include "CGame.h"

using namespace plugin;

class GameUtil
{
private:
    static bool *extraSplash;
    static char *loadPath;
    static char *savePath;

public:
    static void        SaveToFile (std::string fileName);
    static bool        LoadFromFile (std::string fileName);
    static std::string GetLoadFileName ();

    static void SetVehiclesToRealPhysics ();
};
