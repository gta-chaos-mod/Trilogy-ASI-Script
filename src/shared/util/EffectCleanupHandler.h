#pragma once

#include <functional>
#include <vector>

class EffectCleanupHandler
{
    std::vector<std::function<void ()>> cleanupFunctions;

public:
    void
    AddFunction (std::function<void ()> function)
    {
        cleanupFunctions.push_back (function);
    }

    void
    DoCleanup ()
    {
        for (const auto &i : cleanupFunctions)
            i ();

        cleanupFunctions.clear ();
    }
};
