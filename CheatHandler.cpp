#include "CheatHandler.h"

void CheatHandler::HandleCheat(std::string cheat) {
	if (cheat == "give_health_armor_money") {
		Player::GivePlayerHealthArmorMoney();
	}
	else if (cheat == "suicide") {
		Player::KillPlayer();
	}

	else if (cheat == "jetpack") {
		CCheat::JetpackCheat();
	}

	else if (cheat == "fat_player") {
		CCheat::FatCheat();
	}
	else if (cheat == "max_muscle") {
		CCheat::MuscleCheat();
	}
	else if (cheat == "skinny_player") {
		CCheat::SkinnyCheat();
	}
}

TimedEffect* CheatHandler::HandleTimedCheat(std::string cheat, int duration, std::string description) {
	if (cheat == "infinite_ammo") {
		return new TimedAddressCheat(0x969178, duration, description);
	}

	else if (cheat == "never_wanted") {
		return new TimedFunctionCheat(CCheat::NotWantedCheat, 0x969171, duration, description);
	}

	else if (cheat == "always_midnight") {
		return new TimedFunctionCheat(CCheat::MidnightCheat, 0x969167, duration, description);
	}
	else if (cheat == "orange_sky") {
		return new TimedFunctionCheat(CCheat::DuskCheat, 0x969168, duration, description);
	}
	else if (cheat == "faster_clock") {
		return new TimedAddressCheat(0x96913B, duration, description);
	}

	else if (cheat == "pink_traffic") {
		return new TimedAddressCheat(0x969150, duration, description);
	}
	else if (cheat == "black_traffic") {
		return new TimedAddressCheat(0x969151, duration, description);
	}
	else if (cheat == "cheap_cars") {
		return new TimedAddressCheat(0x96915E, duration, description);
	}
	else if (cheat == "expensive_cars") {
		return new TimedAddressCheat(0x96915F, duration, description);
	}
	else if (cheat == "invisible_cars") {
		return new InvisibleVehicles(duration, description);
	}
	else if (cheat == "insane_handling") {
		return new TimedAddressCheat(0x96914C, duration, description);
	}
	else if (cheat == "all_green_lights") {
		return new TimedAddressCheat(0x96914E, duration, description);
	}
	else if (cheat == "cars_on_water") {
		return new TimedAddressCheat(0x969152, duration, description);
	}
	else if (cheat == "boats_fly") {
		return new TimedAddressCheat(0x969153, duration, description);
	}
	else if (cheat == "cars_fly") {
		return new TimedAddressCheat(0x969160, duration, description);
	}
	else if (cheat == "smash_n_boom") {
		return new TimedAddressCheat(0x969164, duration, description);
	}
	else if (cheat == "all_cars_nitro") {
		return new TimedAddressCheat(0x969165, duration, description);
	}
	else if (cheat == "bubble_cars") {
		return new TimedAddressCheat(0x969166, duration, description);
	}
	else if (cheat == "reduced_traffic") {
		return new TimedAddressCheat(0x96917A, duration, description);
	}
	else if (cheat == "all_taxis_nitro") {
		return new TimedAddressCheat(0x96918B, duration, description);
	}

	else if (cheat == "rough_neighbourhood") {
		return new TimedAddressCheat(0x96913E, duration, description);
	}
	else if (cheat == "bounty_on_your_head") {
		return new TimedAddressCheat(0x96913F, duration, description);
	}
	else if (cheat == "elvis_lives") {
		return new TimedFunctionCheat(CCheat::ElvisLivesCheat, 0x969157, duration, description);
	}
	else if (cheat == "village_people") {
		return new TimedFunctionCheat(CCheat::VillagePeopleCheat, 0x969158, duration, description);
	}
	else if (cheat == "only_homies") {
		return new TimedFunctionCheat(CCheat::GangsCheat, 0x96915A, duration, description);
	}
	else if (cheat == "stay_indoors") {
		return new TimedFunctionCheat(CCheat::GangLandCheat, 0x96915B, duration, description);
	}
	else if (cheat == "riot_mode") {
		return new TimedAddressCheat(0x969175, duration, description);
	}
	else if (cheat == "everyone_armed") {
		return new TimedAddressCheat(0x969140, duration, description);
	}
	else if (cheat == "aggressive_drivers") {
		return new TimedAddressCheat(0x96914F, duration, description);
	}
	else if (cheat == "recruit_9mm") {
		return new TimedAddressCheat(0x96917C, duration, description);
	}
	else if (cheat == "recruit_ak47") {
		return new TimedAddressCheat(0x96917D, duration, description);
	}
	else if (cheat == "recruit_rockets") {
		return new TimedAddressCheat(0x96917E, duration, description);
	}
	else if (cheat == "reverse_hooker") {
		return new TimedAddressCheat(0x96918A, duration, description);
	}
	else if (cheat == "beach_party") {
		return new TimedFunctionCheat(CCheat::BeachPartyCheat, 0x969159, duration, description);
	}
	else if (cheat == "ninja_theme") {
		return new TimedFunctionCheat(CCheat::NinjaCheat, 0x96915C, duration, description);
	}
	else if (cheat == "slut_magnet") {
		return new TimedFunctionCheat(CCheat::LoveConquersAllCheat, 0x96915D, duration, description);
	}
	else if (cheat == "funhouse_theme") {
		return new TimedFunctionCheat(CCheat::FunhouseCheat, 0x969176, duration, description);
	}
	else if (cheat == "country_traffic") {
		return new TimedFunctionCheat(CCheat::CountrysideInvasionCheat, 0x96917B, duration, description);
	}

	else if (cheat == "drive_by") {
		return new TimedAddressCheat(0x969179, duration, description);
	}
	else if (cheat == "huge_bunny_hop") {
		return new TimedAddressCheat(0x969161, duration, description);
	}
	else if (cheat == "mega_jump") {
		return new TimedAddressCheat(0x96916C, duration, description);
	}
	else if (cheat == "infinite_health") {
		return new TimedAddressCheat(0x96916D, duration, description);
	}
	else if (cheat == "infinite_oxygen") {
		return new TimedAddressCheat(0x96916E, duration, description);
	}
	else if (cheat == "mega_punch") {
		return new TimedAddressCheat(0x969173, duration, description);
	}

	else if (cheat == "never_hungry") {
		return new TimedAddressCheat(0x969173, duration, description);
	}
	else if (cheat == "lock_respect") {
		return new TimedAddressCheat(0x969173, duration, description);
	}
	else if (cheat == "lock_sex_appeal") {
		return new TimedAddressCheat(0x969173, duration, description);
	}

	return nullptr;
}