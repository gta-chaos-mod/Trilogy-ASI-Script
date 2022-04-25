#include "util/EffectBase.h"

using namespace plugin;

class WhereIsEverybodyEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        injector::MakeCALL (0x707C84, Hooked_CShadows_StoreShadowToBeRendered);
        injector::MakeCALL (0x706B68, Hooked_CShadows_StoreRealTimeShadow);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        // TODO: Unhook

        for (CPed *ped : CPools::ms_pPedPool)
        {
            ped->m_nPedFlags.bDontRender = false;
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        for (CPed *ped : CPools::ms_pPedPool)
        {
            ped->m_nPedFlags.bDontRender = true;
        }
    }

    static void
    Hooked_CShadows_StoreShadowToBeRendered (
        char type, RwTexture *texture, RwV3d *pos, float x1, float y1, float x2,
        float y2, __int16 intensity, char r, char g, char b, float zDistance,
        char bDrawOnWater, float scale, void *shadowData, char bDrawOnBuildings)
    {
        scale = 0.0f;

        Call<0x707390> (type, texture, pos, x1, y1, x2, y2, intensity, r, g, b,
                        zDistance, bDrawOnWater, scale, shadowData,
                        bDrawOnBuildings);
    }

    static void
    Hooked_CShadows_StoreRealTimeShadow (CPhysical *thisPhysical, float *pposx,
                                         float *pposy, float *px1, float *py1,
                                         float *px2, float *py2)
    {
        if (thisPhysical->m_nType == ENTITY_TYPE_PED) return;

        Call<0x707CA0> (thisPhysical, pposx, pposy, px1, py1, px2, py2);
    }
};

DEFINE_EFFECT (WhereIsEverybodyEffect, "effect_where_is_everybody", 0);