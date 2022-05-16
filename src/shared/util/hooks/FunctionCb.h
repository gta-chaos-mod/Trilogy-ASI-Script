#pragma once

enum Types
{
    TYPE_NORMAL,
    TYPE_METHOD,
    TYPE_STD
};

/*******************************************************/
/** SFINAE wrapper to generate proper trampoline for x86 thiscall  hooks
 **/
template <Types HookType, typename Ret, typename... Args>
struct FunctionCbTrampoline
{
    template <auto &info>
    static Ret
    Trampoline (Args... args)
    {
        return info.WalkTree (args...);
    }

    static Ret
    Call (uintptr_t addr, std::tuple<Args...> &params)
    {
        using FuncType = Ret (*) (Args...);
        return std::apply (reinterpret_cast<FuncType> (addr), params);
    }
};

template <typename Ret, typename Arg1, typename... Args>
struct FunctionCbTrampoline<TYPE_METHOD, Ret, Arg1, Args...>
{
    std::tuple<Args...> params;

    template <auto &info>
    static Ret __fastcall Trampoline (Arg1 arg1, void *edx, Args... args)
    {
        return info.WalkTree (arg1, args...);
    }

    static Ret
    Call (uintptr_t addr, std::tuple<Arg1, Args...> &params)
    {
        using FuncType = Ret (__thiscall *) (Arg1, Args...);
        return std::apply (reinterpret_cast<FuncType> (addr), params);
    }
};

template <typename Ret, typename... Args>
struct FunctionCbTrampoline<TYPE_STD, Ret, Args...>
{
    template <auto &info> static Ret __stdcall Trampoline (Args... args)
    {
        return info.WalkTree (args...);
    }

    static Ret
    Call (uintptr_t addr, std::tuple<Args...> &params)
    {
        using FuncType = Ret (__stdcall *) (Args...);
        return std::apply (reinterpret_cast<FuncType> (addr), params);
    }
};
/*******************************************************/

template <Types Method, typename Prototype> struct FunctionCb;

/** Function Callback class for use with HookManager. The class handles calling
 * all the functions in the call tree and the original function in the end.

 The callback functions take FunctionCb as the only parameter and can modify the
 parameters using the `params` member.

 Usage: FunctionCb<method, void(int, int)>

 - Method: boolean to represent whether the function is a method (__thiscall) or
   not.
 **/

template <Types HookType, typename Ret, typename... Args>
struct FunctionCb<HookType, Ret (Args...)>
    : public FunctionCbTrampoline<HookType, Ret, Args...>
{
    using EventCbType  = std::function<void (Args...)>;
    using CbType       = std::function<Ret (FunctionCb &)>;
    using TreeType     = std::list<CbType>;
    using TreeIterator = typename TreeType::const_iterator;

    std::tuple<Args...> params;
    TreeIterator        it;
    TreeIterator        end;
    uintptr_t           origFunction;

    FunctionCb (std::tuple<Args...> params, TreeIterator it, TreeIterator end,
                uintptr_t origFunction)
        : params (params), it (it), end (end), origFunction (origFunction)
    {
    }

    struct HookInfo
    {
        TreeType &s_CallTree;
        uintptr_t s_OriginalFunction;

        Ret
        WalkTree (Args... args)
        {
            FunctionCb cb{std::forward_as_tuple (args...),
                          std::begin (s_CallTree), std::end (s_CallTree),
                          s_OriginalFunction};
            return cb ();
        }
    };

    Ret
    operator() ()
    {
        if (it == end) { return this->Call (origFunction, params); }

        return (*(it++)) (*this);
    }
};
