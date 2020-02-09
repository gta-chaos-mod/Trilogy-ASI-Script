#pragma once

#include "util/EffectBase.h"
#include "util/GameFixes.h"
#include "util/RandomHelper.h"

#include "CControllerConfigManager.h"
#include "CFileMgr.h"

class DisableOneMovementKeyEffect : public EffectBase
{
private:
    static int mode;

public:
    DisableOneMovementKeyEffect ();

    void InitializeHooks () override;

    void Enable () override;

    static __int16 __fastcall HookedGetSteeringLeftRight (CPad *thisPad);
    static __int16 __fastcall HookedPedWalkLeftRight (CPad *thisPad);
    static __int16 __fastcall HookedPedWalkUpDown (CPad *thisPad);
    static __int16 __fastcall HookedGetAccelerate (CPad *thisPad);
    static __int16 __fastcall HookedGetBrake (CPad *thisPad);
};
