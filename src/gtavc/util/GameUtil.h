#pragma once

#include <CMenuManager.h>

class GameUtil
{
public:
    static bool
    IsCutsceneProcessing ()
    {
        return false;
    }

    static bool
    IsPlayerSafe ()
    {
        return true;
    }
};