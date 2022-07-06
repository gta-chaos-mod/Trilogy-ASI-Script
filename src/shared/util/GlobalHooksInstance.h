#pragma once

#include "util/EffectCleanupHandler.h"
#include "util/hooks/HookMacros.h"

class GlobalHooksInstance
{
    EffectCleanupHandler cleanupHandler;

public:
    auto
    Get ()
    {
        return this;
    }

    auto &
    GetCleanupHandler ()
    {
        return cleanupHandler;
    }
} globalHooksInstance;