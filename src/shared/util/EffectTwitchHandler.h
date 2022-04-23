#pragma once

#include <util/EffectSubHandlers.h>

class EffectTwitchHandler : public EffectSubHandler
{
    std::string voter = "";

public:
    std::string
    GetVoter ()
    {
        return voter;
    }

    void
    Initialise (const nlohmann::json &data)
    {
        if (data.contains ("twitchData"))
            voter = data["twitchData"].value ("voter", "");
    }

    explicit operator bool ()
    {
        return voter != "";
    }
};
