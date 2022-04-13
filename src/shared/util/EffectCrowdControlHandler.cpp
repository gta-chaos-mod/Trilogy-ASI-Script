#include "EffectCrowdControlHandler.h"
#include "util/GenericUtil.h"
#include "util/Config.h"

#include "util/EffectBase.h"
#include "util/Websocket.h"

#ifdef GTASA
#include "util/GameUtil.h"
#endif

bool
EffectCrowdControlHandler::IsCrowdControlEnabled ()
{
    return Config::GetOrDefault ("CrowdControl.Enabled", false);
}

void
EffectCrowdControlHandler::Initialise (const nlohmann::json &data)
{
    if (data.contains ("crowdControlData"))
        crowdControlId = data["crowdControlData"].value ("id", -1);
}

bool
EffectCrowdControlHandler::HandleOnQueue () const
{
    if (!*this)
        return true;

    // TODO: GameUtil for GTA3/VC Maybe? :eyes:
    if (GenericUtil::IsMenuActive ()
#ifdef GTASA
        || GameUtil::CanCrowdControlEffectActivate ()
#endif
    )
        return SendRetry (), false;

    return true;
}

bool
EffectCrowdControlHandler::HandleOnAddEffect (EffectBase *effect) const
{
    if (*this && !effect->CanActivate ())
    {
        SendRetry ();
        return false;
    }

    return true;
}

bool
EffectCrowdControlHandler::HandleOnEffectIncompatibility () const
{
    if (*this)
    {
        SendRetry ();
        return false;
    }

    return true;
}

bool
EffectCrowdControlHandler::HandleOnEffectActivated () const
{
    if (*this)
        SendSucceeded ();

    return true;
}

void
EffectCrowdControlHandler::SendRetry () const
{
    Websocket::SendCrowdControlResponse (crowdControlId, 2);
}

void
EffectCrowdControlHandler::SendSucceeded () const
{
    Websocket::SendCrowdControlResponse (crowdControlId, 1);
}
