#include "EffectHandler.h"
#include "util/EffectDatabase.h"

void
EffectHandler::Tick ()
{
    if (GetAsyncKeyState (VK_F7) < 0)
    {
        HandleFunction ("effect_box", "?");
    }

    EmptyQueue ();

    for (auto &effect : effects)
    {
        effect.Tick ();
    }

    effects.remove_if ([] (EffectInstance &effect)
        {
            if (!effect.IsRunning ())
            {
                effect.End ();
                return true;
            }

            return false;            
        });
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

template <typename _Callable, typename... _Args>
void
EffectHandler::QueueFunction (_Callable &&__f, _Args &&... __args)
{
    effectQueue.push (std::bind (std::forward<_Callable> (__f),
                                 std::forward<_Args> (__args)...));
}

void
EffectHandler::QueueEffect (EffectBase *effect, bool executeNow, int duration,
                            std::string_view twitchVoter,
                            std::string_view description)
{
    if (!effect)
    {
        return;
    }

#if (0)
    if (Config::GetOrDefault ("CrowdControl.Enabled", false))
    {
        if (GenericUtil::IsMenuActive ()
            || !GameUtil::CanCrowdControlEffectActivate ())
        {
            NamedPipe::SendCrowdControlResponse (effect->GetCrowdControlID (),
                                                 2);
            return;
        }
    }
#endif

    auto effectFunction = [=] () {
#if (0)
        if (!effect->CanActivate ()
            && Config::GetOrDefault ("CrowdControl.Enabled", false))
        {
            NamedPipe::SendCrowdControlResponse (effect->GetCrowdControlID (),
                                                 2);
            return;
        }
        
        // If an effect with the same type or description is found, disable it,
        // then add the effect and tick it down to start it
        auto it
            = std::find_if (effects.begin (), effects.end (),
                            [effect] (EffectBase *_effect) {
                                if (_effect->IsEnabled ()
                                    || (!_effect->IsEnabled ()
                                        && _effect->CanTickWhenDisabled ())
                                    || _effect->IsDisabledByOtherEffect ()
                                    || (!_effect->IsEnabled ()
                                        && _effect->IsDisabledForMissions ()))
                                {
                                    return effect->IsEqual (_effect);
                                }
                                return false;
                            });

        if (it != effects.end ())
        {
            EffectBase *effect = *it;
            if (effect)
            {
                if (Config::GetOrDefault ("CrowdControl.Enabled", false))
                {
                    NamedPipe::SendCrowdControlResponse (
                        effect->GetCrowdControlID (), 2);
                    return;
                }
                effect->DisableByOtherEffect ();
            }
        }

        NamedPipe::SendCrowdControlResponse (effect->GetCrowdControlID (), 1);
#endif

        
        effects.push_front (effect->CreateInstance());
        auto &inst = effects.back ();

        inst.Start ();
        inst.Tick ();
        inst.SetDuration (duration);
        inst.SetTwitchVoter (twitchVoter);
    };

    if (executeNow)
    {
        effectFunction ();
    }
    else
    {
        QueueFunction (effectFunction);
    }
}

void
EffectHandler::HandleFunction (std::string state, std::string text)
{
    // TODO: GET THESE WITH JSON/WS
    std::string function;
    std::string description;
    std::string voter;

    bool rapid_fire       = 0;
    int  crowd_control_id = -1;
    int  duration         = 0;

    EffectBase *effect = nullptr;
    if (state == "other")
    {
        if (function == "clear_active_effects")
        {
            QueueFunction ([duration, description, voter, rapid_fire] {
                for (auto &effect : effects)
                {
                    effect.Disable ();
                }
            });

            // TODO: Implement EffectPlaceholder
            // effect = new EffectPlaceholder ("clear_active_effects");
        }
    }
    else
    {
        effect = EffectDatabase::FindEffectById (state);
    }
    assert (effect);

    if (effect)
    {
        if (rapid_fire)
            duration = std::min (effect->GetMetadata ().duration, duration);

#if (0)
        if (crowd_control_id > -1)
        {
            effect->SetCrowdControlID (crowd_control_id);
            if (!Config::GetOrDefault ("CrowdControl.Enabled", false))
            {
                NamedPipe::SendCrowdControlResponse (
                    effect->GetCrowdControlID (), 2);
                return;
            }
        }
#endif

        QueueEffect (effect, false, duration, voter, description);
    }

#if (0)
    char c_function[128]    = {};
    int  duration           = 0;
    char c_description[128] = {};
    char c_voter[64]        = {};
    int  rapid_fire         = 0;
    int  crowd_control_id   = -1;
    sscanf (text.c_str (), "%[^:]:%d:%[^:]:%[^:]:%d:%d", &c_function, &duration,
            &c_description, &c_voter, &rapid_fire, &crowd_control_id);

    if (rapid_fire == 1)
    {
        duration = 1000 * 15; // 15 Seconds
    }

    const std::string function (c_function);
    const std::string description (c_description);
    const std::string voter (c_voter);

    EffectBase *effect = nullptr;
    if (state == "other")
    {
        if (function == "clear_active_effects")
        {
            QueueFunction ([duration, description, voter, rapid_fire] {
                for (EffectBase *effect : effects)
                {
                    effect->Disable ();
                }
            });
            effect = new EffectPlaceholder ("clear_active_effects");
        }
    }
    else
    {
        effect = EffectHandler::Get (state, function);
    }

    if (effect)
    {
        effect->SetDescription (description);
        if (rapid_fire)
        {
            effect->SetEffectDuration (
                std::min (effect->GetEffectDuration (), duration));
        }
        effect->SetDuration (duration);
        effect->SetTwitchVoter (voter);

        if (crowd_control_id > -1)
        {
            effect->SetCrowdControlID (crowd_control_id);
            if (!Config::GetOrDefault ("CrowdControl.Enabled", false))
            {
                NamedPipe::SendCrowdControlResponse (
                    effect->GetCrowdControlID (), 2);
                return;
            }
        }

        QueueEffect (effect);
    }
#endif
    
}
