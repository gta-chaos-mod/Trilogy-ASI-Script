#include "KinkyThemeCheat.h"

KinkyThemeCheat::KinkyThemeCheat()
	: TimedFunctionEffect("cheat_kinky_theme", KinkyTheme, 0x96915D)
{
	AddType("theme");
}

void KinkyThemeCheat::KinkyTheme() {
	CCheat::LoveConquersAllCheat();

	GameUtil::RebuildPlayer();
}
