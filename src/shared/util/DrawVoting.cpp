#include "DrawVoting.h"

#include "util/ColorHelper.h"
#include "util/Globals.h"

void
DrawVoting::DrawVotes ()
{
    if (GenericUtil::IsMenuActive ()) return;

    // Always try to draw votes
    for (int i = 0; i < 3; i++)
        DrawVote (i);

    if (drawRemaining > 0)
    {
        // Make sure to bring back the picked one
        for (int i = 0; i < 3; i++)
        {
            if (pickedVote == -1)
            {
                votes[i].offset
                    = std::min (votes[i].offset
                                    + (float) GenericUtil::CalculateTick (
                                        0.0015f),
                                1.0f);
            }
        }

        drawRemaining -= (int) GenericUtil::CalculateTick ();
        return;
    }

    // Finally get rid of every effect again
    for (int i = 0; i < 3; i++)
    {
        votes[i].offset
            = std::max (0.0f,
                        votes[i].offset
                            - (float) GenericUtil::CalculateTick (0.0015f));
    }
}

void
DrawVoting::UpdateVotes (std::vector<std::string> effects,
                         std::vector<int> _votes, int _pickedVote)
{
    totalVotes = 0;
    for (int i = 0; i < 3; i++)
    {
        votes[i] = VotingElement (effects[i], _votes[i], votes[i].offset);

        if (votes[i].votes > 0) totalVotes += votes[i].votes;
    }

    pickedVote = _pickedVote;

    drawRemaining = 15000;
}

void
DrawVoting::DrawVote (int choice)
{
    if (votes[choice].description == "") return;

    float barX = 0.0f;
    float x    = 0.0f;
    if (choice == 0)
    { // Left Align
        x = SCREEN_COORD_LEFT (100.0f) + SCREEN_COORD (150.0f);
    }
    else if (choice == 1)
    { // Center Align
        x = SCREEN_COORD_CENTER_X;
    }
    else if (choice == 2)
    { // Right Align
        x = SCREEN_COORD_RIGHT (100.0f) - SCREEN_COORD (150.0f);
    }

#ifdef GTASA
    float y = SCREEN_COORD_BOTTOM (CalculateYOffset (choice, 65.0f));
#else
    float y = SCREEN_COORD_BOTTOM (CalculateYOffset (choice, 75.0f));
#endif
    std::string_view description = votes[choice].description;

    if (Globals::enabledEffects["replace_all_text"] && pickedVote != -1)
        description = Globals::replaceAllTextString;

    gamefont::PrintUnscaled (std::string (description), x, y, FONT_DEFAULT,
                             SCREEN_MULTIPLIER (0.8f), SCREEN_MULTIPLIER (1.0f),
                             (pickedVote == -1 || pickedVote == choice)
                                 ? color::White
                                 : color::DarkGray,
                             gamefont::AlignCenter, 1, color::Black, true);

    // Vote Bars
    float barWidth = 300.0f;
    float barStart = x - SCREEN_COORD (barWidth / 2);
    y += SCREEN_COORD (40.0f);

    // Outline Bar
    CRect rect
        = CRect (barStart - SCREEN_COORD (2.0f), y - SCREEN_COORD (2.0f),
                 barStart + SCREEN_COORD (barWidth) + SCREEN_COORD (2.0f),
                 y + SCREEN_COORD (18.0f) + SCREEN_COORD (2.0f));
    CSprite2d::DrawRect (rect, color::Black);

    // Background Bar
    rect = CRect (barStart, y, barStart + SCREEN_COORD (barWidth),
                  y + SCREEN_COORD (16.0f));
    CSprite2d::DrawRect (rect, ColorHelper::GetBackgroundColor ());

    // Filled Bar
    rect
        = CRect (barStart, y,
                 barStart + SCREEN_COORD (CalculateBarWidth (choice, barWidth)),
                 y + SCREEN_COORD (16.0f));
    CSprite2d::DrawRect (rect, ColorHelper::GetForegroundColor ());

    // Draw Percentage
    float percentage_x = barStart + 150.0f;

    gamefont::PrintUnscaled (GetPercentage (choice), x, y - SCREEN_COORD (3.0f),
                             FONT_DEFAULT, SCREEN_MULTIPLIER (0.4f),
                             SCREEN_MULTIPLIER (0.6f),
                             (pickedVote == -1 || pickedVote == choice)
                                 ? color::White
                                 : color::DarkGray,
                             gamefont::AlignCenter, 1, color::Black, true);
}

float
DrawVoting::CalculateYOffset (int choice, float adjustment)
{
    if (choice < 0 || choice > 2) return 0.0f;

    float t            = votes[choice].offset;
    float easePosition = 1 + (--t) * t * (2.70158f * t + 1.70158f);
    return easePosition * adjustment;
}

float
DrawVoting::CalculateBarWidth (int choice, float maxWidth)
{
    if (totalVotes == 0 || votes[choice].votes == -1) return 0.0f;

    return maxWidth * ((float) votes[choice].votes / (float) totalVotes);
}

std::string
DrawVoting::GetPercentage (int choice)
{
    if (Globals::enabledEffects["replace_all_text"])
        return Globals::replaceAllTextString;

    std::string percentage;

    if (votes[choice].votes > -1)
    {
        int i_percentage = totalVotes == 0
                               ? 0
                               : (int) round ((float) votes[choice].votes
                                              / (float) totalVotes * 100.0f);

        percentage.append (std::to_string (i_percentage));
        percentage.append ("%");
        percentage.append (" - ");
        percentage.append (std::to_string (votes[choice].votes));
        percentage.append ("/");
        percentage.append (std::to_string (totalVotes));
    }
    else
    {
        percentage.append ("?%");
    }

    return percentage;
}
