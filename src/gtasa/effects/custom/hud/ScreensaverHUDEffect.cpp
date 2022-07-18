#include "util/EffectBase.h"
#include "util/EffectDrawHandler.h"
#include "util/GenericUtil.h"
#include "util/Globals.h"
#include "util/hooks/HookMacros.h"

#include <CFont.h>
#include <CHud.h>
#include <CHudColours.h>

using namespace plugin;

class ScreensaverHUDEffect : public EffectBase
{
    struct HUDElement
    {
        CVector2D pos           = {0.0f, 0.0f};
        float     speedModifier = 1.0f;
        bool      goingRight    = false;
        bool      goingDown     = false;
    };

    static inline std::map<std::string, HUDElement> positions = {};

    static inline EffectInstance *instance = nullptr;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        positions.clear ();

        HOOK_ARGS (inst, Hooked_DrawClock, void (float, float, char *),
                   0x58EC21);

        HOOK_ARGS (inst, Hooked_DrawMoney, void (float, float, char *),
                   0x58F607);

        HOOK_ARGS (inst, Hooked_DrawVehicleName, void (float, float, char *),
                   0x58B156);

        HOOK_ARGS (inst, Hooked_DrawScriptText, void (float, float, char *),
                   0x58C229);

        HOOK_ARGS (inst, Hooked_DrawSubtitles, void (float, float, char *),
                   0x58C68A);

        HOOK_ARGS (inst, Hooked_DrawHelpMessage, void (float, float, char *),
                   0x58C00F);

        HOOK_ARGS (inst, Hooked_DrawWanted, void (float, float, char *),
                   0x58DFD3);

        HOOK_ARGS (inst, Hooked_RenderHealthBar,
                   void (int, signed int, signed int), 0x58EE9A);

        HOOK_ARGS (inst, Hooked_RenderArmorBar,
                   void (int, signed int, signed int), 0x58EF6B);

        HOOK_ARGS (inst, Hooked_RenderBreathBar,
                   void (int, signed int, signed int), 0x58F131);

        HOOK_ARGS (inst, Hooked_RenderWeaponIcon,
                   void (CPed *, signed int, signed int, float), 0x58F944);

        HOOK_ARGS (inst, Hooked_RenderWeaponAmmo,
                   void (CPed *, signed int, signed int, float), 0x58FA25);

        HOOK (inst, Hooked_DrawRadar, void (), 0x58FC53);

        Globals::isScreensaverHUDEffectEnabled = true;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Globals::isScreensaverHUDEffectEnabled = false;

        EffectDrawHandler::ClearScreensaverHUDMap ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        instance = inst;

        float tick = GenericUtil::CalculateTick (0.2f);

