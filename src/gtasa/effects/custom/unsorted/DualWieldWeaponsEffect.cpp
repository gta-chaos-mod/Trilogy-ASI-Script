#include "util/EffectBase.h"
#include "util/GameUtil.h"

class DualWieldWeaponsEffect : public EffectBase
{
    std::array<bool, MAX_WEAPON_INFOS> isTwinPistol;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        isTwinPistol.fill (0);
        for (int i = 0; i < MAX_WEAPON_INFOS; i++)
        {
            CWeaponInfo *p  = aWeaponInfo + i;
            isTwinPistol[i] = p->m_nFlags.bTwinPistol;
        }
    }
    void
    OnEnd (EffectInstance *inst) override
    {
        for (int i = 0; i < MAX_WEAPON_INFOS; i++)
        {
            CWeaponInfo *p          = aWeaponInfo + i;
            p->m_nFlags.bTwinPistol = isTwinPistol[i];
        }
    }
    void
    OnTick (EffectInstance *inst) override
    {
        for (int i = 0; i < MAX_WEAPON_INFOS; i++)
        {
            CWeaponInfo *p          = aWeaponInfo + i;
            p->m_nFlags.bTwinPistol = 1;
        }
    }
};

DEFINE_EFFECT (DualWieldWeaponsEffect, "effect_dual_wield_weapons",
               GROUP_WEAPONS);