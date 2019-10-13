#include "CountryThemeCheat.h"

CountryThemeCheat::CountryThemeCheat()
	: TimedFunctionEffect("cheat_country_theme", CountryTheme, 0x96917D)
{
	AddType("theme");
}

void CountryThemeCheat::CountryTheme() {
	CCheat::CountrysideInvasionCheat();

	GameUtil::RebuildPlayer();
}
