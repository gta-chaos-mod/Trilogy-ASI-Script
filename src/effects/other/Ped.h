// Copyright (c) 2019 Lordmau5
#pragma once

#include "common.h"
#include "plugin.h"

#include "CCheat.h"
#include "CClothes.h"
#include "CFireManager.h"

class Ped
{
public:
	static void SetAllOnFire();
	static void ClearWeapons();

	static void MakeBeachParty();
	static void MakeNinja();
	static void MakeKinky();
	static void MakeFunhouse();
	static void MakeCountry();

private:
	static void RebuildPlayer();
};
