#include "EffectHandler.h"

#include "util/Config.h"
#include "util/EffectDatabase.h"
#include "util/EffectInstance.h"
#include "util/Globals.h"

#include <thread>

#include <CAudioEngine.h>
#include <CMenuManager.h>

void
EffectHandler::SetupCountdownThread ()
{
    std::thread countdownThread (
        []
        {
            while (true)
            {
                if (FrontEndMenuManager.m_bMenuActive) continue;

                // This isn't 100% accurate but this way all effects tick down
                // at the exact same time
                std::this_thread::sleep_for (std::chrono::milliseconds (1000));

                for (auto &effect : effects)
                    effect.TickDownRemaining (1000 * Globals::effectTimerSpeed);
            }
        });

    countdownThread.detach ();
}

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
    if (effects.size () > NUM_RECENT_EFFECTS)
    {
        auto begin = std::begin (effects);
        auto end   = std::end (effects);

        // Remove effects past X effects
        std::advance (begin, NUM_RECENT_EFFECTS);

        effects.erase (std::remove_if (begin, end,
                                       [] (EffectInstance &effect)
                                       { return !effect.IsRunning (); }),
                       end);

        if (effects.size () <= NUM_RECENT_EFFECTS) return;

        // If we still have more than X effects running
        int toRemove = effects.size () - NUM_RECENT_EFFECTS;

        typedef std::deque<EffectInstance>::reverse_iterator rev_itr;
        rev_itr it = effects.rbegin ();
        while (it != effects.rend ())
        {
            if (!it->IsRunning ())
            {
                ++it;
                it = rev_itr (effects.erase (it.base ()));

                if (--toRemove <= 0) break;
            }
            else
            {
                ++it;
            }
        }
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

        if (data.contains ("subtext")) inst.SetSubtext (data["subtext"]);

        if (Config::GetOrDefault ("Chaos.PlayEffectSound", true))
        {
#ifdef GTASA
            AudioEngine.ReportFrontendAudioEvent (0x20, 0.0f, 1.0f);
#endif
        }

        inst.Enable ();
        inst.Tick ();

        RemoveStaleEffects ();
        effects.push_front (std::move (inst));

        // If more than 5 effects and first effect is not a OneTime Effect
        if (effects.size () > 5 && effects[0].GetEffectDuration () != 0)
        {
            RemoveStaleEffects ();
        }
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
