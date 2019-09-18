// Copyright (c) 2019 Lordmau5
#include "CheatHandler.h"

TimedEffect* CheatHandler::HandleCheat(const std::string& name, int duration, const std::string& description) {
	// *** One-Time Cheats ***

	TimedEffect* effect = nullptr;

	if (name == "weapon_set_1") {
		effect = new FunctionEffect(CCheat::WeaponCheat1, duration, description);
	}
	else if (name == "weapon_set_2") {
		effect = new FunctionEffect(CCheat::WeaponCheat2, duration, description);
	}
	else if (name == "weapon_set_3") {
		effect = new FunctionEffect(CCheat::WeaponCheat3, duration, description);
	}
	else if (name == "weapon_set_4") {
		effect = new FunctionEffect(Player::WeaponSet4, duration, description);
	}
	else if (name == "give_health_armor_money") {
		effect = new FunctionEffect(Player::GivePlayerHealthArmorMoney, duration, description);
	}
	else if (name == "suicide") {
		effect = new FunctionEffect(Player::KillPlayer, duration, description);
	}

	else if (name == "wanted_plus_two") {
		effect = new FunctionEffect(Wanted::IncreaseWantedLevel, duration, description, "wanted");
	}
	else if (name == "wanted_clear") {
		effect = new FunctionEffect(Wanted::ClearWantedLevel, duration, description, "wanted");
	}
	else if (name == "wanted_six_stars") {
		effect = new FunctionEffect(Wanted::SixWantedStars, duration, description, "wanted");
	}

	else if (name == "jetpack") {
		effect = new FunctionEffect(CCheat::JetpackCheat, duration, description);
	}
	else if (name == "parachute") {
		effect = new FunctionEffect(CCheat::ParachuteCheat, duration, description);
	}

	else if (name == "blow_up_all_cars") {
		effect = new FunctionEffect(Vehicle::BlowUpAllCars, duration, description);
	}

	else if (name == "fat_player") {
		effect = new FunctionEffect(Player::MakeFat, duration, description);
	}
	else if (name == "max_muscle") {
		effect = new FunctionEffect(Player::MakeMuscle, duration, description);
	}
	else if (name == "skinny_player") {
		effect = new FunctionEffect(Player::MakeSkinny, duration, description);
	}

	// *** End of One-Time Cheats ***

	// *** Timed Cheats ***

	else if (name == "infinite_ammo") {
		effect = new TimedAddressCheat(0x969178, duration, description);
	}

	else if (name == "never_wanted") {
		effect = new TimedFunctionCheat(CCheat::NotWantedCheat, 0x969171, duration, description, "wanted");
	}

	else if (name == "always_midnight") {
		effect = new TimedFunctionCheat(CCheat::MidnightCheat, 0x969167, duration, description, "timecycle");
	}
	else if (name == "orange_sky") {
		effect = new TimedFunctionCheat(CCheat::DuskCheat, 0x969168, duration, description, "timecycle");
	}
	else if (name == "faster_clock") {
		effect = new TimedAddressCheat(0x96913B, duration, description, "timecycle");
	}

	else if (name == "pink_traffic") {
		effect = new TimedFunctionCheat(CCheat::PinkCarsCheat, 0x969150, duration, description, "traffic_color");
	}
	else if (name == "black_traffic") {
		effect = new TimedFunctionCheat(CCheat::BlackCarsCheat, 0x969151, duration, description, "traffic_color");
	}
	else if (name == "cheap_cars") {
		effect = new TimedFunctionCheat(CCheat::AllCarsAreShitCheat, 0x96915E, duration, description, "vehicle_rarity");
	}
	else if (name == "expensive_cars") {
		effect = new TimedFunctionCheat(CCheat::AllCarsAreGreatCheat, 0x96915F, duration, description, "vehicle_rarity");
	}
	else if (name == "insane_handling") {
		effect = new TimedAddressCheat(0x96914C, duration, description);
	}
	else if (name == "all_green_lights") {
		effect = new TimedAddressCheat(0x96914E, duration, description);
	}
	else if (name == "cars_on_water") {
		effect = new TimedAddressCheat(0x969152, duration, description);
	}
	else if (name == "boats_fly") {
		effect = new TimedAddressCheat(0x969153, duration, description);
	}
	else if (name == "cars_fly") {
		effect = new TimedAddressCheat(0x969160, duration, description);
	}
	else if (name == "smash_n_boom") {
		effect = new SmashNBoom(duration, description);
	}
	else if (name == "all_cars_nitro") {
		effect = new TimedAddressCheat(0x969165, duration, description);
	}
	else if (name == "bubble_cars") {
		effect = new TimedAddressCheat(0x969166, duration, description);
	}
	else if (name == "reduced_traffic") {
		effect = new TimedAddressCheat(0x96917A, duration, description);
	}
	else if (name == "all_taxis_nitro") {
		effect = new TimedAddressCheat(0x96918B, duration, description);
	}

	else if (name == "rough_neighbourhood") {
		effect = (new PedsAttackOther(duration, description))->SetDisabledForMissions();
	}
	else if (name == "bounty_on_your_head") {
		effect = (new TimedFunctionCheat(CCheat::EverybodyAttacksPlayerCheat, 0x96913F, duration, description))->SetDisabledForMissions();
	}
	else if (name == "elvis_lives") {
		effect = new TimedFunctionCheat(CCheat::ElvisLivesCheat, 0x969157, duration, description, "gang_members");
	}
	else if (name == "village_people") {
		effect = (new TimedFunctionCheat(CCheat::VillagePeopleCheat, 0x969158, duration, description))->SetDisabledForMissions();
	}
	else if (name == "only_homies") {
		effect = new TimedFunctionCheat(CCheat::GangsCheat, 0x96915A, duration, description, "gang_members");
	}
	else if (name == "stay_indoors") {
		effect = new TimedFunctionCheat(CCheat::GangLandCheat, 0x96915B, duration, description, "gang_members");
	}
	else if (name == "riot_mode") {
		effect = new TimedFunctionCheat(CCheat::RiotCheat, 0x969175, duration, description);
	}
	else if (name == "everyone_armed") {
		effect = new TimedAddressCheat(0x969140, duration, description);
	}
	else if (name == "aggressive_drivers") {
		effect = new TimedAddressCheat(0x96914F, duration, description);
	}
	else if (name == "recruit_9mm") {
		effect = new TimedAddressCheat(0x96917C, duration, description, "npc_recruit");
	}
	else if (name == "recruit_ak47") {
		effect = new TimedAddressCheat(0x96917D, duration, description, "npc_recruit");
	}
	else if (name == "recruit_rockets") {
		effect = new TimedAddressCheat(0x96917E, duration, description, "npc_recruit");
	}
	else if (name == "reverse_hooker") {
		effect = new TimedAddressCheat(0x96918A, duration, description);
	}
	else if (name == "beach_party") {
		effect = new TimedFunctionCheat(Ped::MakeBeachParty, 0x969159, duration, description, "themes");
	}
	else if (name == "ninja_theme") {
		effect = new TimedFunctionCheat(Ped::MakeNinja, 0x96915C, duration, description, "themes");
	}
	else if (name == "kinky_theme") {
		effect = new TimedFunctionCheat(Ped::MakeKinky, 0x96915D, duration, description, "themes");
	}
	else if (name == "funhouse_theme") {
		effect = new TimedFunctionCheat(Ped::MakeFunhouse, 0x969176, duration, description, "themes");
	}
	else if (name == "country_traffic") {
		effect = new TimedFunctionCheat(Ped::MakeCountry, 0x96917B, duration, description, "themes");
	}

	else if (name == "drive_by") {
		effect = new TimedFunctionCheat(CCheat::DrivebyCheat, 0x969179, duration, description);
	}
	else if (name == "huge_bunny_hop") {
		effect = new TimedAddressCheat(0x969161, duration, description);
	}
	else if (name == "mega_jump") {
		effect = new TimedAddressCheat(0x96916C, duration, description);
	}
	else if (name == "infinite_oxygen") {
		effect = new TimedAddressCheat(0x96916E, duration, description);
	}
	else if (name == "mega_punch") {
		effect = new TimedAddressCheat(0x969173, duration, description);
	}

	else if (name == "never_hungry") {
		effect = new TimedAddressCheat(0x969173, duration, description);
	}
	else if (name == "lock_respect") {
		effect = new TimedAddressCheat(0x969173, duration, description);
	}
	else if (name == "lock_sex_appeal") {
		effect = new TimedAddressCheat(0x969173, duration, description);
	}

	return effect;
}
