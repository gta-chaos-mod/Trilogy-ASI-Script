#pragma once

#include "util/hooks/FunctionCb.h"
#include "util/hooks/HookTypes.h"

#include <cstdint>
#include <functional>
#include <map>
#include <tuple>
#include <type_traits>
#include <vector>

/** Hook Manager to handle multiple hooks of the same function. Hooks are
    executed in order they were added.

 Usage:
 HookManagerMain<HookType, FunctionCb<...>, address>::Add(...);

 The Add function returns an iterator that can then be used to remove the hook.

**/
template <template <auto> class Hook, auto Address, typename Callback>
struct HookManagerMain
{
    static uintptr_t
    GetAddress ()
    {
        if constexpr (std::is_invocable_v<decltype (Address)>)
        {
            return Address ();
        }
        else
        {
            return Address;
        }
    }

    inline static typename Callback::TreeType sm_CallTree;

public:
    using CbType = Callback;

    static typename Callback::TreeIterator
    Add (typename Callback::CbType func)
    {
        if (sm_CallTree.size () == 0) Enable ();

        return sm_CallTree.insert (std::end (sm_CallTree), func);
    }

    static void
    Remove (typename Callback::TreeIterator it)
    {
        sm_CallTree.erase (it);

#ifdef HOOK_MANAGER_DISABLE_ON_EMPTY_CALL_TREE
        if (sm_CallTree.size () == 0) Disable ();
#endif
    }

    static void
    Enable ()
    {
        static typename Callback::HookInfo hookInfo{sm_CallTree};

        Hook<Address>::template Enable (GetAddress (),
                                        Callback::template Trampoline<hookInfo>,
                                        hookInfo.s_OriginalFunction);
    }

    static void
    Disable ()
    {
        Hook<Address>::template Disable (GetAddress ());
    }
};

/** Hook Manager to handle hooks to multiple addresses with the same hook type
 * and callback

 Usage:
 HookManagerMulti<HookType, FunctionCb<...>, address1, address2>::Add(...);

**/

template <template <auto> class Hook, typename Callback, auto... Address>
struct HookManagerMulti
{
    using CbType = Callback;

    inline static std::list<std::vector<typename Callback::TreeIterator>>
        s_Iterators;

    static auto
    Add (typename Callback::CbType func)
    {
        std::vector<typename Callback::TreeIterator> iterators;

        (..., iterators.push_back (
                  HookManagerMain<Hook, Address, Callback>::Add (func)));

        return s_Iterators.insert (std::end (s_Iterators),
                                   std::move (iterators));
    }

    static void
    Remove (typename decltype (s_Iterators)::iterator it)
    {
        int i = 0;
        (..., HookManagerMain<Hook, Address, Callback>::Remove ((*it)[i++]));
    }
};
