#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <array>
#include <map>

static const std::array weaponsId
    = {MODEL_COLT45,  MODEL_SILENCED, MODEL_DESERT_EAGLE, MODEL_CHROMEGUN,
       MODEL_SAWNOFF, MODEL_SHOTGSPA, MODEL_MICRO_UZI,    MODEL_MP5LNG,
       MODEL_AK47,    MODEL_M4,       MODEL_TEC9};

union UInt2Float
{
    float        f;
    unsigned int ui;
};

class IncreaseShootingRateEffect : public EffectBase
{
    std::map<int, std::pair<float, unsigned int>> defaultAnimTime;
    std::map<int, std::pair<float, unsigned int>> animTime;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        for (int i = 0; i < MAX_WEAPON_INFOS; i++)
        {
            CWeaponInfo *p        = aWeaponInfo + i;
            int          modelId1 = p->m_nModelId1;
            auto         it
                = std::find (weaponsId.cbegin (), weaponsId.cend (), modelId1);
            if (it != weaponsId.cend ())
            {
                defaultAnimTime.emplace (modelId1,
                                         std::make_pair (p->m_fAnimLoopEnd,
                                                         p->m_nAnimLoop2End));

                float mult1 = (modelId1 != MODEL_TEC9) ? 0.75f : 0.955f;
                float anim1 = p->m_fAnimLoopEnd * mult1;

                UInt2Float uni;
                uni.ui      = p->m_nAnimLoop2End; // kneel shooting
                float mult2 = (modelId1 != MODEL_TEC9) ? 0.75f : 0.785f;
                uni.f *= mult2;

                animTime.emplace (modelId1, std::make_pair (anim1, uni.ui));
            }
        }
    }

    void
    OnTick (EffectInstance *inst)
    {
        for (int i = 0; i < MAX_WEAPON_INFOS; i++)
        {
            CWeaponInfo *p        = aWeaponInfo + i;
            int          modelId1 = p->m_nModelId1;

            auto it = animTime.find (modelId1);
            if (it != animTime.cend ())
            {
                auto [anim1, anim2] = it->second;
                p->m_fAnimLoopEnd   = anim1;
                p->m_nAnimLoop2End  = anim2;
            }
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        for (int i = 0; i < MAX_WEAPON_INFOS; i++)
        {
            CWeaponInfo *p        = aWeaponInfo + i;
            int          modelId1 = p->m_nModelId1;

            auto it = defaultAnimTime.find (modelId1);
            if (it != defaultAnimTime.cend ())
            {
                auto [anim1, anim2] = it->second;
                p->m_fAnimLoopEnd   = anim1;
                p->m_nAnimLoop2End  = anim2;
            }
        }
    }
};

DEFINE_EFFECT (IncreaseShootingRateEffect, "effect_increase_shooting_rate",
               GROUP_WEAPONS);