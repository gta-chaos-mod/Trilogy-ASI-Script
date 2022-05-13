#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

using namespace plugin;

class WhereIsEverybodyEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_ARGS (inst, Hooked_CShadows_StoreShadowToBeRendered,
                   void (char, RwTexture *, RwV3d *, float, float, float, float,
                         __int16, char, char, char, float, char, float, void *,
                         char),
                   0x707C84);

        HOOK_ARGS (inst, Hooked_CShadows_StoreRealTimeShadow,
                   void (CPhysical *, float *, float *, float *, float *,
                         float *, float *),
                   0x706B68);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
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
        auto &&cb, char type, RwTexture *texture, RwV3d *pos, float x1,
        float y1, float x2, float y2, __int16 intensity, char r, char g, char b,
        float zDistance, char bDrawOnWater, float &scale, void *shadowData,
        char bDrawOnBuildings)
    {
        scale = 0.0f;

        cb ();
    }

    static void
    Hooked_CShadows_StoreRealTimeShadow (auto &&cb, CPhysical *thisPhysical,
                                         float *pposx, float *pposy, float *px1,
                                         float *py1, float *px2, float *py2)
    {
        if (thisPhysical->m_nType == ENTITY_TYPE_PED) return;

        cb ();
    }
};

DEFINE_EFFECT (WhereIsEverybodyEffect, "effect_where_is_everybody", 0);