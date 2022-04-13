#include "EffectDatabase.h"
#include "EffectBase.h"

void
EffectDatabase::RegisterEffect (EffectBase *base)
{
    auto &id         = base->GetMetadata ().id;
    auto &effectsMap = GetInstance ().effectsMap;
    if (effectsMap.contains (id))
    {
// TODO: Log this to a file so we know that an effect tried to register
// with an already existing ID
#ifndef _NDEBUG
        MessageBox (NULL, id.c_str (), "Trying to register duplicate effect",
                    MB_ICONHAND);
#endif
        return;
    }
    GetInstance ().effectsMap[id] = base;
}

EffectBase *
EffectDatabase::FindEffectById (std::string id)
{
    auto &effectsMap = GetInstance ().effectsMap;
    return effectsMap.contains (id) ? effectsMap[id] : nullptr;
}
