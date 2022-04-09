#include "EffectDatabase.h"
#include "EffectBase.h"

EffectBase *
EffectDatabase::FindEffectById (std::string_view id)
{
    for (auto i : GetInstance ().effectsList)
    {
        if (i->GetMetadata().id == id)
            return i;
    }

    return nullptr;
}
