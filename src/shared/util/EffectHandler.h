#pragma once

#include "util/EffectBase.h"

#include <list>
#include <queue>
#include <string_view>

class EffectHandler
{
    static inline std::queue<std::function<void ()>> effectQueue;
    static inline std::deque<EffectInstance>         timedEffects;
    static inline std::deque<EffectInstance>         oneTimeEffects;

public:
    static void SetupCountdownThread ();
    static void Tick ();
    static void ProcessScripts ();

    static void EmptyQueue ();

    static int GetActiveEffectCount ();

    static void RemoveStaleEffects (bool checkOneTimeEffects);

    template <typename _Callable, typename... _Args>
    static void QueueFunction (_Callable &&__f, _Args &&...__args);

    static void QueueEffect (EffectBase           *effect,
                             const nlohmann::json &effectData);

    static void HandleFunction (const nlohmann::json &effectData);

    static std::deque<EffectInstance> &
    GetActiveEffects ()
    {
        return timedEffects;
    };

    static std::deque<EffectInstance> &
    GetOneTimeEffects ()
    {
        return oneTimeEffects;
    };

    static void
    Clear ()
    {
        std::deque<EffectInstance> ().swap (timedEffects);
        std::deque<EffectInstance> ().swap (oneTimeEffects);
    };
};
