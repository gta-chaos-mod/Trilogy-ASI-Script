#include "effects/TimedFunctionEffect.h"
#include "util/GameUtil.h"

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
DEFINE_EFFECT (PlayerClothesCheat , "effect_beach_theme"        , GROUP_THEME , CCheat::BeachPartyCheat          , 0x969159);
DEFINE_EFFECT (PlayerClothesCheat , "effect_country_traffic"    , GROUP_THEME , CCheat::CountrysideInvasionCheat , 0x96917B);
DEFINE_EFFECT (PlayerClothesCheat , "effect_funhouse_theme"     , GROUP_THEME , CCheat::FunhouseCheat            , 0x969176);
DEFINE_EFFECT (PlayerClothesCheat , "effect_naughty_theme"      , GROUP_THEME , CCheat::LoveConquersAllCheat     , 0x96915D);
DEFINE_EFFECT (PlayerClothesCheat , "effect_ninja_theme"        , GROUP_THEME , CCheat::NinjaCheat               , 0x96915C);
// clang-format on