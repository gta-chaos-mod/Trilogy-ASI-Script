#pragma once

#include "util/Hooks/HookManager.h"
#include "util/EffectInstance.h"
#include <list>

template <typename Prototype, bool Method, auto... Addresses> class Event
{
public:
    using FunctionCb = FunctionCb<Method, Prototype>;
    using HookManagerType
        = HookManagerMulti<AutomaticHook, FunctionCb, Addresses...>;
    using Callback = typename FunctionCb::EventCbType;

    class FunctionList
    {
        std::list<Callback> callbacks;

    private:
        auto
        Add (Callback cb)
        {
            return callbacks.insert (std::end (callbacks), cb);
        }

        void
        Remove (Callback cb)
        {
            callbacks.erase (cb);
        }

        void
        Add (EffectInstance *inst, Callback cb)
        {
            auto it = Add (cb);
            inst->GetCleanupHandler ().AddFunction ([it, this]
                                                    { Remove (it); });
        }

        void
        operator+= (std::pair<EffectInstance, Callback> cb)
        {
            Add (cb.first, cb.second);
        }
    } inline static before, after;
};
