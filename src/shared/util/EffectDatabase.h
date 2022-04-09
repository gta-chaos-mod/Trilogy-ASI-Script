#pragma once

#include <string_view>
#include <vector>

class EffectBase;

class EffectDatabase
{
    std::vector<EffectBase *> effectsList;

    EffectDatabase ()                            = default;
    EffectDatabase (const EffectDatabase &other) = delete;

public:
    static EffectDatabase &
    GetInstance ()
    {
        static EffectDatabase db;
        return db;
    }

    static void
    RegisterEffect (EffectBase *base)
    {
        GetInstance ().effectsList.push_back (base);
    }

    static EffectBase *FindEffectById (std::string_view id);
};
