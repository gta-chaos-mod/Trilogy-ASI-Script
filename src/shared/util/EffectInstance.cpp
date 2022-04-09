#include "EffectInstance.h"
#include "EffectBase.h"

#include <CTheScripts.h>

EffectInstance::EffectInstance (EffectBase *effect) : effect (effect)
{
}

void
EffectInstance::Start ()
{
    if (this->effect)
        this->effect->OnStart (this);
}

void
EffectInstance::End ()
{
    if (this->effect)
        this->effect->OnEnd (this);
}

void
EffectInstance::Tick ()
{
#if (0)
    this->missionInfo.isPlayerOnAMission = CTheScripts::IsPlayerOnAMission ();
    if (!IsInitialized ())
    {
        Initialize ();
    }

    if (GetRemaining () > 1000)
    {
        this->drawInfo.offset
            = std::min (this->drawInfo.offset + CalculateTick (0.0015f), 1.0f);
    }
    else
    {
        this->drawInfo.offset
            = std::max (0.0f, this->drawInfo.offset - CalculateTick (0.0015f));
    }

    int tick = CalculateTick ();
    this->baseInfo.remaining -= tick;
    if (GetEffectRemaining () >= 0)
    {
        this->baseInfo.effectRemaining -= tick;

        if (this->drawInfo.textColorTick >= 0)
        {
            this->drawInfo.textColorTick -= tick;

            this->drawInfo.textColorHighlight
                = (this->drawInfo.textColorTick / 400) % 2;
        }

        if (this->baseInfo.disabledByOtherEffect)
        {
            return;
        }

        if (this->baseInfo.effectRemaining <= 0)
        {
            Disable ();
            return;
        }

        if (IsEnabled () || CanTickWhenDisabled ())
        {
            if (this->missionInfo.disabledForMissions)
            {
                if (this->missionInfo.isPlayerOnAMission
                    && !this->missionInfo.wasPlayerOnAMission)
                {
                    Disable ();
                    this->missionInfo.wasPlayerOnAMission
                        = this->missionInfo.isPlayerOnAMission;
                    return;
                }
            }

            if (effect)
                effect->OnTick ();
        }
        else if (this->missionInfo.disabledForMissions)
        {
            if (!this->missionInfo.isPlayerOnAMission
                && this->missionInfo.wasPlayerOnAMission)
            {
                Enable ();
            }
        }
    }
    else if (IsEnabled ())
    {
        Disable ();
    }

    this->missionInfo.wasPlayerOnAMission
        = this->missionInfo.isPlayerOnAMission;
#else
    if (effect)
        effect->OnTick (this);
#endif
}

std::string_view
EffectInstance::GetName ()
{
    if (effect && overrideName.length () == 0)
        return effect->GetMetadata ().name;

    return overrideName;
}
