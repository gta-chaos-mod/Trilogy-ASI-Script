#pragma once

#include "EffectSubHandlers.h"

class EffectTwitchHandler : public EffectSubhandler
{
    std::string voter;
    
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

        // TODO: Remove
        if (voter == "N/A")
            voter = "";
    }

    explicit operator bool () { return voter != ""; }
};
