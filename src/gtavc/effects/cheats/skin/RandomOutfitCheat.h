#pragma once

#include "effects/EffectPlaceholder.h"

class RandomOutfitCheat : public EffectPlaceholder
{
public:
    RandomOutfitCheat ();

    void InitializeHooks () override;

    void Enable () override;

private:
    static void HookedCHudSetHelpMessage (int a1, char a2, char a3);
};
