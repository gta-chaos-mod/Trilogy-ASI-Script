#include "FunhouseThemeCheat.h"

FunhouseThemeCheat::FunhouseThemeCheat ()
    : TimedFunctionEffect ("cheat_funhouse_theme", FunhouseTheme, 0x969176)
{
    AddType ("theme");
}

void
FunhouseThemeCheat::FunhouseTheme ()
{
    CCheat::FunhouseCheat ();

    GameUtil::RebuildPlayer ();
}
