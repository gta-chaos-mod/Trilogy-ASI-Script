#include "EffectHandler.h"

EffectBase *
EffectHandler::Get (std::string state, std::string function)
{
    EffectBase *effect = nullptr;

    if (state == "weather")
    {
        effect = new Weather (std::stoi (function));
    }
    else if (state == "spawn_vehicle")
    {
        effect = new SpawnVehicleEffect (
            std::stoi (function),
            false); // "true" for experimental "put player in vehicle" mode
    }
    else if (state == "effect")
    {
        effect = HandleCheat (function);
        if (effect == nullptr)
        {
            effect = HandleEffect (function);
        }
    }
    else if (state == "teleport")
    {
        int x, y, z;
        sscanf (function.c_str (), "%d,%d,%d", &x, &y, &z);

        effect = new TeleportEffect (CVector ((float) x, (float) y, (float) z));
    }

    return effect;
}

EffectBase *
EffectHandler::HandleCheat (std::string name)
{
    EffectBase *effect = nullptr;

    /* Weapons & Health */
    if (name == "weapon_set_1")
    {
        effect = new WeaponCheat1 ();
    }
    else if (name == "weapon_set_2")
    {
        effect = new WeaponCheat2 ();
    }
    else if (name == "weapon_set_3")
    {
        effect = new WeaponCheat3 ();
    }
    else if (name == "weapon_set_4")
    {
        effect = new WeaponCheat4 ();
    }
    else if (name == "health_armor_money")
    {
        effect = new HealthArmorMoneyCheat ();
    }
    else if (name == "suicide")
    {
        effect = new SuicideCheat ();
    }
    else if (name == "infinite_ammo")
    {
        effect = new InfiniteAmmoCheat ();
    }
    else if (name == "infinite_health")
    {
        effect = new InfiniteHealthCheat ();
    }

    /* Wanted Level */
    else if (name == "wanted_plus_two")
    {
        effect = new WantedPlusTwoCheat ();
    }
    else if (name == "clear_wanted")
    {
        effect = new ClearWantedCheat ();
    }
    else if (name == "never_wanted")
    {
        effect = new NeverWantedCheat ();
    }
    else if (name == "wanted_six_stars")
    {
        effect = new WantedSixStarsCheat ();
    }

    /* Spawning */
    else if (name == "get_jetpack")
    {
        effect = new GetJetpackCheat ();
    }
    else if (name == "get_parachute")
    {
        effect = new GetParachuteCheat ();
    }

    /* Time */
    else if (name == "quarter_gamespeed")
    {
        effect = new QuarterGameSpeedCheat ();
    }
    else if (name == "half_gamespeed")
    {
        effect = new HalfGameSpeedCheat ();
    }
    else if (name == "double_gamespeed")
    {
        effect = new DoubleGameSpeedCheat ();
    }
    else if (name == "quadruple_gamespeed")
    {
        effect = new QuadrupleGameSpeedCheat ();
    }
    else if (name == "always_midnight")
    {
        effect = new AlwaysMidnightCheat ();
    }
    else if (name == "stop_game_clock")
    {
        effect = new StopGameClockCheat ();
    }
    else if (name == "faster_clock")
    {
        effect = new FasterClockCheat ();
    }

    /* Vehicles & Traffic */
    else if (name == "blow_up_all_cars")
    {
        effect = new BlowUpAllCarsCheat ();
    }
    else if (name == "pink_traffic")
    {
        effect = new PinkCarsCheat ();
    }
    else if (name == "black_traffic")
    {
        effect = new BlackCarsCheat ();
    }
    else if (name == "cheap_cars")
    {
        effect = new CheapCarsCheat ();
    }
    else if (name == "expensive_cars")
    {
        effect = new ExpensiveCarsCheat ();
    }
    else if (name == "insane_handling")
    {
        effect = new InsaneHandlingCheat ();
    }
    else if (name == "all_green_lights")
    {
        effect = new AllGreenLightsCheat ();
    }
    else if (name == "cars_on_water")
    {
        effect = new CarsOnWaterCheat ();
    }
    else if (name == "boats_fly")
    {
        effect = new BoatsFlyCheat ();
    }
    else if (name == "cars_fly")
    {
        effect = new CarsFlyCheat ();
    }
    else if (name == "smash_n_boom")
    {
        effect = new SmashNBoomCheat ();
    }
    else if (name == "all_cars_have_nitro")
    {
        effect = new AllCarsHaveNitroCheat ();
    }
    else if (name == "cars_float_away_when_hit")
    {
        effect = new CarsFloatAwayWhenHitCheat ();
    }
    else if (name == "all_taxis_have_nitro")
    {
        effect = new AllTaxisHaveNitroCheat ();
    }
    else if (name == "wheels_only_please")
    {
        effect = new WheelsOnlyPleaseCheat ();
    }

    /* Peds & Co. */
    else if (name == "peds_attack_each_other")
    {
        effect = new PedsAttackEachOtherCheat ();
    }
    else if (name == "have_a_bounty_on_your_head")
    {
        effect = new HaveABountyOnYourHeadCheat ();
    }
    else if (name == "elvis_is_everywhere")
    {
        effect = new ElvisIsEverywhereCheat ();
    }
    else if (name == "peds_attack_you")
    {
        effect = new PedsAttackYou ();
    }
    else if (name == "gang_members_everywhere")
    {
        effect = new GangMembersEverywhereCheat ();
    }
    else if (name == "gangs_control_the_streets")
    {
        effect = new GangsControlTheStreetsCheat ();
    }
    else if (name == "riot_mode")
    {
        effect = new RiotModeCheat ();
    }
    else if (name == "everyone_armed")
    {
        effect = new EveryoneArmedCheat ();
    }
    else if (name == "aggressive_drivers")
    {
        effect = new AggressiveDriversCheat ();
    }
    else if (name == "recruit_anyone_9mm")
    {
        effect = new RecruitAnyone9mmCheat ();
    }
    else if (name == "recruit_anyone_ak47")
    {
        effect = new RecruitAnyoneAK47Cheat ();
    }
    else if (name == "recruit_anyone_rockets")
    {
        effect = new RecruitAnyoneRocketsCheat ();
    }
    else if (name == "ghost_town")
    {
        effect = new GhostTownCheat ();
    }
    else if (name == "beach_theme")
    {
        effect = new BeachThemeCheat ();
    }
    else if (name == "ninja_theme")
    {
        effect = new NinjaThemeCheat ();
    }
    else if (name == "kinky_theme")
    {
        effect = new KinkyThemeCheat ();
    }
    else if (name == "funhouse_theme")
    {
        effect = new FunhouseThemeCheat ();
    }
    else if (name == "country_traffic")
    {
        effect = new CountryThemeCheat ();
    }

    /* Player Modifications */
    else if (name == "weapon_aiming_while_driving")
    {
        effect = new WeaponAimingWhileDrivingCheat ();
    }
    else if (name == "huge_bunny_hop")
    {
        effect = new HugeBunnyHopCheat ();
    }
    else if (name == "mega_jump")
    {
        effect = new MegaJumpCheat ();
    }
    else if (name == "infinite_oxygen")
    {
        effect = new InfiniteOxygenCheat ();
    }
    else if (name == "mega_punch")
    {
        effect = new MegaPunchCheat ();
    }

    /* Stats */
    else if (name == "fat_player")
    {
        effect = new FatPlayerCheat ();
    }
    else if (name == "muscle_player")
    {
        effect = new MusclePlayerCheat ();
    }
    else if (name == "skinny_player")
    {
        effect = new SkinnyPlayerCheat ();
    }
    else if (name == "max_stamina")
    {
        effect = new MaxStaminaCheat ();
    }
    else if (name == "no_stamina")
    {
        effect = new NoStaminaCheat ();
    }
    else if (name == "hitman_level_for_all_weapons")
    {
        effect = new HitmanLevelForAllWeaponsCheat ();
    }
    else if (name == "beginner_level_for_all_weapons")
    {
        effect = new BeginnerLevelForAllWeaponsCheat ();
    }
    else if (name == "max_driving_skills")
    {
        effect = new MaxDrivingSkillsCheat ();
    }
    else if (name == "no_driving_skills")
    {
        effect = new NoDrivingSkillsCheat ();
    }
    else if (name == "never_get_hungry")
    {
        effect = new NeverGetHungryCheat ();
    }
    else if (name == "lock_respect_at_max")
    {
        effect = new LockRespectAtMaxCheat ();
    }
    else if (name == "lock_sex_appeal_at_max")
    {
        effect = new LockSexAppealAtMaxCheat ();
    }

    return effect;
}

