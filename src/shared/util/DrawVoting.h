#pragma once

#include "util/GenericUtil.h"

#include <CFont.h>
#include <extensions/FontPrint.h>

using namespace plugin;

enum eVoteChoice
{
    UNDETERMINED = -1,
    NONE         = 0,

    FIRST  = 1 << 0,
    SECOND = 1 << 1,
    THIRD  = 1 << 2,

    FIRST_SECOND = FIRST | SECOND,
    FIRST_THIRD  = FIRST | THIRD,
    SECOND_THIRD = SECOND | THIRD,

    ALL = FIRST | SECOND | THIRD,
};

class DrawVoting
{
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
    static inline eVoteChoice   pickedVote = eVoteChoice::NONE;

    static inline int drawRemaining = 0;

    static eVoteChoice
    GetVoteChoice (int choice)
    {
        switch (choice)
        {
            case 0: return FIRST;
            case 1: return SECOND;
            case 2: return THIRD;

            default: return NONE;
        }
    };

public:
    static void DrawVotes ();
    static void UpdateVotes (std::vector<std::string> effects,
                             std::vector<int> _votes, eVoteChoice _pickedVote);

    static void        DrawVote (int choice);
    static float       CalculateYOffset (int choice, float adjustment);
    static float       CalculateBarWidth (int choice, float maxWidth);
    static std::string GetPercentage (int choice);
};
