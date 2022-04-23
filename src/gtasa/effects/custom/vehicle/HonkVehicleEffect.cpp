#include "util/EffectBase.h"

// TODO: Hook PlayHornOrSiren
// HookCall (0x500366, HookedPlayHornOrSiren);

/*

char __fastcall HookedPlayHornOrSiren (
    CAEVehicleAudioEntity *thisAudioEntity, void *edx, char counter,
    char sirenOrAlarm, char playHorn, cVehicleParams *data)
{
    bool siren    = thisAudioEntity->m_bModelWithSiren;
    int  _counter = siren ? 0 : 1;
    return CallMethodAndReturn<char, 0x4F99D0, CAEVehicleAudioEntity *> (
        thisAudioEntity, _counter, siren, false, data);
}

*/

class HonkVehicleEffect : public EffectBase
{
public:
    void
    OnEnd (EffectInstance *inst) override
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            vehicle->m_vehicleAudio.field_BE               = true;
            vehicle->m_vehicleAudio.m_bSirenOrAlarmPlaying = true;
            vehicle->m_vehicleAudio.m_bHornPlaying         = false;
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
            vehicle->m_nHornCounter = 1;
    }
};

DEFINE_EFFECT (HonkVehicleEffect, "effect_honk_vehicle", 0);