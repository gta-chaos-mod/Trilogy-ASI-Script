#pragma once

#include "util/EffectBase.h"
#include "util/GameFixes.h"

#include "CControllerConfigManager.h"

class ForceVehicleMouseSteering : public EffectBase
{
private:
    static bool overrideMouseSteering;

    CControllerAction origActions[59] = {};

public:
    ForceVehicleMouseSteering ();

    void InitializeHooks () override;

    void Enable () override;
    void Disable () override;

    void HandleTick () override;

    static FILESTREAM HookedOpenFile (const char *file, const char *mode);
    static void __fastcall HookedCMenuManagerProcessPCMenuOptions (
        CMenuManager *thisManager, void *edx, eMenuPage page);
};
