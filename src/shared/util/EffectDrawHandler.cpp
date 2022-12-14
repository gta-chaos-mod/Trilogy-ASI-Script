#include "EffectDrawHandler.h"

#include "util/ColorHelper.h"
#include "util/DrawHelper.h"
#include "util/EffectHandler.h"
#include "util/EffectInstance.h"
#include "util/EffectTwitchHandler.h"
#include "util/GenericUtil.h"
#include "util/Globals.h"

#include <algorithm>

#include <CFont.h>
#include <CMenuSystem.h>
#include <extensions/FontPrint.h>

bool
EffectDrawHandler::AreEffectsInset ()
{
    int i = 0;
    for (const auto &effect : EffectHandler::GetActiveEffects ())
    {
        if (++i > RECENT_EFFECTS) return false;

        if (effect.DoesEffectDrawTimer ()) return true;
    }

    return false;
}

void
EffectDrawHandler::CalculateDrawPosition ()
{
    const float TEXT_SCALE_X = 1.0f;
    const float TEXT_SCALE_Y = 1.2f;

    float position = isInset ? 90.0f : 25.0f;

    std::string_view name = effect->GetName ();

    if (Globals::isReplaceAllTextEffectEnabled)
        name = Globals::replaceAllTextString;

#ifdef GTASA
    CFont::SetScaleForCurrentlanguage (TEXT_SCALE_X, TEXT_SCALE_Y);
    float renderWidth
        = CFont::GetStringWidth (const_cast<char *> (name.data ()), true,
                                 false);
#elif GTAVC
    CFont::SetScale (TEXT_SCALE_X, TEXT_SCALE_Y);
    float renderWidth = CFont::GetStringWidth (
        (wchar_t *) std::wstring (name.begin (), name.end ()).c_str (), true);
#elif GTA3
    CFont::SetScale (TEXT_SCALE_X, TEXT_SCALE_Y);
    float renderWidth = CFont::GetStringWidth (name.data (), true);
#endif

    x = GenericUtil::EaseOutBack (transitionTimer, -renderWidth, position);
    y = ((idx + 1) * 65.0f) + 200.0f;

    if (Globals::isScreensaverHUDEffectEnabled)
    {
        std::string effectName (effect->GetName ());
        auto        element = positions[effectName];

        x = element.pos.x;
        y = element.pos.y;
    }
}

void
EffectDrawHandler::PrintEffectName ()
{
    std::string_view name = effect->GetName ();

    if (Globals::isReplaceAllTextEffectEnabled)
        name = Globals::replaceAllTextString;

    if (DRAW_LEFT)
    {
        gamefont::Print (gamefont::LeftBottom, gamefont::AlignLeft,
                         std::string (name), x, y, FONT_DEFAULT, 1.0f, 1.2f,
                         GetTextColor (), 1, GetDropShadowColor (), false);
    }
    else
    {
        gamefont::Print (gamefont::RightBottom, gamefont::AlignRight,
                         std::string (name), x, y, FONT_DEFAULT, 1.0f, 1.2f,
                         GetTextColor (), 1, GetDropShadowColor (), false);
    }
}

void
EffectDrawHandler::PrintSubtext ()
{
    if (effect->HasSubtext ())
    {
        std::string_view subtext = effect->GetSubtext ();

        if (Globals::isReplaceAllTextEffectEnabled)
            subtext = Globals::replaceAllTextString;

        if (DRAW_LEFT)
        {
            gamefont::Print (gamefont::LeftBottom, gamefont::AlignLeft,
                             std::string (subtext), x, y - 30.0f, FONT_DEFAULT,
                             0.8f, 1.0f, GetTextColor (), 1,
                             GetDropShadowColor (), true);
        }
        else
        {
            gamefont::Print (gamefont::RightBottom, gamefont::AlignRight,
                             std::string (subtext), x, y - 30.0f, FONT_DEFAULT,
                             0.8f, 1.0f, GetTextColor (), 1,
                             GetDropShadowColor (), true);
        }
    }
}

