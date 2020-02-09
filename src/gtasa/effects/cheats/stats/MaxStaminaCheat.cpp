#include "MaxStaminaCheat.h"

MaxStaminaCheat::MaxStaminaCheat () : EffectPlaceholder ("cheat_max_stamina") {}

void
MaxStaminaCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CStats::SetStatValue (eStats::STAT_STAMINA, 1000.0f); // Stamina
}
