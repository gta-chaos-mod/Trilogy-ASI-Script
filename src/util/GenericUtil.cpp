// Copyright (c) 2019 Lordmau5
#include "GenericUtil.h"

std::vector<std::string> GenericUtil::replacements;
bool GenericUtil::areEffectsCryptic = false;

void GenericUtil::InitializeUnprotectedMemory() {
	DWORD ignore;
	injector::UnprotectMemory(0x863984, sizeof(GAME_GRAVITY), ignore);
}

void GenericUtil::InitializeCharReplacements() {
	// Lower-case a-z
	replacements.push_back("abcdefghijklmnopqrstuvwxyz");

	// Upper-case A-Z
	replacements.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	// Numbers 0-9
	replacements.push_back("0123456789");

	// Symbols
	replacements.push_back("!?\"$%&(),.=+-_*/");
}

std::vector<std::string> GenericUtil::GetCharReplacements() {
	return replacements;
}
