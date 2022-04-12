#include <util/EffectBase.h>
#include <effects/TimedFunctionEffect.h>
#include <effects/TimedAddressEffect.h>
#include <effects/OneTimeFunctionEffect.h>

#include <CCheat.h>
#include <util/GameUtil.h>

class PlayerClothesCheat : public TimedFunctionEffect
{
public:
    PlayerClothesCheat (std::function<void ()> function, int addr)
        : TimedFunctionEffect (
            [function]
            {
                function ();
                GameUtil::RebuildPlayer ();
            },
            addr)
    {
    }
};

// clang-format off

// Timed Cheats with functions
DEFINE_EFFECT (TimedFunctionEffect , "effect_cheap_cars"                  , "Test" , 1000 , CCheat::AllCarsAreShitCheat      , 0x96915E);
DEFINE_EFFECT (TimedFunctionEffect , "effect_expensive_cars"              , "Test" , 1000 , CCheat::AllCarsAreGreatCheat     , 0x96915F);
DEFINE_EFFECT (TimedFunctionEffect , "effect_never_wanted"                , "Test" , 1000 , CCheat::NotWantedCheat           , 0x969171);
DEFINE_EFFECT (TimedFunctionEffect , "effect_weapon_aiming_while_driving" , "Test" , 1000 , CCheat::DrivebyCheat             , 0x969179);
DEFINE_EFFECT (TimedFunctionEffect , "effect_peds_attack_you"             , "Test" , 1000 , CCheat::VillagePeopleCheat       , 0x969158);
DEFINE_EFFECT (TimedFunctionEffect , "effect_gangs_control_the_streets"   , "Test" , 1000 , CCheat::GangLandCheat            , 0x96915B);
DEFINE_EFFECT (TimedFunctionEffect , "effect_riot_mode"                   , "Test" , 1000 , CCheat::RiotCheat                , 0x969175);
DEFINE_EFFECT (TimedFunctionEffect , "effect_gang_members_everywhere"     , "Test" , 1000 , CCheat::GangsCheat               , 0x96915A);
DEFINE_EFFECT (TimedFunctionEffect , "effect_elvis_is_everywhere"         , "Test" , 1000 , CCheat::ElvisLivesCheat          , 0x969157);
DEFINE_EFFECT (PlayerClothesCheat  , "effect_ninja_theme"                 , "Test" , 1000 , CCheat::NinjaCheat               , 0x96915C);
DEFINE_EFFECT (PlayerClothesCheat  , "effect_kinky_theme"                 , "Test" , 1000 , CCheat::LoveConquersAllCheat     , 0x96915D);
DEFINE_EFFECT (PlayerClothesCheat  , "effect_funhouse_theme"              , "Test" , 1000 , CCheat::FunhouseCheat            , 0x969176);
DEFINE_EFFECT (PlayerClothesCheat  , "effect_country_traffic"             , "Test" , 1000 , CCheat::CountrysideInvasionCheat , 0x96917B);
DEFINE_EFFECT (PlayerClothesCheat  , "effect_beach_theme"                 , "Test" , 1000 , CCheat::BeachPartyCheat          , 0x969159);

