#pragma once

#include "util/EffectBase.h"

class PedalToTheMetalEffect : public EffectBase
{
public:
    PedalToTheMetalEffect ();

    void InitializeHooks () override;

    static __int16 __fastcall HookedGetAccelerate (CPad *thisPad);
    static __int16 __fastcall HookedGetBrake (CPad *thisPad);
    static __int16 __fastcall HookedGetHandBrake (CPad *thisPad);
};
