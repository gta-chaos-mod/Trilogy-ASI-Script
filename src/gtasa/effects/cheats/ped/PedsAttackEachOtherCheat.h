#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include "CCheat.h"

class PedsAttackEachOtherCheat : public EffectBase
{
private:
    bool *pedsAttackEachOtherCheat = reinterpret_cast<bool *> (0x96913E);

public:
    PedsAttackEachOtherCheat ();

    void Enable () override;
    void Disable () override;
};
