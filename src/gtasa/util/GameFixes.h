#include "util/Config.h"
#include "util/EffectHandler.h"
#include "util/GameUtil.h"
#include "util/GenericUtil.h"

#include <CText.h>

using namespace plugin;

class GameFixes
{
private:
    static inline bool didTryLoadAutoSave = false;

public:
    static void Initialise ();

    static void TryLoadAutoSave ();

    static void __fastcall Hooked_ProcessMenuOptions (CMenuManager *thisManager,
                                                      void         *edx,
                                                      eMenuPage     page);
    static char *__fastcall Hooked_CText_Get (CText *thisText, void *edx,
                                              char *key);
    static bool Hooked_GetIsSlowMotionActive ();
    static __int16 __fastcall Hooked_CRunningScript_CollectParameters (
        CRunningScript *thisScript, void *edx, unsigned __int16 num);
    static char Hooked_CheatCancelEachOther (int id);
    static int __fastcall Hooked_CMenuManager_DoSettingsBeforeStartingAGame (
        CMenuManager *thisManager);

    static void __fastcall Hooked_ProcessTrainTrackSound (
        CAEVehicleAudioEntity *, void *, cVehicleParams *);
};
