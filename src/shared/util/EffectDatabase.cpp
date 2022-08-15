#include "EffectDatabase.h"

#include "util/EffectBase.h"

void
EffectDatabase::RegisterEffect (EffectBase *base)
{
    auto &id         = base->GetMetadata ().id;
    auto &effectsMap = GetInstance ().effectsMap;
    if (effectsMap.contains (id))
    {
#ifdef _DEBUG
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
