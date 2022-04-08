#include <util/DrawHelper.h>
#include <util/GameHandler.cpp>
#include <util/Websocket.h>

#ifdef GTASA
CdeclEvent<AddressList<0x53E550, H_CALL, 0x53E83C, H_CALL, 0x53EBA2, H_CALL>,
           PRIORITY_AFTER, ArgPickNone, void ()>
    drawAfterFadeEvent;
#elif GTAVC
CdeclEvent<AddressList<0x4A5D3D, H_CALL, 0x4A6138, H_CALL>, PRIORITY_AFTER,
           ArgPickNone, void ()>
    drawAfterFadeEvent;
#elif GTA3
CdeclEvent<AddressList<0x48E470, H_CALL>, PRIORITY_AFTER, ArgPickNone, void ()>
    drawAfterFadeEvent;
#endif

class TrilogyChaosMod
{
public:
    TrilogyChaosMod ()
    {
        Websocket::Setup ();

        GameHandler::Initialise ();

        // Events::gameProcessEvent.after += EffectDatabase::Tick;
        Events::gameProcessEvent.after += GameHandler::ProcessGame;

        drawAfterFadeEvent.after += DrawHelper::Draw;
    }
} trilogyChaosMod;
