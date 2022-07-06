#include "util/DrawHelper.h"
#include "util/EffectHandler.h"
#include "util/GameHandler.h"
#include "util/Websocket.h"

class TrilogyChaosMod
{
#ifdef GTASA
    CdeclEvent<
        AddressList<0x53E550, H_CALL, 0x53E83C, H_CALL, 0x53EBA2, H_CALL>,
        PRIORITY_AFTER, ArgPickNone, void ()>
        drawAfterFadeEvent;
#elif GTAVC
    CdeclEvent<AddressList<0x4A5D3D, H_CALL, 0x4A6138, H_CALL>, PRIORITY_AFTER,
               ArgPickNone, void ()>
        drawAfterFadeEvent;
#elif GTA3
    CdeclEvent<AddressList<0x48E470, H_CALL>, PRIORITY_AFTER, ArgPickNone,
               void ()>
        drawAfterFadeEvent;
#endif

public:
    TrilogyChaosMod ()
    {
        Websocket::Setup ();

        Events::initRwEvent += GameHandler::Initialise;

        Events::gameProcessEvent += EffectHandler::Tick;
        Events::processScriptsEvent += EffectHandler::ProcessScripts;
        Events::gameProcessEvent += GameHandler::ProcessGame;

        drawAfterFadeEvent += DrawHelper::Draw;
    }
} trilogyChaosMod;
