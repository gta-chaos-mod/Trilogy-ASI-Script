#pragma once

#include <queue>
#include <list>
#include <string_view>

#include "EffectBase.h"

class EffectHandler
{
    inline static std::queue<std::function<void ()>> effectQueue;
    inline static std::list<EffectInstance> effects;

public:

    static void Tick ();

    static void EmptyQueue ();

    template <typename _Callable, typename... _Args>
    static void QueueFunction (_Callable &&__f, _Args &&... __args);

    static void QueueEffect (EffectBase *effect, bool executeNow, int duration,
                             std::string_view twitchVoter,
                             std::string_view description);

    static void HandleFunction (std::string state, std::string text);
    
    const std::list<EffectInstance> &
    GetActiveEffects ()
    {
        return effects;
    };
};