        for (auto &[name, element] : positions)
        {
            CVector2D &pos          = element.pos;
            float      adjustedTick = tick * element.speedModifier;

            if (element.goingRight)
            {
                pos.x += adjustedTick;
                if (pos.x >= SCREEN_COORD_RIGHT (20.0f))
                    element.goingRight = false;
            }
            else
            {
                pos.x -= adjustedTick;
                if (pos.x < 0.0f) element.goingRight = true;
            }

            if (element.goingDown)
            {
                pos.y += adjustedTick;
                if (pos.y >= SCREEN_COORD_BOTTOM (20.0f))
                    element.goingDown = false;
            }
            else
            {
                pos.y -= adjustedTick;
                if (pos.y < 0.0f) element.goingDown = true;
            }
        }
    }

    static HUDElement
    CreateHUDElement ()
    {
        return HUDElement{
            .pos = CVector2D (instance->Random (SCREEN_COORD_LEFT (20.0f),
                                                SCREEN_COORD_RIGHT (20.0f)),
                              instance->Random (SCREEN_COORD_TOP (20.0f),
                                                SCREEN_COORD_BOTTOM (20.0f))),
            .speedModifier = instance->Random (0.5f, 2.0f),
            .goingRight    = instance->Random (0, 1) == 0,
            .goingDown     = instance->Random (0, 1) == 0};
    }

    static void
    QueueHUDElement (std::string name)
    {
        if (!instance) return;

        positions[name] = CreateHUDElement ();
    }

    static void
    Hooked_DrawClock (auto &&cb, float &x, float &y, char *text)
    {
        if (!positions.contains ("clock"))
        {
            QueueHUDElement ("clock");
            cb ();
            return;
        }

        x = positions["clock"].pos.x;
        y = positions["clock"].pos.y;

        cb ();
    }

    static void
    Hooked_DrawMoney (auto &&cb, float &x, float &y, char *text)
    {
        if (!positions.contains ("money"))
        {
            QueueHUDElement ("money");
            cb ();
            return;
        }

        x = positions["money"].pos.x;
        y = positions["money"].pos.y;

        cb ();
    }

    static void
    Hooked_DrawVehicleName (auto &&cb, float &x, float &y, char *text)
    {
        if (!positions.contains ("vehicleName"))
        {
            QueueHUDElement ("vehicleName");
            cb ();
            return;
        }

        x = positions["vehicleName"].pos.x;
        y = positions["vehicleName"].pos.y;

        cb ();
    }

    static void
    Hooked_DrawScriptText (auto &&cb, float &x, float &y, char *text)
    {
        if (!positions.contains ("scriptText"))
        {
            QueueHUDElement ("scriptText");
            cb ();
            return;
        }

        x = positions["scriptText"].pos.x;
        y = positions["scriptText"].pos.y;

        cb ();
    }

    static void
    Hooked_DrawSubtitles (auto &&cb, float &x, float &y, char *text)
    {
        if (!positions.contains ("subtitles"))
        {
            QueueHUDElement ("subtitles");
            cb ();
            return;
        }

        x = positions["subtitles"].pos.x;
        y = positions["subtitles"].pos.y;

        cb ();
    }

    // TODO: Calculate width for string properly
    static void
    Hooked_DrawHelpMessage (auto &&cb, float &x, float &y, char *text)
    {
        if (!positions.contains ("helpMessage"))
        {
            QueueHUDElement ("helpMessage");
            cb ();
            return;
        }

        x = positions["helpMessage"].pos.x;
        y = positions["helpMessage"].pos.y;

        float width = 34.0 * (RsGlobal.maximumWidth * 0.0015625)
                      + RsGlobal.maximumWidth * 0.0015625 * 200.0
                      - RsGlobal.maximumWidth * 0.0015625 * 4.0;

        CFont::SetWrapx (std::min (x + width, SCREEN_WIDTH));

        cb ();
    }

    static void
    Hooked_DrawWanted (auto &&cb, float &x, float &y, char *text)
    {
        std::string wanted = "wanted" + std::to_string ((int) x);

        if (!positions.contains (wanted))
        {
            QueueHUDElement (wanted);
            cb ();
            return;
        }

        x = positions[wanted].pos.x;
        y = positions[wanted].pos.y;

        cb ();
    }

    static void
    Hooked_RenderHealthBar (auto &&cb, int playerId, signed int &x,
                            signed int &y)
    {
        if (!positions.contains ("healthBar"))
        {
            QueueHUDElement ("healthBar");
            cb ();
            return;
        }

        x = positions["healthBar"].pos.x;
        y = positions["healthBar"].pos.y;

        cb ();
    }

    static void
    Hooked_RenderArmorBar (auto &&cb, int playerId, signed int &x,
                           signed int &y)
    {
        if (!positions.contains ("armorBar"))
        {
            QueueHUDElement ("armorBar");
            cb ();
            return;
        }

        x = positions["armorBar"].pos.x;
        y = positions["armorBar"].pos.y;

        cb ();
    }

    static void
    Hooked_RenderBreathBar (auto &&cb, int playerId, signed int &x,
                            signed int &y)
    {
        if (!positions.contains ("breathBar"))
        {
            QueueHUDElement ("breathBar");
            cb ();
            return;
        }

        x = positions["breathBar"].pos.x;
        y = positions["breathBar"].pos.y;

        cb ();
    }

    static void
    Hooked_RenderWeaponIcon (auto &&cb, CPed *ped, signed int &x, signed int &y,
                             float alpha)
    {
        if (!positions.contains ("weaponIcon"))
        {
            QueueHUDElement ("weaponIcon");
            cb ();
            return;
        }

        x = positions["weaponIcon"].pos.x;
        y = positions["weaponIcon"].pos.y;

        cb ();
    }

    static void
    Hooked_RenderWeaponAmmo (auto &&cb, CPed *ped, signed int &x, signed int &y,
                             float alpha)
    {
        if (!positions.contains ("weaponAmmo"))
        {
            QueueHUDElement ("weaponAmmo");
            cb ();
            return;
        }

        x = positions["weaponAmmo"].pos.x;
        y = positions["weaponAmmo"].pos.y;

        cb ();
    }

    // TODO: Fix squished radar when it goes to the top
    static void
    Hooked_DrawRadar (auto &&cb)
    {
        float   oldX      = injector::ReadMemory<float> (0x858A10);
        RwInt32 oldHeight = RsGlobal.maximumHeight;

        float x = oldX;
        float y = oldHeight;

        if (!positions.contains ("radar"))
        {
            QueueHUDElement ("radar");
            cb ();
            return;
        }

        x = positions["radar"].pos.x / 2.9f;
        y = positions["radar"].pos.y / 0.9f;

        injector::WriteMemory<float> (0x858A10, x);
        RsGlobal.maximumHeight = y;

        cb ();

        RsGlobal.maximumHeight = oldHeight;

        injector::WriteMemory<float> (0x858A10, oldX);
    }
};

// TODO: Crashes when in fade after loading a save and enabling it.
// Got addresses, but no debug symbols, since release build
DEFINE_EFFECT (ScreensaverHUDEffect, "effect_screensaver_hud", GROUP_HUD);