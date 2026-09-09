#pragma once

#include <map>

namespace Globals
{
    inline float                            effectTimerSpeed     = 1.0f;
    inline std::string                      replaceAllTextString = "";
    inline std::map<std::string_view, bool> enabledEffects       = {};
} // namespace Globals