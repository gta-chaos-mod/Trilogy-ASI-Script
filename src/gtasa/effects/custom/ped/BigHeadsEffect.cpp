#include "BigHeadsEffect.h"
#include "Events.h"
#include "CPed.h"
#include "common.h"
#include "ePedBones.h"

BigHeadsEffect::BigHeadsEffect () : EffectBase ("effect_big_heads") {}

void
BigHeadsEffect::Enable ()
{
    EffectBase::Enable ();

    plugin::Events::pedRenderEvent += RenderPedEvent;
}

void
BigHeadsEffect::Disable ()
{
    plugin::Events::pedRenderEvent -= RenderPedEvent;

    EffectBase::Disable ();
}

void
BigHeadsEffect::RenderPedEvent (CPed *ped)
{
    auto animHier = GetAnimHierarchyFromSkinClump (ped->m_pRwClump);
    auto matrices = RpHAnimHierarchyGetMatrixArray (animHier);

    const float coefficient = 3.0;
    RwV3d       scale       = {coefficient, coefficient, coefficient};

    for (int i = BONE_NECK; i <= BONE_HEAD; i++)
    {
        RwMatrixScale (&matrices[RpHAnimIDGetIndex (animHier, i)], &scale,
                       rwCOMBINEPRECONCAT);
    }
}
