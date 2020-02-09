#include "FatPlayerCheat.h"

FatPlayerCheat::FatPlayerCheat () : EffectPlaceholder ("cheat_fat_player") {}

void
FatPlayerCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    CStats::SetStatValue (eStats::STAT_FAT, 1000.0f);

    GameUtil::RebuildPlayer ();
}