void
EffectDrawHandler::PrintEffectTimer ()
{
    int actualRemaining
        = effect->GetEffectRemaining () / Globals::effectTimerSpeed;

    if (Config::GetOrDefault ("Drawing.DrawCircles", true))
    {
        if (effect->HasSubtext ()) y -= 10.0f;

        CVector2D center
            = CVector2D (SCREEN_COORD_LEFT (x) - SCREEN_COORD (50.0f),
                         SCREEN_COORD_BOTTOM (y) + SCREEN_COORD (20.0f));

        if (!DRAW_LEFT)
        {
            center = CVector2D (SCREEN_COORD_RIGHT (x) + SCREEN_COORD (50.0f),
                                SCREEN_COORD_BOTTOM (y) + SCREEN_COORD (20.0f));
        }

        RwTextureFilterMode filter        = rwFILTERLINEAR;
        int                 alphaBlending = true;

        RwRenderStateSet (rwRENDERSTATEVERTEXALPHAENABLE, &alphaBlending);
        RwRenderStateSet (rwRENDERSTATETEXTUREFILTER, (void *) (filter));
        RwRenderStateSet (rwRENDERSTATETEXTURERASTER, NULL);

        float angle = (float) effect->GetEffectRemaining ()
                      / (float) effect->GetEffectDuration () * 360.0f;

        DrawHelper::DrawCircle (center, SCREEN_MULTIPLIER (24.0f), 360.0f,
                                color::White);

        DrawHelper::DrawCircle (center, SCREEN_MULTIPLIER (20.0f), 360.0f,
                                ColorHelper::GetBackgroundColor ());

        DrawHelper::DrawCircle (center, SCREEN_MULTIPLIER (20.0f), angle,
                                GetEffectColor ());

        if (actualRemaining < 60000)
        {
            float timerPosX = DRAW_LEFT ? x + 57.0f : x - 57.0f;

            if (DRAW_LEFT)
            {
                gamefont::Print (gamefont::LeftBottom, gamefont::AlignLeft,
                                 GenericUtil::FormatTime (actualRemaining,
                                                          true),
                                 x - 59.0f, y - 2.0f, FONT_DEFAULT, 0.6f, 1.0f,
                                 GetTextColor (), 1, GetDropShadowColor (),
                                 true, 9999.0f, false);
            }
            else
            {
                gamefont::Print (gamefont::RightBottom, gamefont::AlignRight,
                                 GenericUtil::FormatTime (actualRemaining,
                                                          true),
                                 x - 59.0f, y - 2.0f, FONT_DEFAULT, 0.6f, 1.0f,
                                 GetTextColor (), 1, GetDropShadowColor (),
                                 true, 9999.0f, false);
            }
        }
    }
    else
    {
        if (DRAW_LEFT)
        {
            gamefont::Print (gamefont::LeftBottom, gamefont::AlignLeft,
                             GenericUtil::FormatTime (actualRemaining),
                             x - 60.0f, y - 8.0f, FONT_DEFAULT, 0.6f, 0.8f,
                             GetTextColor (), 1, GetDropShadowColor (), true,
                             9999.0f, true);
        }
        else
        {
            gamefont::Print (gamefont::RightBottom, gamefont::AlignRight,
                             GenericUtil::FormatTime (actualRemaining),
                             x - 60.0f, y - 8.0f, FONT_DEFAULT, 0.6f, 0.8f,
                             GetTextColor (), 1, GetDropShadowColor (), true,
                             9999.0f, true);
        }
    }
}
void
EffectDrawHandler::Draw (EffectInstance *effect, int idx, bool inset)
{
    this->effect  = effect;
    this->idx     = idx;
    this->isInset = inset;

    UpdateTimers ();

    CalculateDrawPosition ();

    // Print subtext before effect name so it's behind the effect name
    PrintSubtext ();
    PrintEffectName ();

    if (effect->DoesEffectDrawTimer ()) PrintEffectTimer ();

#ifdef GTASA
    CFont::SetProportional (true);
#else
    CFont::SetPropOn ();
#endif
}

void
EffectDrawHandler::UpdateTimers ()
{
    /* Fade-in of the effect text (and timer)  */
    this->transitionTimer += GenericUtil::CalculateTick (0.0015f);

    this->transitionTimer = std::clamp (this->transitionTimer, 0.0f, 1.0f);

    /* Flashing text during effect start */
    if (textFlashTimer >= 0)
    {
        textFlashTimer -= (int) GenericUtil::CalculateTick (1.0f);
        textFlashingThisFrame = (textFlashTimer / 400) % 2;
    }
    else
        textFlashingThisFrame = false;
}

