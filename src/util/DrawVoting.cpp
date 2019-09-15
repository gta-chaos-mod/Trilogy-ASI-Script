// Copyright (c) 2019 Lordmau5
#include "DrawVoting.h"

std::string DrawVoting::effects[3];
int DrawVoting::votes[3];
int DrawVoting::totalVotes;
float DrawVoting::fadeIn[3];
int DrawVoting::drawRemaining = 0;
int DrawVoting::pickedChoice = -1;

void DrawVoting::DrawVotes() {
	// Always try to draw votes
	for (int i = 0; i < 3; i++) {
		DrawVote(i);
	}

	if (drawRemaining > 0) {
		// Make sure to bring back the picked one
		for (int i = 0; i < 3; i++) {
			if (pickedChoice == -1) {
				fadeIn[i] = min(fadeIn[i] + 0.05f, 1.0f);
			}
		}

		drawRemaining -= GenericUtil::CalculateTick();
		return;
	}

	// Finally get rid of every effect again
	for (int i = 0; i < 3; i++) {
		fadeIn[i] = max(0.0f, fadeIn[i] - 0.05f);
	}
}

void DrawVoting::UpdateVotes(char _effects[3][128], int _votes[3], int _pickedChoice) {
	totalVotes = 0;
	for (int i = 0; i < 3; i++) {
		effects[i] = std::string(_effects[i]);
		votes[i] = _votes[i];

		if (votes[i] > 0) {
			totalVotes += votes[i];
		}
	}

	pickedChoice = _pickedChoice;

	drawRemaining = 15000;
}

void DrawVoting::DrawVote(int choice) {
	if (effects[choice] == "") {
		return;
	}

	// Effect Text
	CFont::SetCentreSize(SCREEN_WIDTH);
	CFont::SetScaleForCurrentlanguage(SCREEN_MULTIPLIER(0.8f), SCREEN_MULTIPLIER(1.6f));

	/*CFont::SetOrientation(choice == 0 ? eFontAlignment::ALIGN_LEFT : (choice == 1 ? eFontAlignment::ALIGN_CENTER : eFontAlignment::ALIGN_RIGHT));*/
	CFont::SetOrientation(eFontAlignment::ALIGN_CENTER);
	CFont::SetJustify(false);
	CFont::SetProportional(true);
	CFont::SetFontStyle(FONT_SUBTITLES);
	CFont::SetDropColor(CRGBA(0, 0, 0, 200));
	CFont::SetDropShadowPosition(0);
	CFont::SetEdge(1);
	CFont::SetBackground(false, false);

	float stringWidth = CFont::GetStringWidth((char*)effects[choice].c_str(), true, false);

	float x = 0.0f;
	//if (choice == 0) { // Left Align
	//	x = SCREEN_COORD_LEFT(40.0f);
	//}
	//else if (choice == 1) { // Center Align
	//	x = SCREEN_COORD_CENTER_X;
	//}
	//else if (choice == 2) { // Right Align
	//	x = SCREEN_COORD_RIGHT(40.0f);
	//}

	if (choice == 0) { // Left Align
		x = SCREEN_COORD_LEFT(80.0f) + SCREEN_COORD(150.0f);
	}
	else if (choice == 1) { // Center Align
		x = SCREEN_COORD_CENTER_X;
	}
	else if (choice == 2) { // Right Align
		x = SCREEN_COORD_RIGHT(80.0f) - SCREEN_COORD(150.0f);
	}

	float y = SCREEN_COORD_BOTTOM(60.0f) + SCREEN_COORD(60.0f - CalculateYOffset(choice) * 60.0f);

	CFont::SetColor((pickedChoice == -1 || pickedChoice == choice) ? CRGBA(255, 255, 255, 200) : CRGBA(175, 175, 175, 200));
	CFont::PrintString(x, y, (char*)effects[choice].c_str());

	//// Vote Bars
	//DrawVoteBars(choice, x, y, stringWidth);

	// Vote Bars
	float barWidth = 300.0f;
	float barStart = x - SCREEN_COORD(barWidth / 2);
	y += SCREEN_COORD(32.0f);

	// Outline Bar
	CRect rect = CRect(barStart - SCREEN_COORD(2.0f), y - SCREEN_COORD(2.0f), barStart + SCREEN_COORD(barWidth) + SCREEN_COORD(2.0f), y + SCREEN_COORD(18.0f) + SCREEN_COORD(2.0f));
	CSprite2d::DrawRect(rect, CRGBA(0, 0, 0, 225));

	// Background Bar
	rect = CRect(barStart, y, barStart + SCREEN_COORD(barWidth), y + SCREEN_COORD(16.0f));
	CSprite2d::DrawRect(rect, CRGBA(120, 0, 0, 225));

	// Filled Bar
	rect = CRect(barStart, y, barStart + SCREEN_COORD(CalculateBarWidth(choice, barWidth)), y + SCREEN_COORD(16.0f));
	CSprite2d::DrawRect(rect, CRGBA(230, 0, 0, 225));

	// Draw Percentage
	float percentage_x = barStart + SCREEN_COORD(150.0f);

	CFont::SetCentreSize(SCREEN_WIDTH);
	CFont::SetScaleForCurrentlanguage(SCREEN_MULTIPLIER(0.4f), SCREEN_MULTIPLIER(0.8f));

	CFont::SetOrientation(eFontAlignment::ALIGN_CENTER);
	CFont::SetJustify(false);
	CFont::SetProportional(true);
	CFont::SetFontStyle(FONT_SUBTITLES);
	CFont::SetDropColor(CRGBA(0, 0, 0, 200));
	CFont::SetDropShadowPosition(0);
	CFont::SetEdge(1);
	CFont::SetBackground(false, false);

	CFont::SetColor((pickedChoice == -1 || pickedChoice == choice) ? CRGBA(255, 255, 255, 200) : CRGBA(175, 175, 175, 200));
	CFont::PrintString(percentage_x, y, (char*)GetPercentage(choice).c_str());
}

float DrawVoting::CalculateYOffset(int choice) {
	if (choice < 0 || choice > 2) {
		return 0.0f;
	}

	float t = fadeIn[choice];
	return 1 + (--t) * t * (2.70158f * t + 1.70158f);
}

float DrawVoting::CalculateBarWidth(int choice, float maxWidth) {
	if (totalVotes == 0 || votes[choice] == -1) {
		return 0.0f;
	}

	return maxWidth * ((float)votes[choice] / (float)totalVotes);
}

std::string DrawVoting::GetPercentage(int choice) {
	std::string percentage;

	if (votes[choice] > -1) {
		int i_percentage = totalVotes == 0 ? 0 : (int)round((float)votes[choice] / (float)totalVotes * 100.0f);

		percentage.append(std::to_string(i_percentage));
		percentage.append("%");
		percentage.append(" (");
		percentage.append(std::to_string(votes[choice]));
		percentage.append("/");
		percentage.append(std::to_string(totalVotes));
		percentage.append(")");
	}
	else {
		percentage.append("?%");
	}

	return percentage;
}
