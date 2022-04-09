#pragma once

#include <string>
#include <memory>

class EffectBase;

struct EffectInstance
{
  EffectBase* effect;
  
  std::string overrideName;
  std::string twitchVoter;
  std::string description;

  int crowdControlID = -1;

  int remaining = 0;
  int duration = 0;

  std::shared_ptr<void*> customData;

  EffectInstance (EffectBase* effect);

  EffectInstance (const EffectInstance &other) = delete;
  EffectInstance (EffectInstance &&other) = default;

  void SetDuration (int duration) 
  {
      this->duration = remaining = duration;
  };

  void
  SetTwitchVoter (std::string_view voter)
  {
      twitchVoter = voter;
  };

  void
  OverrideName (std::string_view name)
  {
      overrideName = name;
  };

  void
  SetDescription (std::string_view description)
  {
      this->description = description;
  };

  bool
  IsRunning ()
  {
      return true;
  };

  std::string_view GetName ();

  void Start ();
  void End ();
  void Tick ();

  void
  Disable ()
  {
      SetDuration (0);
      End ();
  };
};
