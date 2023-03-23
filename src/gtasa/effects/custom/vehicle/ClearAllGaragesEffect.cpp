#include "util/EffectBase.h"

namespace
{
int garagesOffset[]
    = {0x96ABD8, 0x96AC18, 0x96AC58, 0x96AC98, 0x96ACD8, 0x96AD18, 0x96AD58,
       0x96AD98, 0x96ADD8, 0x96AE18, 0x96AE58, 0x96AE98, 0x96AED8, 0x96AF18,
       0x96AF58, 0x96AF98, 0x96AFD8, 0x96B018, 0x96B058, 0x96B098, 0x96B0D8,
       0x96B118, 0x96B158, 0x96B198, 0x96B1D8, 0x96B218, 0x96B258, 0x96B298,
       0x96B2D8, 0x96B318, 0x96B358, 0x96B398, 0x96B3D8, 0x96B418, 0x96B458,
       0x96B498, 0x96B4D8, 0x96B518, 0x96B558, 0x96B598, 0x96B5D8, 0x96B618,
       0x96B658, 0x96B698, 0x96B6D8, 0x96B718, 0x96B758, 0x96B798, 0x96BAD8,
       0x96BB18, 0x96BB58, 0x96BB98, 0x96BBD8, 0x96BC18, 0x96BC58, 0x96BC98,
       0x96BCD8, 0x96BD18, 0x96BD58, 0x96BD98, 0x96BDD8, 0x96BE18, 0x96BE58,
       0x96BE98, 0x96BED8, 0x96BF18, 0x96BF58, 0x96BF98};

const int GARAGE_MEM_BLOCK_SIZE = 64;
} // namespace

class ClearAllGaragesEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        inst->SetIsOneTimeEffect ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        for (auto address : garagesOffset)
        {
            auto *carId = reinterpret_cast<std::int32_t *> (address + 0x10);

            if (*carId > 0)
            {
                void *p = reinterpret_cast<void *> (address);
                std::memset (p, 0, GARAGE_MEM_BLOCK_SIZE);
            }
        }

        inst->Disable ();
    }
};

DEFINE_EFFECT (ClearAllGaragesEffect, "effect_clear_all_garages", 0);
