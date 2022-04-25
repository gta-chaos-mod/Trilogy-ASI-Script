#include "util/CShopping.h"
#include "util/EffectBase.h"
#include "util/GameUtil.h"

#include <CClothes.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class RandomOutfitEffect : public EffectBase
{
    std::map<int, std::vector<std::pair<int, int>>> mClothes = {};

public:
    bool
    CanActivate () override
    {
        return GameUtil::IsPlayerSafe ();
    }

    void
    OnStart (EffectInstance *inst) override
    {
        InitialiseClothes ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (!CanActivate ()) return;

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            for (int i = CLOTHES_TEXTURE_TORSO; i < CLOTHES_TEXTURE_SPECIAL;
                 i++)
            {
                auto clothes = GetRandomCRCForComponent (inst, i);

                Command<eScriptCommands::COMMAND_GIVE_PLAYER_CLOTHES> (
                    0, clothes.second, clothes.first, i);
            }

            GameUtil::RebuildPlayer ();

            inst->Disable ();
        }
    }

    void
    InitialiseClothes ()
    {
        mClothes.clear ();

        std::vector<std::string> shops
            = {"CSchp", "CSsprt",  "LACS1",   "clothgp", "Csdesgn",
               "Csexl", "barbers", "barber2", "barber3"};

        for (auto i : shops)
        {
            CShopping::LoadShop (i.c_str ());
            for (int i = 0; i < CShopping::m_nTotalItems; i++)
            {
                auto &item = CShopping::m_aShoppingItems[i];
                if (item.modelType >= CLOTHES_TEXTURE_TORSO
                    && item.modelType <= CLOTHES_TEXTURE_SPECIAL)
                {
                    mClothes[item.modelType].push_back (
                        std::make_pair (item.modelName, item.textureName));
                }
            }
        }
    }

    std::pair<int, int>
    GetRandomCRCForComponent (EffectInstance *inst, int componentId)
    {
        int size = mClothes[componentId].size () - 1;
        if (size < 0) return {0, 0};

        int randomId = inst->Random (0, size);
        return mClothes[componentId][randomId];
    }
};

DEFINE_EFFECT (RandomOutfitEffect, "effect_random_outfit", 0);
