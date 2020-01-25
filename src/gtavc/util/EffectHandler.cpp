#include "EffectHandler.h"

EffectBase* EffectHandler::Get(std::string state, std::string function) {
	EffectBase* effect = nullptr;

	if (state == "weather") {
		// 0 to 4
		effect = new Weather(std::stoi(function));
	}
	else if (state == "spawn_vehicle") {
		effect = new SpawnVehicle(std::stoi(function));
	}
	else if (state == "effect") {
		effect = HandleCheat(function);
		if (effect == nullptr) {
			effect = HandleEffect(function);
		}
	}
	else if (state == "teleport") {
		int x, y, z;
		sscanf(function.c_str(), "%d,%d,%d", &x, &y, &z);

		effect = new Teleport(CVector((float)x, (float)y, (float)z));
	}

	return effect;
}

EffectBase* EffectHandler::HandleCheat(std::string name) {
	EffectBase* effect = nullptr;

	// Ped
	if (name == "armed_female_peds") {
		effect = new ArmedFemalePedsCheat();
	}
	else if (name == "armed_peds") {
		effect = new ArmedPedsCheat();
	}
	else if (name == "hostile_peds") {
		effect = new HostilePedsCheat();
	}
	else if (name == "ladies_man") {
		effect = new LadiesManCheat();
	}
	else if (name == "peds_get_in_your_car") {
		effect = new PedsGetInYourCarCheat();
	}
	else if (name == "riot") {
		effect = new RiotCheat();
	}

	// Player
	else if (name == "full_armor") {
		effect = new FullArmorCheat();
	}
	else if (name == "full_health") {
		effect = new FullHealthCheat();
	}
	else if (name == "suicide") {
		effect = new SuicideCheat();
	}

	// Skin
	else if (name == "candy_suxxx_skin") {
		effect = new CandySuxxxSkinCheat();
	}
	else if (name == "dick_skin") {
		effect = new DickSkinCheat();
	}
	else if (name == "fat_skin") {
		effect = new FatSkinCheat();
	}
	else if (name == "hilary_skin") {
		effect = new HilarySkinCheat();
	}
	else if (name == "jezz_skin") {
		effect = new JezzSkinCheat();
	}
	else if (name == "ken_skin") {
		effect = new KenSkinCheat();
	}
	else if (name == "lance_skin") {
		effect = new LanceSkinCheat();
	}
	else if (name == "mercedes_skin") {
		effect = new MercedesSkinCheat();
	}
	else if (name == "phil_skin") {
		effect = new PhilSkinCheat();
	}
	else if (name == "random_outfit") {
		effect = new RandomOutfitCheat();
	}
	else if (name == "ricardo_skin") {
		effect = new RicardoSkinCheat();
	}
	else if (name == "skinny_skin") {
		effect = new SkinnySkinCheat();
	}
	else if (name == "sonny_skin") {
		effect = new SonnySkinCheat();
	}

	// Time
	else if (name == "double_game_speed") {
		effect = new DoubleGameSpeedCheat();
	}
	else if (name == "half_game_speed") {
		effect = new HalfGameSpeedCheat();
	}
	else if (name == "quadruple_game_speed") {
		effect = new QuadrupleGameSpeedCheat();
	}
	else if (name == "quarter_game_speed") {
		effect = new QuarterGameSpeedCheat();
	}
	else if (name == "quick_clock") {
		effect = new QuickClockCheat();
	}

	// Vehicle
	else if (name == "aggressive_drivers") {
		effect = new AggressiveDriversCheat();
	}
	else if (name == "all_green_lights") {
		effect = new AllGreenLightsCheat();
	}
	else if (name == "big_wheels") {
		effect = new BigWheelsCheat();
	}
	else if (name == "black_cars") {
		effect = new BlackCarsCheat();
	}
	else if (name == "cars_on_water") {
		effect = new CarsOnWaterCheat();
	}
	else if (name == "explode_all_vehicles") {
		effect = new ExplodeAllVehiclesCheat();
	}
	else if (name == "flying_boats") {
		effect = new FlyingBoatsCheat();
	}
	else if (name == "flying_cars") {
		effect = new FlyingCarsCheat();
	}
	else if (name == "insane_handling") {
		effect = new InsaneHandlingCheat();
	}
	else if (name == "pink_cars") {
		effect = new PinkCarsCheat();
	}
	else if (name == "wheels_only") {
		effect = new WheelsOnlyCheat();
	}

	// Wanted
	else if (name == "clear_wanted_level") {
		effect = new ClearWantedLevelCheat();
	}
	else if (name == "increase_wanted_level") {
		effect = new IncreaseWantedLevelCheat();
	}

	// Weapons
	else if (name == "weapon_set_1") {
		effect = new WeaponCheat1();
	}
	else if (name == "weapon_set_2") {
		effect = new WeaponCheat2();
	}
	else if (name == "weapon_set_3") {
		effect = new WeaponCheat3();
	}

	return effect;
}

