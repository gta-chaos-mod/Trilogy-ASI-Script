#include "SkinnySkinCheat.h"

SkinnySkinCheat::SkinnySkinCheat () : EffectPlaceholder ("cheat_skinny_skin") {}

void
SkinnySkinCheat::Enable ()
{
    EffectPlaceholder::Enable ();

    *bodyWidth = -1097229926.0f;
}
