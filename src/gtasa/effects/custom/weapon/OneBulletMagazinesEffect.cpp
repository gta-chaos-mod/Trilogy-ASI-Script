#include <util/EffectBase.h>

class OneBulletMagazinesEffect : public EffectBase
{
public:
    void
    OnTick (EffectInstance *inst) override
    {
        for (CPed *ped : CPools::ms_pPedPool)
        {
            for (int i = 0; i < 13; i++)
            {
                CWeapon &weapon      = ped->m_aWeapons[i];
                weapon.m_nAmmoInClip = std::min (weapon.m_nAmmoInClip, 1u);
            }
        }
    }
};

DEFINE_EFFECT (OneBulletMagazinesEffect, "effect_one_bullet_magazines", 0);