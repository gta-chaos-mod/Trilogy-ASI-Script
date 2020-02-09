#pragma once

#include "plugin.h"

#include <queue>

#include "EffectBase.h"
#include "util/EffectHandler.h"

class EffectDatabase
{
private:
    static std::queue<std::function<void ()>> effectQueue;
    static std::list<EffectBase *>            effects;

public:
    static void Tick ();

    static void EmptyQueue ();

    template <typename _Callable, typename... _Args>
    static void QueueFunction (_Callable &&__f, _Args &&... __args);

    static void QueueEffect (EffectBase *effect, bool executeNow = false);

    static void HandleFunction (std::string state, std::string text);

    static std::list<EffectBase *> GetActiveEffects ();
};