void
EffectDrawHandler::DrawAndXMore ()
{
    auto &effects = EffectHandler::GetActiveEffects ();

    int size = effects.size ();
    if (size <= RECENT_EFFECTS) return;

    int more = 0;
    for (int i = RECENT_EFFECTS; i < size; i++)
    {
        auto &effect = effects[i];
        if (effect.IsRunning ()) more++;
    }

    if (more == 0) return;

    std::string text = "And " + std::to_string (more) + " more...";

    if (Globals::isReplaceAllTextEffectEnabled)
        text = Globals::replaceAllTextString;

    y = ((RECENT_EFFECTS + 2) * 65.0f) + 200.0f - 20.0f;

    CRGBA darkGray (color::DarkGray);

    if (CMenuSystem::num_menus_in_use && DRAW_LEFT) darkGray.a = 20;

    if (DRAW_LEFT)
    {
        gamefont::Print (gamefont::LeftBottom, gamefont::AlignLeft, text, x, y,
                         FONT_DEFAULT, 0.8f, 1.0f, darkGray, 1,
                         GetDropShadowColor (), true);
    }
    else
    {
        gamefont::Print (gamefont::RightBottom, gamefont::AlignRight, text, x,
                         y, FONT_DEFAULT, 0.8f, 1.0f, darkGray, 1,
                         GetDropShadowColor (), true);
    }
}

void
EffectDrawHandler::DrawRecentEffects ()
{
    bool inset = AreEffectsInset ();

    int i = 0;
    for (auto &effect : EffectHandler::GetActiveEffects ())
    {
        if (++i > RECENT_EFFECTS) break;

        if (!Globals::isHideChaosUIEffectEnabled
            || effect.GetEffect ()->GetID () == "effect_hide_chaos_ui")
            effect.Draw (i, inset);
    }

    if (!Globals::isHideChaosUIEffectEnabled) DrawAndXMore ();
}

EffectDrawHandler::ScreensaverHUDElement
EffectDrawHandler::CreateHUDElement (EffectInstance *effect)
{
    return ScreensaverHUDElement{
        .pos           = CVector2D (effect->Random (SCREEN_COORD_LEFT (10.0f),
                                                    SCREEN_COORD_RIGHT (10.0f)),
                                    effect->Random (SCREEN_COORD_TOP (10.0f),
                                                    SCREEN_COORD_BOTTOM (10.0f))),
        .speedModifier = effect->Random (0.5f, 2.0f),
        .goingRight    = effect->Random (0, 1) == 0,
        .goingDown     = effect->Random (0, 1) == 0};
}

void
EffectDrawHandler::Tick ()
{
    if (!Globals::isScreensaverHUDEffectEnabled) return;

    for (auto &effect : EffectHandler::GetActiveEffects ())
    {
        std::string name (effect.GetName ());
        if (!positions.contains (name))
        {
            positions[name] = CreateHUDElement (&effect);
        }
    }

    float tick = GenericUtil::CalculateTick (0.2f);

    for (auto &[name, element] : positions)
    {
        CVector2D &pos          = element.pos;
        float      adjustedTick = tick * element.speedModifier;

        if (element.goingRight)
        {
            pos.x += adjustedTick;
            if (pos.x >= SCREEN_COORD_RIGHT (20.0f)) element.goingRight = false;
        }
        else
        {
            pos.x -= adjustedTick;
            if (pos.x < 0.0f) element.goingRight = true;
        }

        if (element.goingDown)
        {
            pos.y += adjustedTick;
            if (pos.y >= SCREEN_COORD_BOTTOM (20.0f)) element.goingDown = false;
        }
        else
        {
            pos.y -= adjustedTick;
            if (pos.y < 0.0f) element.goingDown = true;
        }
    }
}

void
EffectDrawHandler::ClearScreensaverHUDMap ()
{
    positions.clear ();
}

CRGBA
EffectDrawHandler::GetTextColor () const
{
    CRGBA color (textColor);

    if (textFlashingThisFrame) color = flashColor;

    if (!effect->IsRunning () || !effect->DoesEffectDrawTimer ())
        color = disabledColor;

    if (CMenuSystem::num_menus_in_use && DRAW_LEFT) color.a = 20;

    return color;
};

CRGBA
EffectDrawHandler::GetDropShadowColor ()
{
    CRGBA color (color::Black);

    if (CMenuSystem::num_menus_in_use && DRAW_LEFT) color.a = 20;

    return color;
};

CRGBA
EffectDrawHandler::GetEffectColor () const
{
    return ColorHelper::GetForegroundColor ();
};
