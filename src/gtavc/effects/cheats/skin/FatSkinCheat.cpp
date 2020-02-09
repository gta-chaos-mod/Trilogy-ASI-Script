#include "FatSkinCheat.h"

FatSkinCheat::FatSkinCheat () : EffectPlaceholder ("cheat_fat_skin") {}

void
FatSkinCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    *bodyWidth = 1048911544.0f;
}
