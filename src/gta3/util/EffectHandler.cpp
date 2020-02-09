#include "EffectHandler.h"

EffectBase *
EffectHandler::Get (std::string state, std::string function)
{
    EffectBase *effect = nullptr;

    if (state == "weather")
    {
        effect = new Weather (std::stoi (function));
    }
    else if (state == "spawn_vehicle")
    {
        effect = new SpawnVehicle (std::stoi (function));
    }
    else if (state == "cheat" || state == "timed_cheat")
    {
        effect = HandleCheat (function);
    }
    else if (state == "effect" || state == "timed_effect")
    {
        effect = HandleEffect (function);
    }
    else if (state == "teleport")
    {
        int x, y, z;
        sscanf (function.c_str (), "%d,%d,%d", &x, &y, &z);

        effect = new Teleport (CVector ((float) x, (float) y, (float) z));
    }

    return effect;
}

EffectBase *
EffectHandler::HandleEffect (std::string name)
{
    EffectBase *effect = nullptr;

    if (name == "")
    {
    }

    return effect;
}

EffectBase *
EffectHandler::HandleCheat (std::string name)
{
    EffectBase *effect = nullptr;

    if (name == "")
    {
    }

    return effect;
}
