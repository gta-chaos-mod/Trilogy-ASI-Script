#pragma once

#include "TimedEffect.h"

#include "CPedDamageResponseCalculator.h"
#include "CPlayerInfo.h"

class LongLiveTheRich : public TimedEffect
{
public:
	static bool isEnabled;

private:
	int storedMoney = 0;

public:
	LongLiveTheRich(int _duration, std::string _description);

	void Enable() override;
	void Disable() override;

	static void HandleArmour(CPedDamageResponseCalculator* damageResponseCalc, CPed* ped, int cDamageResponseInfo);
	static void HandleHealth(CPedDamageResponseCalculator* damageResponseCalc, CPed* ped, float* a3, char a4);
};

