#include "BeachThemeCheat.h"

BeachThemeCheat::BeachThemeCheat ()
    : TimedFunctionEffect ("cheat_beach_theme", BeachTheme, 0x969159)
{
    AddType ("theme");
}

void
BeachThemeCheat::BeachTheme ()
{
    CCheat::BeachPartyCheat ();

    GameUtil::RebuildPlayer ();
}
