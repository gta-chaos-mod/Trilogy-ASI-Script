#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

class HonkVehicleEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        HOOK_METHOD_ARGS (inst, Hooked_CAEVehicleAudioEntity_PlayHornOrSiren,
                          char (CAEVehicleAudioEntity *, char, char, char,
                                cVehicleParams *),
                          0x500366);
    }

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
        CPlayerPed *player = FindPlayerPed ();

        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
        {
            if (vehicle->m_pDriver && vehicle->m_pDriver == player) continue;

            vehicle->m_nHornCounter = 1;
        }
    }

    static char
    Hooked_CAEVehicleAudioEntity_PlayHornOrSiren (
        auto &&cb, CAEVehicleAudioEntity *thisAudioEntity, char &counter,
        char &sirenOrAlarm, char mrWhoopie, cVehicleParams *dat)
    {
        sirenOrAlarm = thisAudioEntity->m_bModelWithSiren;
        counter      = sirenOrAlarm ? 0 : 1;

        return cb ();
    }
};

DEFINE_EFFECT (HonkVehicleEffect, "effect_honk_vehicle", 0);