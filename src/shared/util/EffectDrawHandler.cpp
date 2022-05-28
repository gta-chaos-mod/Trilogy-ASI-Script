#include "EffectDrawHandler.h"

#include "util/Config.h"
#include "util/DrawHelper.h"
#include "util/EffectHandler.h"
#include "util/EffectInstance.h"
#include "util/EffectTwitchHandler.h"
#include "util/GenericUtil.h"
#include "util/Globals.h"

#include <algorithm>

#include <CFont.h>
#include <extensions/FontPrint.h>

bool
EffectDrawHandler::AreEffectsInset (int num)
{
    int i = 0;
    for (const auto &effect : EffectHandler::GetActiveEffects ())
    {
        if (++i > num) return false;

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

#ifdef GTASA
    CFont::SetScaleForCurrentlanguage (TEXT_SCALE_X, TEXT_SCALE_Y);
    float renderWidth = CFont::GetStringWidth (const_cast<char *> (
                                                   effect->GetName ().data ()),
                                               true, false);
#elif GTAVC
    CFont::SetScale (TEXT_SCALE_X, TEXT_SCALE_Y);
    std::string_view name        = effect->GetName ();
    float            renderWidth = CFont::GetStringWidth (
                   (wchar_t *) std::wstring (name.begin (), name.end ()).c_str (), true);
#elif GTA3
    CFont::SetScale (TEXT_SCALE_X, TEXT_SCALE_Y);
    float renderWidth
        = CFont::GetStringWidth (effect->GetName ().data (), true);
#endif

    x = GenericUtil::EaseOutBack (transitionTimer, -renderWidth, position);
    y = ((idx + 1) * 65.0f) + 240.0f;
}

void
EffectDrawHandler::PrintEffectName ()
{
    gamefont::Print (gamefont::RightBottom, gamefont::AlignRight,
                     std::string (effect->GetName ()), x, y, FONT_DEFAULT, 1.0f,
                     1.2f, GetTextColor (), 1, color::Black, true);
}

void
EffectDrawHandler::PrintSubtext ()
{
    if (effect->HasSubtext ())
    {
        gamefont::Print (gamefont::RightBottom, gamefont::AlignRight,
                         std::string (effect->GetSubtext ()), x, y - 30.0f,
                         FONT_DEFAULT, 0.8f, 1.0f, GetTextColor (), 1,
                         color::Black, true);
    }
}

void
EffectDrawHandler::PrintEffectTimer ()
{
    if (Config::GetOrDefault ("Drawing.DrawCircles", true))
    {
        if (effect->HasSubtext ()) y -= 10.0f;

        CVector2D center
            = CVector2D (SCREEN_COORD_RIGHT (x) + SCREEN_COORD (50.0f),
                         SCREEN_COORD_BOTTOM (y) + SCREEN_COORD (20.0f));

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
                                CHAOS_BACKGROUND_COLOR);

        DrawHelper::DrawCircle (center, SCREEN_MULTIPLIER (20.0f), angle,
                                GetEffectColor ());

        int actualRemaining
            = effect->GetEffectRemaining () / Globals::effectTimerSpeed;
        if (actualRemaining < 60000)
        {
            gamefont::Print (gamefont::RightBottom, gamefont::AlignRight,
                             GenericUtil::FormatTime (actualRemaining, true),
                             x - 57.0f, y - 2.0f, FONT_DEFAULT, 0.6f, 1.0f,
                             color::White, 1, color::Black, true, 9999.0f,
                             false);
        }
    }
    else
    {
        gamefont::Print (gamefont::RightBottom, gamefont::AlignRight,
                         GenericUtil::FormatTime (
                             effect->GetEffectRemaining ()),
                         x - 60.0f, y - 10.0f, FONT_DEFAULT, 0.6f, 0.8f,
                         GetTextColor (), 1, color::White, true, 9999.0f,
                         false);
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
    PrintEffectName ();
    PrintSubtext ();

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
    if (size <= NUM_RECENT_EFFECTS) return;

    int more = 0;
    for (int i = NUM_RECENT_EFFECTS; i < size; i++)
    {
        auto &effect = effects[i];
        if (effect.IsRunning ()) more++;
    }

    if (more == 0) return;

    std::string text = "And " + std::to_string (more) + " more...";

    y = ((NUM_RECENT_EFFECTS + 2) * 65.0f) + 240.0f - 20.0f;

    gamefont::Print (gamefont::RightBottom, gamefont::AlignRight, text, x, y,
                     FONT_DEFAULT, 0.8f, 1.0f, color::DarkGray, 1, color::Black,
                     true);
}

void
EffectDrawHandler::DrawRecentEffects (int num)
{
    bool inset = AreEffectsInset (num);

    int i = 0;
    for (auto &effect : EffectHandler::GetActiveEffects ())
    {
        if (++i > num) break;

        effect.Draw (i, inset);
    }

    DrawAndXMore ();
}
CRGBA
EffectDrawHandler::GetTextColor () const
{
    if (textFlashingThisFrame) return flashColor;

    if (!effect->IsRunning () || !effect->DoesEffectDrawTimer ())
        return disabledColor;

    return textColor;
};

CRGBA
EffectDrawHandler::GetEffectColor () const
{
    return CHAOS_FOREGROUND_COLOR;
};
