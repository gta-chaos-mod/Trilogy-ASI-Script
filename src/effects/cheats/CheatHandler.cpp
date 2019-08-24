// Copyright (c) 2019 Lordmau5
#include "CheatHandler.h"

TimedEffect* CheatHandler::HandleCheat(std::string cheat, int duration, std::string description) {
	// *** One-Time Cheats ***

	if (cheat == "weapon_set_1") {
		return new FunctionEffect(CCheat::WeaponCheat1, duration, description);
	}
	else if (cheat == "weapon_set_2") {
		return new FunctionEffect(CCheat::WeaponCheat2, duration, description);
	}
	else if (cheat == "weapon_set_3") {
		return new FunctionEffect(CCheat::WeaponCheat3, duration, description);
	}
	else if (cheat == "give_health_armor_money") {
		return new FunctionEffect(Player::GivePlayerHealthArmorMoney, duration, description);
	}
	else if (cheat == "suicide") {
		return new FunctionEffect(Player::KillPlayer, duration, description);
	}

	else if (cheat == "wanted_plus_two") {
		return new FunctionEffect(Wanted::IncreaseWantedLevel, duration, description, "wanted");
	}
	else if (cheat == "wanted_clear") {
		return new FunctionEffect(Wanted::ClearWantedLevel, duration, description, "wanted");
	}
	else if (cheat == "wanted_six_stars") {
		return new FunctionEffect(Wanted::SixWantedStars, duration, description, "wanted");
	}

	else if (cheat == "jetpack") {
		return new FunctionEffect(CCheat::JetpackCheat, duration, description);
	}
	else if (cheat == "parachute") {
		return new FunctionEffect(CCheat::ParachuteCheat, duration, description);
	}

	else if (cheat == "blow_up_all_cars") {
		return new FunctionEffect(Vehicle::BlowUpAllCars, duration, description);
	}

	else if (cheat == "fat_player") {
		return new FunctionEffect(CCheat::FatCheat, duration, description);
	}
	else if (cheat == "max_muscle") {
		return new FunctionEffect(CCheat::MuscleCheat, duration, description);
	}
	else if (cheat == "skinny_player") {
		return new FunctionEffect(CCheat::SkinnyCheat, duration, description);
	}

	// *** End of One-Time Cheats ***

	// *** Timed Cheats ***

	else if (cheat == "infinite_ammo") {
		return new TimedAddressCheat(0x969178, duration, description);
	}

	else if (cheat == "never_wanted") {
		return new TimedFunctionCheat(CCheat::NotWantedCheat, 0x969171, duration, description, "wanted");
	}

	else if (cheat == "always_midnight") {
		return new TimedFunctionCheat(CCheat::MidnightCheat, 0x969167, duration, description, "timecycle");
	}
	else if (cheat == "orange_sky") {
		return new TimedFunctionCheat(CCheat::DuskCheat, 0x969168, duration, description, "timecycle");
	}
	else if (cheat == "faster_clock") {
		return new TimedAddressCheat(0x96913B, duration, description, "timecycle");
	}

	else if (cheat == "pink_traffic") {
		return new TimedFunctionCheat(CCheat::PinkCarsCheat, 0x969150, duration, description, "traffic_color");
	}
	else if (cheat == "black_traffic") {
		return new TimedFunctionCheat(CCheat::BlackCarsCheat, 0x969151, duration, description, "traffic_color");
	}
	else if (cheat == "cheap_cars") {
		return new TimedFunctionCheat(CCheat::AllCarsAreShitCheat, 0x96915E, duration, description, "vehicle_rarity");
	}
	else if (cheat == "expensive_cars") {
		return new TimedFunctionCheat(CCheat::AllCarsAreGreatCheat, 0x96915F, duration, description, "vehicle_rarity");
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
		return new SmashNBoom(duration, description);
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
		return new PedsAttackOther(duration, description);
	}
	else if (cheat == "bounty_on_your_head") {
		return new TimedFunctionCheat(CCheat::EverybodyAttacksPlayerCheat, 0x96913F, duration, description);
	}
	else if (cheat == "elvis_lives") {
		return new TimedFunctionCheat(CCheat::ElvisLivesCheat, 0x969157, duration, description, "gang_members");
	}
	else if (cheat == "village_people") {
		return new TimedFunctionCheat(CCheat::VillagePeopleCheat, 0x969158, duration, description);
	}
	else if (cheat == "only_homies") {
		return new TimedFunctionCheat(CCheat::GangsCheat, 0x96915A, duration, description, "gang_members");
	}
	else if (cheat == "stay_indoors") {
		return new TimedFunctionCheat(CCheat::GangLandCheat, 0x96915B, duration, description, "gang_members");
	}
	else if (cheat == "riot_mode") {
		return new TimedFunctionCheat(CCheat::RiotCheat, 0x969175, duration, description);
	}
	else if (cheat == "everyone_armed") {
		return new TimedAddressCheat(0x969140, duration, description);
	}
	else if (cheat == "aggressive_drivers") {
		return new TimedAddressCheat(0x96914F, duration, description);
	}
	else if (cheat == "recruit_9mm") {
		return new TimedAddressCheat(0x96917C, duration, description, "npc_recruit");
	}
	else if (cheat == "recruit_ak47") {
		return new TimedAddressCheat(0x96917D, duration, description, "npc_recruit");
	}
	else if (cheat == "recruit_rockets") {
		return new TimedAddressCheat(0x96917E, duration, description, "npc_recruit");
	}
	else if (cheat == "reverse_hooker") {
		return new TimedAddressCheat(0x96918A, duration, description);
	}
	else if (cheat == "beach_party") {
		return new TimedFunctionCheat(CCheat::BeachPartyCheat, 0x969159, duration, description, "themes");
	}
	else if (cheat == "ninja_theme") {
		return new TimedFunctionCheat(CCheat::NinjaCheat, 0x96915C, duration, description, "themes");
	}
	else if (cheat == "kinky_theme") {
		return new TimedFunctionCheat(CCheat::LoveConquersAllCheat, 0x96915D, duration, description, "themes");
	}
	else if (cheat == "funhouse_theme") {
		return new TimedFunctionCheat(CCheat::FunhouseCheat, 0x969176, duration, description, "themes");
	}
	else if (cheat == "country_traffic") {
		return new TimedFunctionCheat(CCheat::CountrysideInvasionCheat, 0x96917B, duration, description, "themes");
	}

	else if (cheat == "drive_by") {
		return new TimedFunctionCheat(CCheat::DrivebyCheat, 0x969179, duration, description);
	}
	else if (cheat == "huge_bunny_hop") {
		return new TimedAddressCheat(0x969161, duration, description);
	}
	else if (cheat == "mega_jump") {
		return new TimedAddressCheat(0x96916C, duration, description);
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
