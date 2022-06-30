#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

class LowLODVehiclesEffect : public EffectBase
{
    static inline float &ms_vehicleLod0RenderMultiPassDist
        = *(float *) 0xC88044;
    static inline float &ms_vehicleLod0Dist    = *(float *) 0xC88040;
    static inline float &ms_vehicleLod1Dist    = *(float *) 0xC8803C;
    static inline float &ms_bigVehicleLod0Dist = *(float *) 0xC88038;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK (inst, Hooked_SetRenderWareCamera, RwV3d * (RwCamera *), 0x53D714,
              0x53D7DF, 0x53D986, 0x53E7F0, 0x53EB4F);
    }

    static RwV3d *
    Hooked_SetRenderWareCamera (auto &&cb)
    {
        RwV3d *ret = cb ();

        ms_vehicleLod0RenderMultiPassDist = -1;
        ms_vehicleLod0Dist                = -1;
        ms_vehicleLod1Dist                = -1;
        ms_bigVehicleLod0Dist             = -1;

        return ret;
    }
};

DEFINE_EFFECT (LowLODVehiclesEffect, "effect_low_lod_vehicles", 0);