DEFINE_EFFECT(TimedAddressEffect , "effect_infinite_ammo"          , "Test" , 1000 , 0x969178);
DEFINE_EFFECT(TimedAddressEffect , "effect_all_taxis_have_nitro"   , "Test" , 1000 , 0x96918B);
DEFINE_EFFECT(TimedAddressEffect , "effect_boats_fly"              , "Test" , 1000 , 0x969153);
DEFINE_EFFECT(TimedAddressEffect , "effect_cars_fly"               , "Test" , 1000 , 0x969160);
DEFINE_EFFECT(TimedAddressEffect , "effect_cars_on_water"          , "Test" , 1000 , 0x969152);
DEFINE_EFFECT(TimedAddressEffect , "effect_insane_handling"        , "Test" , 1000 , 0x96914C);
DEFINE_EFFECT(TimedAddressEffect , "effect_smash_n_boom"           , "Test" , 1000 , 0x969164);
DEFINE_EFFECT(TimedAddressEffect , "effect_all_green_lights"       , "Test" , 1000 , 0x96914E);
DEFINE_EFFECT(TimedAddressEffect , "effect_all_cars_have_nitro"    , "Test" , 1000 , 0x969165);
DEFINE_EFFECT(TimedAddressEffect , "effect_stop_game_clock"        , "Test" , 1000 , 0x969168);
DEFINE_EFFECT(TimedAddressEffect , "effect_faster_clock"           , "Test" , 1000 , 0x96913B);
DEFINE_EFFECT(TimedAddressEffect , "effect_always_midnight"        , "Test" , 1000 , 0x969167);
DEFINE_EFFECT(TimedAddressEffect , "effect_mega_jump"              , "Test" , 1000 , 0x96916C);
DEFINE_EFFECT(TimedAddressEffect , "effect_mega_punch"             , "Test" , 1000 , 0x969173);
DEFINE_EFFECT(TimedAddressEffect , "effect_recruit_anyone_ak47"    , "Test" , 1000 , 0x96917D);
DEFINE_EFFECT(TimedAddressEffect , "effect_recruit_anyone_rockets" , "Test" , 1000 , 0x96917E);
DEFINE_EFFECT(TimedAddressEffect , "effect_recruit_anyone_9mm"     , "Test" , 1000 , 0x96917C);
DEFINE_EFFECT(TimedAddressEffect , "effect_never_get_hungry"       , "Test" , 1000 , 0x969174);
DEFINE_EFFECT(TimedAddressEffect , "effect_ghost_town"             , "Test" , 1000 , 0x96917A);
DEFINE_EFFECT(TimedAddressEffect , "effect_lock_sex_appeal_at_max" , "Test" , 1000 , 0x969180);
DEFINE_EFFECT(TimedAddressEffect , "effect_everyone_armed"         , "Test" , 1000 , 0x969140);
DEFINE_EFFECT(TimedAddressEffect , "effect_lock_respect_at_max"    , "Test" , 1000 , 0x96917F);
DEFINE_EFFECT(TimedAddressEffect , "effect_infinite_oxygen"        , "Test" , 1000 , 0x96916E);
DEFINE_EFFECT(TimedAddressEffect , "effect_aggressive_drivers"     , "Test" , 1000 , 0x96914F);
DEFINE_EFFECT(TimedAddressEffect , "effect_huge_bunny_hop"         , "Test" , 1000 , 0x969161);

DEFINE_EFFECT(OneTimeFunctionEffect, "effect_weapon_set_1", "Test", 1000 ,CCheat::WeaponCheat1);
DEFINE_EFFECT(OneTimeFunctionEffect, "effect_weapon_set_2", "Test", 1000 ,CCheat::WeaponCheat2);
DEFINE_EFFECT(OneTimeFunctionEffect, "effect_weapon_set_3", "Test", 1000 ,CCheat::WeaponCheat3);
DEFINE_EFFECT(OneTimeFunctionEffect, "effect_get_jetpack", "Test", 1000 ,CCheat::JetpackCheat);
DEFINE_EFFECT(OneTimeFunctionEffect, "effect_get_parachute", "Test", 1000 ,CCheat::ParachuteCheat);
DEFINE_EFFECT(OneTimeFunctionEffect, "effect_fat_player", "Test", 1000 ,CCheat::FatCheat);
DEFINE_EFFECT(OneTimeFunctionEffect, "effect_max_muscle", "Test", 1000 ,CCheat::MuscleCheat);
DEFINE_EFFECT(OneTimeFunctionEffect, "effect_skinny_player", "Test", 1000 ,CCheat::SkinnyCheat);

//DEFINE_EFFECT(OneTimeFunctionEffect, "effect_give_health_armor_money", "Test", 1000 ,Player::GivePlayerHealthArmorMoney, Vehicle::FixPlayerVehicle);
//DEFINE_EFFECT(OneTimeFunctionEffect, "effect_suicide", "Test", 1000 ,Player::KillPlayer);

// clang-format on
