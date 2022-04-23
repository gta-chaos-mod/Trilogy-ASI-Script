#include <util/EffectBase.h>
#include <util/GenericUtil.h>

#include <CClothes.h>
#include <CClothesBuilder.h>

class DefaultOutfitEffect : public EffectBase
{
    int              wait        = 0;
    std::vector<int> slotLengths = {
        67, // Shirt
        32, // Haircut
        44, // Legs
        37, // Shoes
        2,  // Tattoo Left Upper Arm
        3,  // Tattoo Left Lower Arm
        3,  // Tattoo Right Upper Arm
        3,  // Tattoo Right Lower Arm
        6,  // Tattoo Back
        5,  // Tattoo Left Chest
        6,  // Tattoo Right Chest
        6,  // Tattoo Stomach
        5,  // Tattoo Lower Back
        11, // Necklace
        11, // Watches
        16, // Glasses
        56, // Hats
    };

public:
    void
    OnTick (EffectInstance *inst) override
    {
        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0) return;

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            CPlayerData *data = player->m_pPlayerData;
            if (data)
            {
                for (unsigned int i
                     = eClothesTexturePart::CLOTHES_TEXTURE_TORSO;
                     i < eClothesTexturePart::CLOTHES_TEXTURE_SPECIAL; i++)
                {
                    // TODO: Crashes because we are iterating over indices that
                    // probably don't exist?

                    unsigned int randomCloth
                        = (unsigned int) inst->Random (0, slotLengths[i] - 1);
                    data->m_pPedClothesDesc->SetTextureAndModel (randomCloth,
                                                                 randomCloth,
                                                                 i);
                }

                CClothes::RebuildPlayer (player, false);

                wait = 1000;
            }
        }
    }
};

// DEFINE_EFFECT (DefaultOutfitEffect, "effect_default_outfit", 0);
