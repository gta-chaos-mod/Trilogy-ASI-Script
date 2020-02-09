#pragma once

#include "util/EffectBase.h"

class EffectPlaceholder : public EffectBase
{
public:
    EffectPlaceholder (std::string id);

    void Enable () override;
};