EffectBase *
EffectHandler::HandleEffect (std::string name)
{
    EffectBase *effect = nullptr;

    if (name == "remove_all_weapons")
    {
        effect = new RemoveAllWeaponsEffect ();
    }
    else if (name == "get_busted")
    {
        effect = new GetBustedEffect ();
    }
    else if (name == "get_wasted")
    {
        effect = new GetWastedEffect ();
    }
    else if (name == "set_everyone_on_fire")
    {
        effect = new SetEveryoneOnFireEffect ();
    }
    else if (name == "kick_player_out_of_vehicle")
    {
        effect = new KickPlayerOutOfVehicleEffect ();
    }
    else if (name == "lock_player_inside_vehicle")
    {
        effect = new LockPlayerInsideVehicleEffect ();
    }
    else if (name == "set_current_vehicle_on_fire")
    {
        effect = new SetCurrentVehicleOnFireEffect ();
    }
    else if (name == "pop_tires_of_all_vehicles")
    {
        effect = new PopTiresOfAllVehiclesEffect ();
    }
    else if (name == "send_vehicles_to_space")
    {
        effect = new SendVehiclesToSpaceEffect ();
    }
    else if (name == "turn_vehicles_around")
    {
        effect = new TurnVehiclesAroundEffect ();
    }
    else if (name == "to_the_left_to_the_right")
    {
        effect = new ToTheLeftToTheRightEffect ();
    }
    else if (name == "timelapse")
    {
        effect = new TimelapseEffect ();
    }
    else if (name == "where_is_everybody")
    {
        effect = new WhereIsEverybodyEffect ();
    }
    else if (name == "everybody_bleed_now")
    {
        effect = new EverybodyBleedNowEffect ();
    }
    else if (name == "to_drive_or_not_to_drive")
    {
        effect = new ToDriveOrNotToDriveEffect ();
    }
    else if (name == "one_hit_ko")
    {
        effect = new OneHitKOEffect ();
    }
    else if (name == "experience_the_lag")
    {
        effect = new ExperienceTheLagEffect ();
    }
    else if (name == "ghost_rider")
    {
        effect = new GhostRiderEffect ();
    }
    else if (name == "disable_hud")
    {
        effect = new DisableHUDEffect ();
    }
    else if (name == "disable_blips_markers_pickups")
    {
        effect = new DisableBlipsMarkersPickupsEffect ();
    }
    else if (name == "disable_all_weapon_damage")
    {
        effect = new DisableAllWeaponDamageEffect ();
    }
    else if (name == "lets_take_a_break")
    {
        effect = new LetsTakeABreakEffect ();
    }
    else if (name == "pride_cars")
    {
        effect = new PrideCarsEffect ();
    }
    else if (name == "high_suspension_damping")
    {
        effect = new HighSuspensionDampingEffect ();
    }
    else if (name == "zero_suspension_damping")
    {
        effect = new ZeroSuspensionDampingEffect ();
    }
    else if (name == "long_live_the_rich")
    {
        effect = new LongLiveTheRichEffect ();
    }
    else if (name == "inverted_controls")
    {
        effect = new InvertedControlsEffect ();
    }
    else if (name == "disable_one_movement_key")
    {
        effect = new DisableOneMovementKeyEffect ();
    }
    else if (name == "fail_current_mission")
    {
        effect = new FailCurrentMissionEffect ();
    }
    else if (name == "night_vision")
    {
        effect = new NightVisionEffect ();
    }
    else if (name == "thermal_vision")
    {
        effect = new ThermalVisionEffect ();
    }
    else if (name == "pass_current_mission")
    {
        effect = new PassCurrentMissionEffect ();
    }
    else if (name == "infinite_health_everyone")
    {
        effect = new InfiniteHealthEveryoneEffect ();
    }
    else if (name == "invisible_vehicles")
    {
        effect = new InvisibleVehiclesEffect ();
    }
    else if (name == "framerate_15")
    {
        effect = new FPS15Effect ();
    }
    else if (name == "framerate_60")
    {
        effect = new FPS60Effect ();
    }
    else if (name == "reload_autosave")
    {
        effect = new ReloadAutosaveEffect ();
    }
    else if (name == "quarter_gravity")
    {
        effect = new QuarterGravityEffect ();
    }
    else if (name == "half_gravity")
    {
        effect = new HalfGravityEffect ();
    }
    else if (name == "double_gravity")
    {
        effect = new DoubleGravityEffect ();
    }
    else if (name == "quadruple_gravity")
    {
        effect = new QuadrupleGravityEffect ();
    }
    else if (name == "inverted_gravity")
    {
        effect = new InvertedGravityEffect ();
    }
    else if (name == "zero_gravity")
    {
        effect = new ZeroGravityEffect ();
    }
    else if (name == "insane_gravity")
    {
        effect = new InsaneGravityEffect ();
    }
    else if (name == "tunnel_vision")
    {
        effect = new TunnelVisionEffect ();
    }
    else if (name == "high_pitched_audio")
    {
        effect = new HighPitchedAudioEffect ();
    }
    else if (name == "pitch_shifter")
    {
        effect = new PitchShifterEffect ();
    }
    else if (name == "fake_pass_current_mission")
    {
        effect = new FakePassCurrentMissionEffect ();
    }
    else if (name == "dvd_screensaver")
    {
        effect = new DVDScreensaverEffect ();
    }
    else if (name == "honk_boost")
    {
        effect = new HonkBoostEffect ();
    }
    else if (name == "oh_hey_tanks")
    {
        effect = new OhHeyTanksEffect ();
    }
    else if (name == "always_wanted")
    {
        effect = new AlwaysWantedEffect ();
    }
    else if (name == "cinematic_vehicle_camera")
    {
        effect = new CinematicVehicleCameraEffect ();
    }
    else if (name == "top_down_camera")
    {
        effect = new TopDownCameraEffect ();
    }
    else if (name == "your_car_floats_away_when_hit")
    {
        effect = new YourCarFloatsAwayWhenHitEffect ();
    }
    else if (name == "ring_ring")
    {
        effect = new RingRingEffect ();
    }
    else if (name == "peds_explode_when_run_over")
    {
        effect = new PedsExplodeWhenRunOverEffect ();
    }
    else if (name == "honk_vehicle")
    {
        effect = new HonkVehicleEffect ();
    }
    else if (name == "quake_fov")
    {
        effect = new QuakeFOVEffect ();
    }
    else if (name == "beyblade")
    {
        effect = new BeybladeEffect ();
    }
    else if (name == "weapon_roulette")
    {
        effect = new WeaponRouletteEffect ();
    }
    else if (name == "no_need_to_hurry")
    {
        effect = new NoNeedToHurryEffect ();
    }
    else if (name == "drunk_player")
    {
        effect = new DrunkPlayerEffect ();
    }
    else if (name == "force_vehicle_mouse_steering")
    {
        effect = new ForceVehicleMouseSteering ();
    }
    else if (name == "upside_down_screen")
    {
        effect = new UpsideDownScreenEffect ();
    }
    else if (name == "mirrored_screen")
    {
        effect = new MirroredScreenEffect ();
    }
    else if (name == "big_heads")
    {
        effect = new BigHeadsEffect ();
    }
    else if (name == "mirrored_world")
    {
        effect = new MirroredWorldEffect ();
    }
    else if (name == "pedal_to_the_metal")
    {
        effect = new PedalToTheMetalEffect ();
    }
    else if (name == "unflippable_vehicles")
    {
        effect = new UnflippableVehiclesEffect ();
    }
    else if (name == "freefall")
    {
        effect = new FreefallEffect ();
    }
    else if (name == "carpocalypse")
    {
        effect = new CarpocalypseEffect ();
    }
    else if (name == "i_am_speed")
    {
        effect = new IAmSpeedEffect ();
    }
    else if (name == "roll_credits")
    {
        effect = new RollCreditsEffect ();
    }
    /*
    // TODO: Add support for new RwRenderFast system like in Upside-Down and
    Mirrored Screen effects else if (name == "greyscale_screen") { effect = new
    GreyscaleScreenEffect();
    }
    */

    return effect;
}
