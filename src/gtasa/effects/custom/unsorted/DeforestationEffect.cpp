#include "util/EffectBase.h"

#include <CPools.h>
#include <util/GameUtil.h>

class DeforestationEffect : public EffectBase
{
public:
    void
    OnEnd (EffectInstance *inst) override
    {
        for (CBuilding *building : CPools::ms_pBuildingPool)
        {
            ToggleTree (building, true);
        }

        for (CObject *object : CPools::ms_pObjectPool)
        {
            ToggleTree (object, true);
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        for (CBuilding *building : CPools::ms_pBuildingPool)
        {
            ToggleTree (building, false);
        }

        for (CObject *object : CPools::ms_pObjectPool)
        {
            ToggleTree (object, false);
        }
    }

    void
    ToggleTree (CBuilding *building, bool visible)
    {
        if (!GameUtil::IsTreeModel (building->m_nModelIndex)) return;

        building->bUsesCollision = visible;
        building->bIsVisible     = visible;
    }

    void
    ToggleTree (CObject *object, bool visible)
    {
        if (!GameUtil::IsTreeModel (object->m_nModelIndex)) return;

        object->bUsesCollision = visible;
        object->bIsVisible     = visible;
    }
};

DEFINE_EFFECT (DeforestationEffect, "effect_deforestation", 0);