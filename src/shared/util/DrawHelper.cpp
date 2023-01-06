#include "DrawHelper.h"

#include "util/ColorHelper.h"
#include "util/Config.h"
#include "util/DrawVoting.h"
#include "util/EffectDrawHandler.h"
#include "util/EffectHandler.h"
#include "util/EffectInstance.h"
#include "util/GenericUtil.h"
#include "util/Globals.h"
#include "util/MathHelper.h"

#include <CFont.h>
#include <CTimer.h>
#include <extensions/FontPrint.h>

std::string
DrawHelper::GetCooldownString ()
{
    if (Globals::isReplaceAllTextEffectEnabled)
        return Globals::replaceAllTextString;

    std::string cooldown;
    if (mode != "")
    {
        cooldown.append (mode);
        cooldown.append (": ");
    }
    cooldown.append (GenericUtil::FormatTime (remaining));
    return cooldown;
}

float
DrawHelper::CalculateBarWidth ()
{
    return (SCREEN_WIDTH / cooldown * remaining);
}

void
DrawHelper::UpdateCooldown (int _remaining, int _cooldown, std::string _mode)
{
    remaining = _remaining;
    cooldown  = _cooldown;
    mode      = _mode;
}

void
DrawHelper::Tick ()
{
    EffectDrawHandler::Tick ();
}

void
DrawHelper::Draw ()
{
    ColorHelper::UpdateRainbowColor ();

    DrawVersion ();

    if (Config::GetOrDefault ("Drawing.Enabled", true))
    {
        bool drawActiveEffects
            = Config::GetOrDefault ("Drawing.DrawActiveEffects", true);

        if (!Globals::isHideChaosUIEffectEnabled)
        {
            if (Config::GetOrDefault ("Drawing.DrawRemainingTimeBar", true))
            {
                DrawTopBar ();
            }

            if (drawActiveEffects)
            {
                DrawRecentEffects ();
            }

            if (Config::GetOrDefault ("Drawing.DrawVoting", true))
            {
                DrawVoting::DrawVotes ();
            }
        }
        else if (drawActiveEffects)
        {
            DrawRecentEffects ();
        }
    }
}

void
DrawHelper::DrawVersion ()
{
    if (GenericUtil::IsMenuActive () && KeyPressed (VK_F7))
    {
        std::string version{GenericUtil::GetModVersion ()};
#ifdef GTASA
        int lines = CFont::GetNumberLines (0.0f, 0.0f, version.data ());
#else
        int lines = CFont::GetNumberLines (
            0.0f, 0.0f,
            std::wstring (version.begin (), version.end ()).c_str ());
#endif
        gamefont::Print (gamefont::LeftBottom, gamefont::AlignLeft, version,
                         20.0f, lines * 50.0f,
                         FONT_DEFAULT, 1.0f, 1.4f, color::White, 2,
                         color::Black, true);
    }
}

void
DrawHelper::DrawTopBar ()
{
    // Calculate the width of the inner timer bar
    float maxWidth = SCREEN_WIDTH - SCREEN_COORD (8.0f);
    float barWidth = CalculateBarWidth () - SCREEN_COORD (8.0f);

    barWidth = std::max (0.0f, std::min (barWidth, maxWidth));

    // Draw black background bar
    // The reason the top left has to be -1,-1
    // is because otherwise there'd be a 1px gap
    CRect rect = CRect (-1.0f, -1.0f, SCREEN_WIDTH, SCREEN_COORD_TOP (30.0f));
    CSprite2d::DrawRect (rect, color::Black);

    // Draw inner, dark bar
    rect = CRect (SCREEN_COORD_LEFT (4.0f), SCREEN_COORD_TOP (4.0f),
                  SCREEN_WIDTH - SCREEN_COORD (4.0f), SCREEN_COORD_TOP (26.0f));
    CSprite2d::DrawRect (rect, ColorHelper::GetBackgroundColor ());

    // Draw filled bar
    rect = CRect (SCREEN_COORD_LEFT (4.0f), SCREEN_COORD_TOP (4.0f),
                  barWidth + SCREEN_COORD (4.0f), SCREEN_COORD_TOP (26.0f));
    CSprite2d::DrawRect (rect, ColorHelper::GetForegroundColor ());

    // Draw time centered
    float x = SCREEN_COORD_CENTER_X;
    gamefont::PrintUnscaled (GetCooldownString (), x, SCREEN_MULTIPLIER (2.0f),
                             FONT_DEFAULT, SCREEN_MULTIPLIER (0.8f),
                             SCREEN_MULTIPLIER (0.8f), color::White,
                             gamefont::AlignCenter, 1, color::Black, true,
                             9999.0F, true);

#ifdef GTASA
    CFont::SetProportional (true);
#else
    CFont::SetPropOn ();
#endif
}

void
DrawHelper::DrawRecentEffects ()
{
    if (GenericUtil::IsMenuActive ()) return;

    EffectDrawHandler::DrawRecentEffects ();
}

// ######################################################
/* Drawing Circles! - Big thanks to Parik for the code */
static const int    numVertices = 60;
static RwIm2DVertex vertices[numVertices];

void
DrawHelper::DrawCircle (CVector2D position, float radius, float angle,
                        CRGBA color)
{
    AppendPie (vertices, numVertices, radius, position, angle, color, 0);
    RwIm2DRenderPrimitive (rwPRIMTYPETRIFAN, vertices, numVertices);
}

void
DrawHelper::AppendPie (RwIm2DVertex *vertices, int numCount, float radius,
                       CVector2D center, float pie, CRGBA color,
                       float baseRotation)
{
    numCount--;
    float step = (MathHelper::ToRadians (pie)) / (numCount - 1);
    Append (vertices, 0, CVector2D (0, 0), color);
    for (int i = 0; i < numCount; i++)
    {
        float rotation = baseRotation + step * i;
        Append (vertices + 1, i, CVector2D (0, -radius), color);
        Rotate (vertices + i + 1, 1, CVector2D (0, 0), rotation);
    }
    Transform (vertices, numCount + 1, center);
}

void
DrawHelper::Transform (RwIm2DVertex *vertices, int numCount,
                       CVector2D transformation)
{
    for (int i = 0; i < numCount; i++)
    {
        vertices[i].x += transformation.x;
        vertices[i].y += transformation.y;
    }
}

void
DrawHelper::Append (RwIm2DVertex *vertices, int index, CVector2D coord,
                    CRGBA color, RwReal u, RwReal v)
{
    vertices[index].u = u;
    vertices[index].v = v;
    RwIm2DVertexSetIntRGBA (&vertices[index], color.r, color.g, color.b,
                            color.a);
    vertices[index].x = coord.x;
    vertices[index].y = coord.y;
#ifndef GTA3
    vertices[index].z = CSprite2d::NearScreenZ;
#endif
    vertices[index].rhw = CSprite2d::RecipNearClip;
}

void
DrawHelper::Rotate (RwIm2DVertex *vertices, int numCount, CVector2D origin,
                    float angle)
{
    for (int i = 0; i < numCount; i++)
    {
        float tempx = vertices[i].x - origin.x;
        float tempy = vertices[i].y - origin.y;

        vertices[i].x = origin.x + tempx * cos (angle) - tempy * sin (angle);
        vertices[i].y = origin.y + tempx * sin (angle) + tempy * cos (angle);
    }
}
