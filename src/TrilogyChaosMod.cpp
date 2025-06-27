#include "util/Config.h"
#include "util/DrawHelper.h"
#include "util/EffectHandler.h"
#include "util/GameHandler.h"
#include "util/Globals.h"
#include "util/Websocket.h"

// Thanks to Parik for this!
static void
UnProtectInstance ()
{
    auto              hExecutableInstance = (size_t) GetModuleHandle (NULL);
    IMAGE_NT_HEADERS *ntHeader
        = (IMAGE_NT_HEADERS *) (hExecutableInstance
                                + ((IMAGE_DOS_HEADER *) hExecutableInstance)
                                      ->e_lfanew);
    SIZE_T size = ntHeader->OptionalHeader.SizeOfImage;
    DWORD  oldProtect;
    VirtualProtect ((VOID *) hExecutableInstance, size, PAGE_EXECUTE_READWRITE,
                    &oldProtect);
}

class TrilogyChaosMod
{
public:
    TrilogyChaosMod ()
    {
        UnProtectInstance ();

        Config::Init ();
        Websocket::Setup ();

        Events::initRwEvent += GameHandler::Initialise;

        Events::gameProcessEvent += EffectHandler::Tick;
        Events::gameProcessEvent += GameHandler::ProcessGame;
        Events::processScriptsEvent += EffectHandler::ProcessScripts;

        Events::gameProcessEvent += DrawHelper::Tick;
        drawAfterFadeEvent += [] ()
        {
            if (Globals::enabledEffects["mirrored_screen"]
                || Globals::enabledEffects["upside_down_screen"])
                return;

            DrawHelper::DrawEffects ();
        };
        drawAfterFadeEvent += [] ()
        {
            if (Globals::enabledEffects["mirrored_screen"]
                || Globals::enabledEffects["upside_down_screen"])
                return;

            DrawHelper::Draw ();
        };
    }
} trilogyChaosMod;
