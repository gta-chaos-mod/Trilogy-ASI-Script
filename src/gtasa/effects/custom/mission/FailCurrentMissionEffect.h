#pragma once

#include "effects/EffectPlaceholder.h"
#include "util/GameUtil.h"
#include "util/Teleportation.h"

#include "CGangWars.h"
#include "CTheScripts.h"
#include "extensions/ScriptCommands.h"

class FailCurrentMissionEffect : public EffectPlaceholder
{
public:
    FailCurrentMissionEffect ();

    void Enable () override;

    void ClearPlayerStatus ();
};
