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

	static bool HandleArmour(CPedDamageResponseCalculator* damageResponseCalc, CPed* ped, int cDamageResponseInfo);
	static bool HandleHealth(CPedDamageResponseCalculator* damageResponseCalc, CPed* ped, float* a3, char a4);
};

