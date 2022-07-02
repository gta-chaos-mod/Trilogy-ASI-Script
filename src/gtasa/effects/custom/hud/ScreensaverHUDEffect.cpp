#include "util/EffectBase.h"
#include "util/GenericUtil.h"
#include "util/Globals.h"
#include "util/hooks/HookMacros.h"

#include <CFont.h>
#include <CHud.h>

using namespace plugin;

class ScreensaverHUDEffect : public EffectBase
{
    struct HUDElement
    {
        CVector2D pos;
        float     speedModifier = 1.0f;
        bool      goingRight    = false;
        bool      goingDown     = false;
    };

    static inline std::map<const char *, HUDElement> positions = {};

    static inline EffectInstance *instance;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        instance = inst;
        positions.clear ();

        HOOK_ARGS (inst, Hooked_DrawClock, char (float, float, char *),
                   0x58EC21);

        HOOK_ARGS (inst, Hooked_DrawMoney, char (float, float, char *),
                   0x58F607);

        // TODO: Crashes?
        // HOOK_ARGS (inst, Hooked_DrawWanted, char (float, float, char *),
        //            0x58DE42, 0x58DF11, 0x58DFD3);

        HOOK_ARGS (inst, Hooked_DrawVehicleName, char (float, float, char *),
                   0x58B156);

        HOOK_ARGS (inst, Hooked_DrawScriptText, char (float, float, char *),
                   0x58C229);

        HOOK_ARGS (inst, Hooked_DrawSubtitles, char (float, float, char *),
                   0x58C68A);

        HOOK_ARGS (inst, Hooked_DrawHelpMessage, char (float, float, char *),
                   0x58C00F);

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
    }

    void
    OnTick (EffectInstance *inst) override
    {
        float tick = GenericUtil::CalculateTick (0.2f);

        for (auto &[name, element] : positions)
        {
            CVector2D &pos          = element.pos;
            float      adjustedTick = tick * element.speedModifier;

            if (element.goingRight)
            {
                pos.x += adjustedTick;
                if (SCREEN_COORD (pos.x) >= SCREEN_WIDTH)
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
                if (SCREEN_COORD (pos.y) >= SCREEN_HEIGHT)
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
    CreateHUDElement (float x, float y)
    {
        return HUDElement{.pos
                          = CVector2D (instance->Random (0.0f, SCREEN_WIDTH),
                                       instance->Random (0.0f, SCREEN_HEIGHT)),
                          .speedModifier = instance->Random (0.75f, 1.25f),
                          .goingRight    = instance->Random (0, 1) == 0,
                          .goingDown     = instance->Random (0, 1) == 0};
    }

    static char
    Hooked_DrawClock (auto &&cb, float &x, float &y, char *text)
    {
        if (!positions.contains ("clock"))
        {
            positions["clock"] = CreateHUDElement (x, y);
        }

        x = positions["clock"].pos.x;
        y = positions["clock"].pos.y;

        return cb ();
    }

    static char
    Hooked_DrawMoney (auto &&cb, float &x, float &y, char *text)
    {
        if (!positions.contains ("money"))
        {
            positions["money"] = CreateHUDElement (x, y);
        }

        x = positions["money"].pos.x;
        y = positions["money"].pos.y;

        return cb ();
    }

    static char
    Hooked_DrawWanted (auto &&cb, float &x, float &y, char *text)
    {
        if (!positions.contains ("wanted"))
        {
            positions["wanted"] = CreateHUDElement (x, y);
        }

        x = positions["wanted"].pos.x;
        y = positions["wanted"].pos.y;

        return cb ();
    }

    static char
    Hooked_DrawVehicleName (auto &&cb, float &x, float &y, char *text)
    {
        if (!positions.contains ("vehicleName"))
        {
            positions["vehicleName"] = CreateHUDElement (x, y);
        }

        x = positions["vehicleName"].pos.x;
        y = positions["vehicleName"].pos.y;

        return cb ();
    }

    static char
    Hooked_DrawScriptText (auto &&cb, float &x, float &y, char *text)
    {
        if (!positions.contains ("scriptText"))
        {
            positions["scriptText"] = CreateHUDElement (x, y);
        }

        x = positions["scriptText"].pos.x;
        y = positions["scriptText"].pos.y;

        return cb ();
    }

    static char
    Hooked_DrawSubtitles (auto &&cb, float &x, float &y, char *text)
    {
        if (!positions.contains ("subtitles"))
        {
            positions["subtitles"] = CreateHUDElement (x, y);
        }

        x = positions["subtitles"].pos.x;
        y = positions["subtitles"].pos.y;

        return cb ();
    }

    // TODO: Calculate width for string properly
    static char
    Hooked_DrawHelpMessage (auto &&cb, float &x, float &y, char *text)
    {
        if (!positions.contains ("helpMessage"))
        {
            positions["helpMessage"] = CreateHUDElement (x, y);
        }

        x = positions["helpMessage"].pos.x;
        y = positions["helpMessage"].pos.y;

        float width = 34.0 * (RsGlobal.maximumWidth * 0.0015625)
                      + RsGlobal.maximumWidth * 0.0015625 * 200.0
                      - RsGlobal.maximumWidth * 0.0015625 * 4.0;

        CFont::SetWrapx (width);

        return cb ();
    }

    static void
    Hooked_RenderHealthBar (auto &&cb, int playerId, signed int &x,
                            signed int &y)
    {
        if (!positions.contains ("healthBar"))
        {
            positions["healthBar"] = CreateHUDElement (x, y);
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
            positions["armorBar"] = CreateHUDElement (x, y);
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
            positions["breathBar"] = CreateHUDElement (x, y);
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
            positions["weaponIcon"] = CreateHUDElement (x, y);
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
            positions["weaponAmmo"] = CreateHUDElement (x, y);
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

        // mod

        if (!positions.contains ("radar"))
        {
            positions["radar"] = CreateHUDElement (x, y);
        }

        x = positions["radar"].pos.x / 2.2f;
        y = positions["radar"].pos.y * 1.45f;

        injector::WriteMemory<float> (0x858A10, x);
        RsGlobal.maximumHeight = y;

        cb ();

        RsGlobal.maximumHeight = oldHeight;

        injector::WriteMemory<float> (0x858A10, oldX);
    }
};

DEFINE_EFFECT (ScreensaverHUDEffect, "effect_screensaver_hud", GROUP_HUD);