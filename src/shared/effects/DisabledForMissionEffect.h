#pragma once

#include <util/EffectInstance.h>

#include <utility>

#include <CTheScripts.h>

template <typename ChildEffect>
class DisabledForMissionEffect : public ChildEffect
{
    inline static bool prevOnMission = false;

    virtual void
    OnTick (EffectInstance *inst) override
    {
        bool onMission = CTheScripts::IsPlayerOnAMission ();
        inst->SetTimerVisible (!onMission);

        // On Mission State changed from last frame
        if (std::exchange (prevOnMission, onMission) != prevOnMission)
        {
            if (onMission)
                ChildEffect::OnEnd (inst);
            else
                ChildEffect::OnStart (inst);
        }

        if (!onMission) ChildEffect::OnTick (inst);
    }
};