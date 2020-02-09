#include "HookDatabase.h"

void
HookDatabase::HookCall (std::string id, int address, void *func, bool vp)
{
    if (id == "_")
    {
        injector::MakeCALL (GetGlobalAddress (address), func, vp);
        return;
    }

    if (registeredHooks ().contains (address))
    {
        RestoreHook (registeredHooks ()[address]);
        registeredHooks ().erase (address);
    }
    registeredHooks ()[address]
        = HookElement (id, address,
                       injector::MakeCALL (GetGlobalAddress (address), func,
                                           vp),
                       true);
}

void
HookDatabase::HookJump (std::string id, int address, void *func, bool vp)
{
    if (id == "_")
    {
        injector::MakeJMP (GetGlobalAddress (address), func, vp);
        return;
    }

    if (registeredHooks ().contains (address))
    {
        RestoreHook (registeredHooks ()[address]);
        registeredHooks ().erase (address);
    }
    registeredHooks ()[address]
        = HookElement (id, address,
                       injector::MakeJMP (GetGlobalAddress (address), func, vp),
                       false);
}

void
HookDatabase::RestoreHook (HookElement hook)
{
    if (hook.isCall)
    {
        injector::MakeCALL (GetGlobalAddress (hook.address), hook.pointer);
    }
    else
    {
        injector::MakeJMP (GetGlobalAddress (hook.address), hook.pointer);
    }
}

void
HookDatabase::RestoreHooks (std::string id)
{
    for (auto it = registeredHooks ().cbegin ();
         it != registeredHooks ().cend ();)
    {
        if (id == it->second.id)
        {
            RestoreHook (it->second);
            it = registeredHooks ().erase (it);
        }
        else
        {
            ++it;
        }
    }
}
