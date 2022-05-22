#include "util/CPedDamageResponseCalculator.h"
#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <CStreaming.h>

class CopsEverywhereEffect : public EffectBase
{
    static inline int  randomPedModel   = 280;
    static inline bool generateNewModel = false;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        randomPedModel   = 280;
        generateNewModel = false;

        HOOK_ARGS (inst, Hooked_CPopulation_AddPed,
                   CPed * (ePedType, int, CVector *, bool), 0x613B7F, 0x613ECD,
                   0x613F24, 0x6142FB, 0x614D26, 0x614D79, 0x6153AB, 0x616598,
                   0x6E29B6, 0x6F3D03, 0x612DFE, 0x5FD629, 0x5FD176, 0x5FCBEC,
                   0x5FCB0D, 0x59676F, 0x594FD7, 0x594D48, 0x48C8AA);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (!generateNewModel) return;

        randomPedModel   = inst->Random (280, 288);
        generateNewModel = false;
    }

    static CPed *
    Hooked_CPopulation_AddPed (auto &&cb, ePedType &pedType, int &modelIndex,
                               CVector *position, bool a4)
    {
        pedType          = PED_TYPE_COP;
        modelIndex       = randomPedModel;
        generateNewModel = true;

        CStreaming::RequestModel (modelIndex, 2);
        CStreaming::LoadAllRequestedModels (false);

        return cb ();
    }
};

DEFINE_EFFECT (CopsEverywhereEffect, "effect_cops_everywhere", 0);