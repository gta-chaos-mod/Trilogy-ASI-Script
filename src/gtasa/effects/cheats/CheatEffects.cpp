#include "effects/OneTimeFunctionEffect.h"
#include "effects/TimedAddressEffect.h"
#include "effects/TimedFunctionEffect.h"
#include "util/EffectBase.h"

#include <CCheat.h>

// clang-format off

// NPCs
DEFINE_EFFECT (TimedAddressEffect    , "effect_aggressive_drivers"          , GROUP_PED_SPAWNS                          , 0x96914F);
DEFINE_EFFECT (TimedFunctionEffect   , "effect_elvis_is_everywhere"         , GROUP_PED_SPAWNS                          , CCheat::ElvisLivesCheat          , 0x969157);
DEFINE_EFFECT (TimedAddressEffect    , "effect_everyone_armed"              , GROUP_PED_SPAWNS                          , 0x969140);
DEFINE_EFFECT (TimedFunctionEffect   , "effect_gang_members_everywhere"     , GROUP_PED_SPAWNS                          , CCheat::GangsCheat               , 0x96915A);
DEFINE_EFFECT (TimedFunctionEffect   , "effect_gangs_control_the_streets"   , GROUP_PED_SPAWNS                          , CCheat::GangLandCheat            , 0x96915B);
DEFINE_EFFECT (TimedAddressEffect    , "effect_ghost_town"                  , GROUP_PED_SPAWNS | GROUP_VEHICLE_RARITY   , 0x96917A);
DEFINE_EFFECT (TimedFunctionEffect   , "effect_npcs_attack_you"             , GROUP_PEDS_ATTACK | GROUP_PED_SPAWNS      , CCheat::VillagePeopleCheat       , 0x969158);
DEFINE_EFFECT (TimedAddressEffect    , "effect_recruit_anyone_9mm"          , GROUP_PED_SPAWNS | GROUP_NPC_RECRUIT      , 0x96917C);
DEFINE_EFFECT (TimedAddressEffect    , "effect_recruit_anyone_ak47"         , GROUP_PED_SPAWNS | GROUP_NPC_RECRUIT      , 0x96917D);
DEFINE_EFFECT (TimedAddressEffect    , "effect_recruit_anyone_rockets"      , GROUP_PED_SPAWNS | GROUP_NPC_RECRUIT      , 0x96917E);
DEFINE_EFFECT (TimedFunctionEffect   , "effect_riot_mode"                   , GROUP_PED_SPAWNS                          , CCheat::RiotCheat                , 0x969175);

// Player
DEFINE_EFFECT (OneTimeFunctionEffect , "effect_get_jetpack"                 , 0                                         , CCheat::JetpackCheat);
DEFINE_EFFECT (OneTimeFunctionEffect , "effect_get_parachute"               , 0                                         , CCheat::ParachuteCheat);

// Stats
DEFINE_EFFECT (TimedAddressEffect    , "effect_huge_bunny_hop"              , 0                                         , 0x969161);
DEFINE_EFFECT (TimedAddressEffect    , "effect_infinite_oxygen"             , 0                                         , 0x96916E);
DEFINE_EFFECT (TimedAddressEffect    , "effect_lock_respect_at_max"         , 0                                         , 0x96917F);
DEFINE_EFFECT (TimedAddressEffect    , "effect_lock_sex_appeal_at_max"      , 0                                         , 0x969180);
DEFINE_EFFECT (TimedAddressEffect    , "effect_mega_jump"                   , 0                                         , 0x96916C);
// TODO: Mega Punch (Custom Implementation to be able to punch cars away)
DEFINE_EFFECT (TimedAddressEffect    , "effect_never_get_hungry"            , 0                                         , 0x969174);
DEFINE_EFFECT (TimedFunctionEffect   , "effect_weapon_aiming_while_driving" , 0                                         , CCheat::DrivebyCheat             , 0x969179);

// Theme - Defined in their own file "theme/ThemeEffects.cpp"

// Time
DEFINE_EFFECT (TimedAddressEffect    , "effect_faster_clock"                , GROUP_TIME                                , 0x96913B);

// Vehicle
DEFINE_EFFECT (TimedAddressEffect    , "effect_all_cars_have_nitro"         , 0                                         , 0x969165);
DEFINE_EFFECT (TimedAddressEffect    , "effect_all_green_lights"            , 0                                         , 0x96914E);
DEFINE_EFFECT (TimedAddressEffect    , "effect_all_taxis_have_nitro"        , 0                                         , 0x96918B);
DEFINE_EFFECT (TimedAddressEffect    , "effect_boats_fly"                   , 0                                         , 0x969153);
DEFINE_EFFECT (TimedAddressEffect    , "effect_cars_fly"                    , 0                                         , 0x969160);
DEFINE_EFFECT (TimedAddressEffect    , "effect_cars_on_water"               , 0                                         , 0x969152);
DEFINE_EFFECT (TimedFunctionEffect   , "effect_cheap_cars"                  , GROUP_VEHICLE_RARITY                      , CCheat::AllCarsAreShitCheat      , 0x96915E);
DEFINE_EFFECT (TimedFunctionEffect   , "effect_expensive_cars"              , GROUP_VEHICLE_RARITY                      , CCheat::AllCarsAreGreatCheat     , 0x96915F);
DEFINE_EFFECT (TimedAddressEffect    , "effect_insane_handling"             , 0                                         , 0x96914C);

// Wanted
DEFINE_EFFECT (TimedFunctionEffect   , "effect_never_wanted"                , GROUP_WANTED                              , CCheat::NotWantedCheat           , 0x969171);

// Weapon
DEFINE_EFFECT (TimedAddressEffect    , "effect_infinite_ammo"               , 0                                         , 0x969178);
DEFINE_EFFECT (OneTimeFunctionEffect , "effect_weapon_set_1"                , GROUP_WEAPONS                             , CCheat::WeaponCheat1);
DEFINE_EFFECT (OneTimeFunctionEffect , "effect_weapon_set_2"                , GROUP_WEAPONS                             , CCheat::WeaponCheat2);
DEFINE_EFFECT (OneTimeFunctionEffect , "effect_weapon_set_3"                , GROUP_WEAPONS                             , CCheat::WeaponCheat3);

// clang-format on
