#include "NinjaThemeCheat.h"

NinjaThemeCheat::NinjaThemeCheat()
	: TimedFunctionEffect("cheat_ninja_theme", NinjaTheme, 0x96915C)
{
	AddType("theme");
}

void NinjaThemeCheat::NinjaTheme() {
	CCheat::NinjaCheat();

	GameUtil::RebuildPlayer();
}
