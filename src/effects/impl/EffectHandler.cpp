// Copyright (c) 2019 Lordmau5
#include "EffectHandler.h"

void EffectHandler::HandleEffect(std::string effect) {
	if (effect == "hot_potato") {
		Ped::SetAllOnFire();
	}
	else if (effect == "kick_out_of_car") {
		Player::KickOutOfVehicleAndLock();
	}
	else if (effect == "there_is_no_escape") {
		Player::LockPlayerInsideVehicle();
	}
	else if (effect == "set_vehicle_on_fire") {
		Vehicle::SetPlayerVehicleOnFire();
	}
	else if (effect == "pop_vehicle_tires") {
		Vehicle::PopAllVehicleTires();
	}
	else if (effect == "send_vehicles_to_space") {
		Vehicle::SendVehiclesToSpace();
	}

	else if (effect == "max_stamina") {
		Player::SetStamina(true);
	}
	else if (effect == "no_stamina") {
		Player::SetStamina(false);
	}
	else if (effect == "max_weapon_skill") {
		Player::SetWeaponSkills(true);
	}
	else if (effect == "no_weapon_skill") {
		Player::SetWeaponSkills(false);
	}
	else if (effect == "max_driving_skill") {
		Player::SetDrivingSkills(true);
	}
	else if (effect == "no_driving_skill") {
		Player::SetDrivingSkills(false);
	}

	else if (effect == "player_wasted") {
		Player::DoWasted();
	}
	else if (effect == "player_busted") {
		Player::DoBusted();
	}

	else if (effect == "turn_vehicles_around") {
		Vehicle::TurnVehiclesAround();
	}
}

TimedEffect* EffectHandler::HandleTimedEffect(std::string effect, int duration, std::string description) {
	if (effect == "totheleft_totheright") {
		return new ToTheLeftToTheRight(duration, description);
	}
	else if (effect == "timelapse") {
		return new Timelapse(duration, description);
	}
	else if (effect == "where_is_everybody") {
		return new WhereIsEverybody(duration, description);
	}
	else if (effect == "everybody_bleed_now") {
		return new EverybodyBleedNow(duration, description);
	}
	else if (effect == "to_drive_or_not_to_drive") {
		return new ToDriveOrNotToDrive(duration, description);
	}
	else if (effect == "one_hit_ko") {
		return new OneHitKO(duration, description);
	}
	else if (effect == "experience_the_lag") {
		return new LagEffect(duration, description);
	}
	else if (effect == "ghost_rider") {
		return new GhostRider(duration, description);
	}
	else if (effect == "disable_hud") {
		return new DisableHUD(duration, description);
	}
	else if (effect == "disable_radar_blips") {
		return new DisableRadarBlips(duration, description);
	}
	else if (effect == "true_pacifist") {
		return new TruePacifist(duration, description);
	}
	else if (effect == "lets_take_a_break") {
		return new LetsTakeABreak(duration, description);
	}
	else if (effect == "rainbow_cars") {
		return new RainbowCars(duration, description);
	}
	else if (effect == "no_bouncy_vehicles") {
		return new Suspension(10, duration, description);
	}
	else if (effect == "bouncy_vehicles") {
		return new Suspension(0.001f, duration, description);
	}
	else if (effect == "very_bouncy_vehicles") {
		return new Suspension(-1.0f, duration, description);
	}
	else if (effect == "long_live_the_rich") {
		return new LongLiveTheRich(duration, description);
	}
	else if (effect == "inverted_controls") {
		return new InvertedControls(duration, description);
	}
	else if (effect == "disable_one_movement_key") {
		return new DisableOneMovementKey(duration, description);
	}
	else if (effect == "fail_mission") {
		return new FailMission(duration, description);
	}
	else if (effect == "night_vision") {
		return new ThermalNightVision(true, duration, description);
	}
	else if (effect == "thermal_vision") {
		return new ThermalNightVision(false, duration, description);
	}
	else if (effect == "pass_mission") {
		return new PassMission(duration, description);
	}
	else if (effect == "cryptic_effects") {
		return new CrypticEffects(duration, description);
	}
	else if (effect == "infinite_health") {
		return new InfiniteHealth(duration, description);
	}
	else if (effect == "invisible_vehicles") {
		return new InvisibleVehicles(duration, description);
	}
	else if (effect == "framerate_15") {
		return new Framerate(15, duration, description);
	}
	else if (effect == "framerate_60") {
		return new Framerate(60, duration, description);
	}
	else if (effect == "reload_autosave") {
		return new ReloadAutosave(duration, description);
	}

	return nullptr;
}
