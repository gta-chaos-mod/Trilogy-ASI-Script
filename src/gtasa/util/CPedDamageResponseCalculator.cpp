#include "CPedDamageResponseCalculator.h"

void
CPedDamageResponseCalculator::AccountForPedArmour (CPed    *ped,
                                                   uint8_t *cDamageResponseInfo)
{
    plugin::CallMethod<0x4AD550, CPedDamageResponseCalculator *> (
        this, ped, cDamageResponseInfo);
}

void
CPedDamageResponseCalculator::ComputeWillKillPed (CPed    *ped,
                                                  uint8_t *cDamageResponseInfo,
                                                  bool     bSpeak)
{
    plugin::CallMethod<0x4B3210, CPedDamageResponseCalculator *> (
        this, ped, cDamageResponseInfo, bSpeak);
}
