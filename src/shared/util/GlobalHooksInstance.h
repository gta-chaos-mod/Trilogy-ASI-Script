#pragma once

#include "util/EffectCleanupHandler.h"
#include "util/hooks/HookMacros.h"

class GlobalHooksInstance
{
    EffectCleanupHandler cleanupHandler;

public:
    static auto
    Get ()
    {
        static GlobalHooksInstance instance;
        return &instance;
    }

    auto &
    GetCleanupHandler ()
    {
        return cleanupHandler;
    }
};