EffectBase* EffectHandler::HandleEffect(std::string name) {
	EffectBase* effect = nullptr;

	// HUD
	if (name == "disable_hud") {
		effect = new DisableHUDEffect();
	}
	else if (name == "disable_radar_blips") {
		effect = new DisableRadarBlipsEffect();
	}
	else if (name == "dvd_screensaver") {
		effect = new DVDScreensaverEffect();
	}
	else if (name == "tunnel_vision") {
		effect = new TunnelVisionEffect();
	}

	// Ped
	else if (name == "disable_all_weapon_damage") {
		effect = new DisableAllWeaponDamageEffect();
	}
	else if (name == "everybody_bleed_now") {
		effect = new EverybodyBleedNowEffect();
	}
	else if (name == "infinite_health_everyone") {
		effect = new InfiniteHealthEveryoneEffect();
	}
	else if (name == "long_live_the_rich") {
		effect = new LongLiveTheRichEffect();
	}
	else if (name == "one_hit_ko") {
		effect = new OneHitKOEffect();
	}
	else if (name == "remove_all_weapons") {
		effect = new RemoveAllWeaponsEffect();
	}
	else if (name == "set_all_peds_on_fire") {
		effect = new SetAllPedsOnFireEffect();
	}
	else if (name == "where_is_everybody") {
		effect = new WhereIsEverybodyEffect();
	}

	// Time
	else if (name == "experience_the_lag") {
		effect = new ExperienceTheLagEffect();
	}
	else if (name == "fps_15") {
		effect = new FPS15Effect();
	}
	else if (name == "fps_60") {
		effect = new FPS60Effect();
	}
	else if (name == "timelapse") {
		effect = new TimelapseEffect();
	}

	// Unsorted
	else if (name == "reload_autosave") {
		effect = new ReloadAutosaveEffect();
	}

	// Vehicle
	else if (name == "ghost_rider") {
		effect = new GhostRiderEffect();
	}
	else if (name == "high_suspension_damping") {
		effect = new HighSuspensionDampingEffect();
	}
	else if (name == "invisible_vehicles") {
		effect = new InvisibleVehiclesEffect();
	}
	else if (name == "lightspeed_braking") {
		effect = new LightspeedBrakingEffect();
	}
	else if (name == "little_suspension_damping") {
		effect = new LittleSuspensionDampingEffect();
	}
	else if (name == "pop_tires_of_all_vehicles") {
		effect = new PopTiresOfAllVehiclesEffect();
	}
	else if (name == "rainbow_cars") {
		effect = new RainbowCarsEffect();
	}
	else if (name == "send_vehicles_to_space") {
		effect = new SendVehiclesToSpaceEffect();
	}
	else if (name == "set_current_vehicle_on_fire") {
		effect = new SetCurrentVehicleOnFireEffect();
	}
	else if (name == "to_drive_or_not_to_drive") {
		effect = new ToDriveOrNotToDriveEffect();
	}
	else if (name == "to_the_left_to_the_right") {
		effect = new ToTheLeftToTheRightEffect();
	}
	else if (name == "turn_vehicles_around") {
		effect = new TurnVehiclesAroundEffect();
	}
	else if (name == "zero_suspension_damping") {
		effect = new ZeroSuspensionDampingEffect();
	}

	return effect;
}
