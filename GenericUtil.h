#pragma once

#include "common.h"

class GenericUtil
{
private:
	static std::vector<std::string> replacements;

public:
	static bool areEffectsCryptic;

public:
	static void InitializeUnprotectedMemory();
	static void InitializeCharReplacements();

	static std::vector<std::string> GetCharReplacements();
};
