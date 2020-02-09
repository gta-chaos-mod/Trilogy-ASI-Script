#pragma once

#include "effects/EffectPlaceholder.h"

class SkinnySkinCheat : public EffectPlaceholder
{
private:
    float *bodyWidth = reinterpret_cast<float *> (0x68E058);

public:
    SkinnySkinCheat ();

    void Enable () override;
};
