#include "EffectHandler.h"

#include "util/Config.h"
#include "util/EffectDatabase.h"
#include "util/EffectInstance.h"

#include <CAudioEngine.h>

void
EffectHandler::Tick ()
{
    EmptyQueue ();

    for (auto &effect : effects)
        effect.Tick ();
}

void
EffectHandler::ProcessScripts ()
{
    for (auto &effect : effects)
        effect.ProcessScripts ();
}

void
EffectHandler::EmptyQueue ()
{
    if (!effectQueue.empty ())
    {
        effectQueue.front () ();
        effectQueue.pop ();
    }
}

void
EffectHandler::RemoveStaleEffects ()
{
    if (effects.size () > 5)
    {
        auto begin = std::begin (effects);
        auto end   = std::end (effects);

        std::advance (begin, 5);

        effects.erase (std::remove_if (begin, end,
                                       [] (EffectInstance &effect) {
                                           return !effect.IsShownOnScreen ()
                                                  && !effect.IsRunning ();
                                       }),
                       end);
    }
}

template <typename _Callable, typename... _Args>
void
EffectHandler::QueueFunction (_Callable &&__f, _Args &&...__args)
{
    effectQueue.push (std::bind (std::forward<_Callable> (__f),
                                 std::forward<_Args> (__args)...));
}

void
EffectHandler::QueueEffect (EffectBase *effect, const nlohmann::json &data)
{
    if (!effect) return;

    EffectInstance::SubHandlers_t handlers (data);

    if (!handlers.HandleOnQueue ()) return;

    auto effectFunction = [=] ()
    {
        if (!handlers.HandleOnAddEffect (effect)) return;

        auto inst = effect->CreateInstance ();

        /* Check for incompatibilities before effect activation */
        for (auto &i : effects)
        {
            if (inst.IsOtherEffectIncompatible (i))
            {
                if (!handlers.HandleOnEffectIncompatibility ()) return;

                i.Disable ();
            }
        }

        /* Actually activate the effect */
        if (!handlers.HandleOnEffectActivated ()) return;

        inst.SetSubHandlers (handlers);
        inst.SetDuration (data["duration"]);

        if (data.contains ("effectData"))
            inst.SetCustomData (data["effectData"]);

        if (data.contains ("displayName"))
            inst.OverrideName (data["displayName"]);

        if (Config::GetOrDefault ("Chaos.PlayEffectSound", true))
        {
#ifdef GTASA
            AudioEngine.ReportFrontendAudioEvent (0x20, 0.0f, 1.0f);
#endif
        }

        inst.Enable ();
        inst.Tick ();
        effects.push_front (std::move (inst));

        RemoveStaleEffects ();
    };

    QueueFunction (effectFunction);
}

void
EffectHandler::HandleFunction (const nlohmann::json &effectData)
{
    EffectBase *effect = nullptr;

    effect = EffectDatabase::FindEffectById (effectData.at ("effectID"));

    if (effect) QueueEffect (effect, effectData);
    //     else
    // #ifndef _NDEBUG
    //         MessageBox (NULL, std::string (effectData.at ("effectID")).c_str
    //         (),
    //                     "Effect not found", MB_ICONHAND);
    // #endif
}
