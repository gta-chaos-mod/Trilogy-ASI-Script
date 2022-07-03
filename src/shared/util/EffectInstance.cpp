#include "EffectInstance.h"

#include "util/EffectBase.h"
#include "util/EffectHandler.h"
#include "util/GenericUtil.h"
#include "util/Globals.h"

EffectInstance::EffectInstance (EffectBase *effect) : effect (effect) {}

void
EffectInstance::Start ()
{
    if (this->effect) this->effect->OnStart (this);
}

void
EffectInstance::End ()
{
    cleanupHandler.DoCleanup ();
    if (this->effect) this->effect->OnEnd (this);

    EffectHandler::RemoveStaleEffect (this);
}

void
EffectInstance::Tick ()
{
    int tick
        = (int) round (GenericUtil::CalculateTick (Globals::effectTimerSpeed));
    this->remaining -= tick;

    if (GetEffectRemaining () < 0) Disable ();

    if (effect && isRunning) effect->OnTick (this);
}

void
EffectInstance::ProcessScripts ()
{
    if (effect && isRunning) effect->OnProcessScripts (this);
}

std::string_view
EffectInstance::GetName () const
{
    if (effect && overrideName.length () == 0)
        return effect->GetMetadata ().name;

    return overrideName;
}

bool
EffectInstance::IsOtherEffectIncompatible (const EffectInstance &other)
{
    if (!this->effect) return false;

    auto &thisMetadata  = this->effect->GetMetadata ();
    auto &otherMetadata = other.effect->GetMetadata ();

    // Check for equal id
    if (thisMetadata.id == otherMetadata.id) return true;

    // Check for common groups
    if ((thisMetadata.groups & otherMetadata.groups).any ()) return true;

    // Check for same description/name (old Chaos code did as well)
    if (this->GetName () == other.GetName ()) return true;

    return false;
}
