#pragma once

#include <MinHook.h>
#include <injector/hooking.hpp>

template<auto Address, typename T>
struct InjectorHook
{
    inline static T scopedObj;

    static void
    Disable (uintptr_t addr)
    {
        scopedObj.restore ();
    }

    template <typename DstT>
    static void
    Enable (uintptr_t src, DstT dst, uintptr_t &out)
    {
        out = scopedObj.install (src, uintptr_t (dst)).as_int ();
    }
};

template <auto Address>
using CallHook = InjectorHook<Address, injector::scoped_call>;

template <auto Address>
using JmpHook = InjectorHook<Address, injector::scoped_jmp>;

template <auto Address> struct MinHookHook
{
    static void
    Disable (uintptr_t addr)
    {
        MH_RemoveHook (LPVOID (addr));
    }

    template <typename DstT>
    static void
    Enable (uintptr_t src, DstT dst, uintptr_t &out)
    {
        MH_CreateHook (LPVOID (src), LPVOID (dst), (LPVOID*) (&out));
        MH_EnableHook (LPVOID (src));
    }
};

/*** Hook type to automatically detect the type of hook from one of the three:

     1. Branch Instruction Hook - If the given address is a branch instruction
     (call/jmp), redirect the call instruction at that point to the hooked
     function.

     2. MinHook Hook - If the given address is not a branch instruction, then
     MinHook is used to hook the entire function body. (Note there's no check
     for the validty of the address. A hook in the middle of a function is
     unlikely to work.
***/

template <auto Address> struct AutomaticHook
{
    enum class HookType
    {
        CALL,
        JMP,
        MINHOOK
    };

    inline static HookType type;

    static void
    Disable (uintptr_t addr)
    {
        switch (type)
        {
            case HookType::CALL: CallHook<Address>::Disable (addr); break;
            case HookType::JMP: JmpHook<Address>::Disable (addr); break;
            case HookType::MINHOOK: MinHookHook<Address>::Disable (addr); break;
        }
    }

    static void
    InitialiseType (uintptr_t src)
    {
        uint8_t opcode = injector::ReadMemory<uint8_t> (src);

        switch (opcode)
        {
            case 0xE8: type = HookType::CALL; break;
            case 0xE9: type = HookType::JMP; break;
            default: type = HookType::MINHOOK; break;
        }
    }

    template <typename DstT>
    static void
    Enable (uintptr_t src, DstT dst, uintptr_t &out)
    {
        InitialiseType (src);

        switch (type)
        {
            case HookType::CALL:
                CallHook<Address>::Enable (src, dst, out);
                break;

            case HookType::JMP:
                JmpHook<Address>::Enable (src, dst, out);
                break;

            case HookType::MINHOOK:
                MinHookHook<Address>::Enable (src, dst, out);
                break;
        }
    }
};
