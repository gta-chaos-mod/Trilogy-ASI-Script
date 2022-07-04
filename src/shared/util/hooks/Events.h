#pragma once

#include "util/EffectInstance.h"
#include "util/hooks/HookManager.h"

#include <list>

template <typename Prototype, bool Method, auto... Addresses> class Event
{
    static inline bool enabled;

public:
    using FunctionCb = FunctionCb<Method, Prototype>;
    using HookManagerType
        = HookManagerMulti<AutomaticHook, FunctionCb, Addresses...>;
    using Callback = typename FunctionCb::EventCbType;

    static void
    Enable ()
    {
        if (!enabled)
        {
            HookManagerType::Add (Trampoline);
            enabled = true;
        }
    }

    static auto
    Trampoline (FunctionCb &cb)
    {
        for (auto &func : before.callbacks)
            std::apply (func, cb.params);

        auto ret = cb ();

        for (auto &func : after.callbacks)
            std::apply (func, cb.params);

        return ret;
    }

    class FunctionList
    {
        std::list<Callback> callbacks;

    private:
        auto
        Add (Callback cb)
        {
            Enable ();
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
        operator+= (std::pair<EffectInstance *, Callback> cb)
        {
            Add (cb.first, cb.second);
        }
    } static inline before, after;

    static void
    Add (std::pair<EffectInstance *, Callback> cb)
    {
        before += cb;
    }
};
