// Copyright (c) 2019 Lordmau5
#pragma once

#include "plugin.h"
#include "common.h"

#include "GenericUtil.h"

#include "CFont.h"

class DrawVoting
{
private:
	static std::string effects[3];
	static int votes[3];
	static int totalVotes;
	static float fadeIn[3];
	static int drawRemaining;
	static int pickedChoice;

public:
	static void DrawVotes();
	static void UpdateVotes(char _effects[3][128], int _votes[3], int _pickedChoice);
	static void UpdateVote(int choice, std::string effect, int votes);
	static void DrawVote(int choice);
	static void DrawVoteBars(int choice, float x, float y, float stringWidth);
	static float CalculateYOffset(int choice);
	static float CalculateBarWidth(int choice, float maxWidth);
	static std::string GetPercentage(int choice);
};
