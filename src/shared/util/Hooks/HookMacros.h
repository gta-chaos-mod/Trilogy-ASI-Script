#pragma once

#include "HookManager.h"

/**
   Helpful Macros for using with HookManager to encapsulate verbose parts of the
   hook manager templates.

   Usage:
   DEFINE_HOOK(<name>, (<address(es)>), <true for thiscall>, <function
   prototype>);

   =================
   1. Single function:
   =================
   DEFINE_HOOK(NameOfTheHook, (address1, address2), false, void(int,int))
   {
       auto& [param1, param2] = cb.params;
       ...
       return cb ();
   }
   ENABLE_HOOK(inst, NameOfTheHook);

   ================
   2. Multiple/std::bind functions:
   ================
   DECLARE_HOOK(NameOfTheHook, (address1, address2), false, void(int,int));

   void ExampleFunction(HOOK_PARAMS(NameOfTheHook))
   {
       auto& [param1, param2] = cb.params;
       // ...
       return cb ();
   }
   ADD_TO_HOOK (NameOfTheHook, ExampleFunction);
   ADD_TO_HOOK (NameOfTheHook, [] (auto&& cb) {
       std::get<0>(cb.params) = 2; cb();
   });
 */

// Utility Macros
#define HOOK_CLASS(name) name##_h
#define ADDRESS_LIST(...) __VA_ARGS__
#define HOOK_PARAMS(name) HOOK_CLASS (name)::CbType &cb

// Macros for defining hook types
#define DECLARE_HOOK(name, prototype, method, ...)                             \
    using HOOK_CLASS (name)                                                    \
        = HookManagerMulti<AutomaticHook, FunctionCb<method, prototype>,       \
                           __VA_ARGS__>

#define DEFINE_HOOK(name, prototype, method, ...)                              \
    DECLARE_HOOK (name, prototype, method, __VA_ARGS__);                       \
    static void name (HOOK_PARAMS (name))

// Hooks for using hooks
#define ADD_TO_HOOK_(function, name) HOOK_CLASS (name)::Add (function);

#define ADD_TO_HOOK(function, inst, name)                                      \
    {                                                                          \
        auto it = ADD_TO_HOOK_ (function, name);                               \
        inst->GetCleanupHandler ().AddFunction (                               \
            [it] { HOOK_CLASS (name)::Remove (it); });                         \
    }
#define ENABLE_HOOK(inst, name) ADD_TO_HOOK (name, inst, name)

#define HOOK(inst, func, prototype, ...)                                       \
    {                                                                          \
        DECLARE_HOOK (hook, prototype, false, __VA_ARGS__);                    \
        ADD_TO_HOOK ([] (auto &&cb) { return func (cb); }, inst, hook);        \
    }

#define HOOK_METHOD(inst, func, prototype, ...)                                \
    {                                                                          \
        DECLARE_HOOK (hook, prototype, true, __VA_ARGS__);                     \
        ADD_TO_HOOK ([] (auto &&cb) { return func (cb); }, inst, hook);        \
    }
