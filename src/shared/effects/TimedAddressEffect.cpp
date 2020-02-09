#include "TimedAddressEffect.h"

TimedAddressEffect::TimedAddressEffect (std::string id, int address)
    : EffectBase (id)
{
    if (address)
    {
        this->address = reinterpret_cast<bool *> (address);
    }
}

void
TimedAddressEffect::Disable ()
{
    if (address && *address)
    {
        *address = false;
    }

    EffectBase::Disable ();
}

void
TimedAddressEffect::HandleTick ()
{
    EffectBase::HandleTick ();

    if (address && !*address)
    {
        *address = true;
    }
}
