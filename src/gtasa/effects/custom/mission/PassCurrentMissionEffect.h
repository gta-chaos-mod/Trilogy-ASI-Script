#pragma once

#include <map>

#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/Teleportation.h"

#include "CCamera.h"
#include "CCutsceneMgr.h"
#include "extensions/ScriptCommands.h"

class PassCurrentMissionEffect : public EffectBase
{
private:
    static bool isEnabled;

private:
    std::map<std::string, int>  offsetMap           = {};
    std::map<std::string, bool> debugCodeMap        = {};
    bool                        triedPassingMission = false;
    int                         missionPassWait     = 100;

public:
    PassCurrentMissionEffect ();

    void InitializeHooks () override;

    void Enable () override;
    void Disable () override;

    void HandleTick () override;

    void ClearPlayerStatus ();

    static char __stdcall HookedDebugGetKeyDown (int keyCode, int a2, int a3);
};
