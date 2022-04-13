#pragma once

#include <string_view>

class EffectBase;

class EffectDatabase
{
    std::map<std::string, EffectBase *> effectsMap;

    EffectDatabase ()                            = default;
    EffectDatabase (const EffectDatabase &other) = delete;

public:
    static EffectDatabase &
    GetInstance ()
    {
        static EffectDatabase db;
        return db;
    }

    static void RegisterEffect (EffectBase *base);

    static EffectBase *FindEffectById (std::string id);
};
