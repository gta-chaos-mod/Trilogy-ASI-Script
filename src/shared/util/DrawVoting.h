#pragma once

#include "GenericUtil.h"

#include "CFont.h"
#include "extensions/FontPrint.h"

using namespace plugin;

class DrawVoting
{
private:
    struct VotingElement
    {
        std::string description = "";
        int         votes       = 0;
        float       offset      = 0.0f;

        VotingElement () {}
        VotingElement (std::string description, int votes, float offset)
        {
            this->description = std::move (description);
            this->votes       = votes;
            this->offset      = offset;
        }
    };

    static inline VotingElement votes[3];
    static inline int           totalVotes = 0;
    static inline int           pickedVote = 0;

    static inline int drawRemaining = 0;

public:
    static void DrawVotes ();
    static void UpdateVotes (char effects[3][128], int _votes[3],
                             int _pickedVote);

    static void        DrawVote (int choice);
    static float       CalculateYOffset (int choice, float adjustment);
    static float       CalculateBarWidth (int choice, float maxWidth);
    static std::string GetPercentage (int choice);
};
