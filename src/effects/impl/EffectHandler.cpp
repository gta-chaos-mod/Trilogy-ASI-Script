// Copyright (c) 2019 Lordmau5
#include "EffectHandler.h"

TimedEffect* EffectHandler::HandleEffect(const std::string& name, int duration, const std::string& description) {
	// *** One-Time Effects ***

	TimedEffect* effect = nullptr;

	if (name == "clear_weapons") {
		effect = new FunctionEffect(Ped::ClearWeapons, duration, description);
	}
	else if (name == "hot_potato") {
		effect = new FunctionEffect(Ped::SetAllOnFire, duration, description);
	}
	else if (name == "kick_out_of_car") {
		effect = new FunctionEffect(Player::KickOutOfVehicleAndLock, duration, description);
	}
	else if (name == "set_vehicle_on_fire") {
		effect = new FunctionEffect(Vehicle::SetPlayerVehicleOnFire, duration, description);
	}
	else if (name == "pop_vehicle_tires") {
		effect = new FunctionEffect(Vehicle::PopAllVehicleTires, duration, description);
	}
	else if (name == "send_vehicles_to_space") {
		effect = new FunctionEffect(Vehicle::SendVehiclesToSpace, duration, description);
	}

	else if (name == "max_stamina") {
		effect = new FunctionEffect(Player::MaxStamina, duration, description);
	}
	else if (name == "no_stamina") {
		effect = new FunctionEffect(Player::NoStamina, duration, description);
	}
	else if (name == "max_weapon_skill") {
		effect = new FunctionEffect(Player::MaxWeaponSkills, duration, description);
	}
	else if (name == "no_weapon_skill") {
		effect = new FunctionEffect(Player::NoWeaponSkills, duration, description);
	}
	else if (name == "max_driving_skill") {
		effect = new FunctionEffect(Player::MaxDrivingSkills, duration, description);
	}
	else if (name == "no_driving_skill") {
		effect = new FunctionEffect(Player::NoDrivingSkills, duration, description);
	}

	else if (name == "player_wasted") {
		effect = new FunctionEffect(Player::DoWasted, duration, description);
	}
	else if (name == "player_busted") {
		effect = new FunctionEffect(Player::DoBusted, duration, description);
	}

	else if (name == "turn_vehicles_around") {
		effect = new FunctionEffect(Vehicle::TurnVehiclesAround, duration, description);
	}

	// *** End of One-Time Effects ***

	// *** Timed Effects ***

	else if (name == "to_the_left_to_the_right") {
		effect = new ToTheLeftToTheRight(duration, description);
	}
	else if (name == "timelapse") {
		effect = new Timelapse(duration, description);
	}
	else if (name == "where_is_everybody") {
		effect = new WhereIsEverybody(duration, description);
	}
	else if (name == "everybody_bleed_now") {
		effect = new EverybodyBleedNow(duration, description);
	}
	else if (name == "to_drive_or_not_to_drive") {
		effect = new ToDriveOrNotToDrive(duration, description);
	}
	else if (name == "one_hit_ko") {
		effect = new OneHitKO(duration, description);
	}
	else if (name == "experience_the_lag") {
		effect = new LagEffect(duration, description);
	}
	else if (name == "ghost_rider") {
		effect = new GhostRider(duration, description);
	}
	else if (name == "disable_hud") {
		effect = new DisableHUD(duration, description);
	}
	else if (name == "disable_radar_blips") {
		effect = new DisableRadarBlips(duration, description);
	}
	else if (name == "true_pacifist") {
		effect = new TruePacifist(duration, description);
	}
	else if (name == "lets_take_a_break") {
		effect = new LetsTakeABreak(duration, description);
	}
	else if (name == "rainbow_cars") {
		effect = new RainbowCars(duration, description);
	}
	else if (name == "no_bouncy_vehicles") {
		effect = new Suspension(10, duration, description);
	}
	else if (name == "bouncy_vehicles") {
		effect = new Suspension(0.001f, duration, description);
	}
	else if (name == "very_bouncy_vehicles") {
		effect = new Suspension(-1.0f, duration, description);
	}
	else if (name == "long_live_the_rich") {
		effect = new LongLiveTheRich(duration, description);
	}
	else if (name == "inverted_controls") {
		effect = new InvertedControls(duration, description);
	}
	else if (name == "disable_one_movement_key") {
		effect = new DisableOneMovementKey(duration, description);
	}
	else if (name == "fail_mission") {
		effect = new FailMission(false, duration, description);
	}
	else if (name == "night_vision") {
		effect = new ThermalNightVision(true, duration, description);
	}
	else if (name == "thermal_vision") {
		effect = new ThermalNightVision(false, duration, description);
	}
	else if (name == "pass_mission") {
		effect = new PassMission(duration, description);
	}
	else if (name == "cryptic_effects") {
		effect = new CrypticEffects(duration, description);
	}
	else if (name == "infinite_health") {
		effect = new InfiniteHealth(false, duration, description);
	}
	else if (name == "wheels_only_please") {
		effect = new InvisibleVehicles(true, duration, description);
	}
	else if (name == "invisible_vehicles") {
		effect = new InvisibleVehicles(false, duration, description);
	}
	else if (name == "framerate_15") {
		effect = new Framerate(15, duration, description);
	}
	else if (name == "framerate_60") {
		effect = new Framerate(60, duration, description);
	}
	else if (name == "reload_autosave") {
		effect = new ReloadAutosave(duration, description);
	}

	else if (name == "quarter_gravity") {
		effect = new Gravity(0.002f, duration, description);
	}
	else if (name == "half_gravity") {
		effect = new Gravity(0.004f, duration, description);
	}
	else if (name == "double_gravity") {
		effect = new Gravity(0.016f, duration, description);
	}
	else if (name == "quadruple_gravity") {
		effect = new Gravity(0.032f, duration, description);
	}
	else if (name == "inverted_gravity") {
		effect = new CustomGravity(-0.001f, duration, description);
	}
	else if (name == "zero_gravity") {
		effect = new CustomGravity(0.0f, duration, description);
	}
	else if (name == "insane_gravity") {
		effect = new CustomGravity(0.64f, duration, description);
	}

	else if (name == "quarter_gamespeed") {
		effect = new GameSpeed(0.25f, duration / 3, description);
	}
	else if (name == "half_gamespeed") {
		effect = new GameSpeed(0.5f, duration / 3 * 2, description);
	}
	else if (name == "double_gamespeed") {
		effect = new GameSpeed(2.0f, duration, description);
	}
	else if (name == "quadruple_gamespeed") {
		effect = new GameSpeed(4.0f, duration, description);
	}
	else if (name == "there_is_no_escape") {
		effect = new LockPlayerInsideVehicle(duration, description);
	}

	else if (name == "infinite_health_player") {
		effect = new InfiniteHealth(true, duration, description);
	}
	else if (name == "woozie_mode") {
		effect = new WoozieMode(duration, description);
	}
	else if (name == "chipmunks") {
		effect = new AudioPitch(1.5f, duration, description);
	}
	else if (name == "vocal_range") {
		effect = new PitchShifter(duration, description);
	}
	else if (name == "fail_pass_mission") {
		effect = new FailMission(true, duration, description);
	}

	return effect;
}
