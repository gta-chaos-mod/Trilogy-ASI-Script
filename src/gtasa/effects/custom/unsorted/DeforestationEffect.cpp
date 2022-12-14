#include "util/EffectBase.h"

#include <CPools.h>

class DeforestationEffect : public EffectBase
{
    std::set<int> treeModels
        = {615,   616,   617,   618,   619,  620,  621,  622,   623,   624,
           629,   634,   641,   645,   648,  649,  652,  654,   655,   656,
           657,   658,   659,   660,   661,  664,  669,  670,   671,   672,
           673,   685,   687,   688,   689,  690,  691,  693,   694,   695,
           696,   697,   698,   700,   703,  704,  705,  706,   707,   708,
           709,   710,   711,   712,   713,  714,  715,  717,   719,   720,
           721,   722,   723,   724,   725,  726,  727,  728,   729,   730,
           731,   732,   733,   734,   735,  736,  737,  738,   739,   740,
           763,   764,   765,   766,   767,  768,  769,  770,   771,   772,
           773,   774,   775,   776,   777,  778,  779,  780,   782,   784,
           785,   789,   790,   791,   792,  8835, 8836, 8837,  886,   887,
           890,   892,   893,   894,   3505, 3506, 3507, 3508,  3509,  3510,
           3511,  3512,  3517,  3898,  9019, 9034, 9035, 16060, 16061, 18268,
           18269, 18270, 18271, 18272, 18273};

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
        if (!treeModels.contains (building->m_nModelIndex)) return;

        building->m_bUsesCollision = visible;
        building->m_bIsVisible     = visible;
    }

    void
    ToggleTree (CObject *object, bool visible)
    {
        if (!treeModels.contains (object->m_nModelIndex)) return;

        object->m_bUsesCollision = visible;
        object->m_bIsVisible     = visible;
    }
};

DEFINE_EFFECT (DeforestationEffect, "effect_deforestation", 0);