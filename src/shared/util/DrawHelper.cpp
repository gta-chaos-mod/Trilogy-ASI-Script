#include "DrawHelper.h"

int         DrawHelper::remaining = 0;
int         DrawHelper::cooldown  = 0;
std::string DrawHelper::mode      = "";

std::string
DrawHelper::GetCooldownString ()
{
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
DrawHelper::Draw ()
{
    DrawVersion ();

    if (Config::GetOrDefault ("Drawing.Enabled", true))
    {
        if (Config::GetOrDefault ("Drawing.DrawRemainingTimeBar", true))
        {
            DrawTopBar ();
        }
        if (Config::GetOrDefault ("Drawing.DrawActiveEffects", true))
        {
            DrawRecentEffects ();
        }
        if (Config::GetOrDefault ("Drawing.DrawVoting", true))
        {
            DrawVoting::DrawVotes ();
        }
    }
}

void
DrawHelper::DrawVersion ()
{
    if (GenericUtil::IsMenuActive () && KeyPressed (VK_F7))
    {
        gamefont::Print (gamefont::LeftBottom, gamefont::AlignLeft,
                         GenericUtil::GetModVersion (), 20.0f, 60.0f,
                         FONT_DEFAULT, 1.0f, 1.8f, CRGBA (255, 255, 255, 255),
                         2, CRGBA (0, 0, 0, 255), true);
    }
}

void
DrawHelper::DrawTopBar ()
{
    float maxWidth = SCREEN_WIDTH - SCREEN_COORD (8.0f);
    float barWidth = CalculateBarWidth () - SCREEN_COORD (8.0f);

    barWidth = std::max (0.0f, std::min (barWidth, maxWidth));

    CRect rect = CRect (0.0f, -1.0f, SCREEN_WIDTH, SCREEN_COORD_TOP (30.0f));
    CSprite2d::DrawRect (rect, CRGBA (0, 0, 0, 255));

    rect = CRect (SCREEN_COORD_LEFT (4.0f), SCREEN_COORD_TOP (4.0f),
                  SCREEN_WIDTH - SCREEN_COORD (4.0f), SCREEN_COORD_TOP (26.0f));
    CSprite2d::DrawRect (rect, CRGBA (25, 75, 128, 200));

    rect = CRect (SCREEN_COORD_LEFT (4.0f), SCREEN_COORD_TOP (4.0f),
                  barWidth + SCREEN_COORD (4.0f), SCREEN_COORD_TOP (26.0f));
    CSprite2d::DrawRect (rect, CRGBA (50, 150, 255, 200));

    float x = SCREEN_COORD_CENTER_X;
    gamefont::PrintUnscaled (GetCooldownString (), x, SCREEN_MULTIPLIER (2.0f),
                             FONT_DEFAULT, SCREEN_MULTIPLIER (0.8f),
                             SCREEN_MULTIPLIER (0.8f),
                             CRGBA (255, 255, 255, 255), gamefont::AlignCenter,
                             1, CRGBA (0, 0, 0, 255), true, 9999.0F, false);

#ifdef GTASA
    CFont::SetProportional (true);
#else
    CFont::SetPropOn ();
#endif
}

void
DrawHelper::DrawRecentEffects ()
{
    if (GenericUtil::IsMenuActive ())
    {
        return;
    }

    int  i       = 1;
    bool isInset = false;
    for (EffectBase *effect : EffectDatabase::GetActiveEffects ())
    {
        if (i > 5)
        {
            break;
        }

        if (!effect->IsPlaceholder ()
            && (effect->IsEnabled () || effect->IsDisabledForMissions ()))
        {
            isInset = true;
            break;
        }
    }

    i = 1;
    for (EffectBase *effect : EffectDatabase::GetActiveEffects ())
    {
        if (i > 5)
        {
            break;
        }

        bool timedEffect
            = !effect->IsPlaceholder ()
              && (effect->IsEnabled () || effect->IsDisabledForMissions ());

        float position = isInset ? 90.0f : 25.0f;

#ifdef GTASA
        CFont::SetScaleForCurrentlanguage (1.0f, 1.2f);
        float renderWidth
            = CFont::GetStringWidth (
                  (char *) effect->GetDescription ().c_str (), true, false)
              + position;
#elif GTAVC
        CFont::SetScale (1.0f, 1.2f);
        std::string description = effect->GetDescription ();
        float       renderWidth = CFont::GetStringWidth (
                                (wchar_t *) std::wstring (description.begin (),
                                                          description.end ())
                                    .c_str (),
                                true)
                            + position;
#elif GTA3
        CFont::SetScale (1.0f, 1.2f);
        float renderWidth
            = CFont::GetStringWidth (
                  (char *) effect->GetDescription ().c_str (), true)
              + position;
#endif
        float offsetWidth
            = effect->CalculateFadeInOffset (renderWidth + position);

        float x = offsetWidth - renderWidth;
        float y = ((i + 1) * 65.0f) + 240.0f;

        gamefont::Print (gamefont::RightBottom, gamefont::AlignRight,
                         effect->GetDescription (), x, y, FONT_DEFAULT, 1.0f,
                         1.2f, effect->GetTextColor (), 1, CRGBA (0, 0, 0, 255),
                         true);

        // Draw voter
        if (effect->HasTwitchVoter ())
        {
            gamefont::Print (gamefont::RightBottom, gamefont::AlignRight,
                             effect->GetTwitchVoter (), x, y - 30.0f,
                             FONT_DEFAULT, 0.8f, 1.0f, effect->GetTextColor (),
                             1, CRGBA (0, 0, 0, 255), true);
        }

        // Draw timed effect circle
        if (timedEffect)
        {
            if (Config::GetOrDefault ("Drawing.DrawCircles", true))
            {
                if (effect->HasTwitchVoter ())
                {
                    y -= 10.0f;
                }

                CVector2D center
                    = CVector2D (SCREEN_COORD_RIGHT (x) + SCREEN_COORD (50.0f),
                                 SCREEN_COORD_BOTTOM (y)
                                     + SCREEN_COORD (20.0f));

                RwTextureFilterMode filter        = rwFILTERLINEAR;
                int                 alphaBlending = true;

                RwRenderStateSet (rwRENDERSTATEVERTEXALPHAENABLE,
                                  &alphaBlending);
                RwRenderStateSet (rwRENDERSTATETEXTUREFILTER,
                                  (void *) (filter));
                RwRenderStateSet (rwRENDERSTATETEXTURERASTER, NULL);

                float angle = (float) effect->GetEffectRemaining ()
                              / (float) effect->GetEffectDuration () * 360.0f;

                DrawHelper::DrawCircle (center, SCREEN_MULTIPLIER (24.0f),
                                        360.0f, CRGBA (255, 255, 255, 255));

#ifdef GTASA
                CRGBA backgroundColor = CRGBA (0, 83, 117, 255);
#elif GTAVC
                CRGBA backgroundColor = CRGBA (110, 0, 77, 255);
#elif GTA3
                CRGBA backgroundColor = CRGBA (110, 56, 0, 255);
#endif

                DrawHelper::DrawCircle (center, SCREEN_MULTIPLIER (20.0f),
                                        360.0f, backgroundColor);

                DrawHelper::DrawCircle (center, SCREEN_MULTIPLIER (20.0f),
                                        angle, effect->GetEffectColor ());

                if (effect->GetEffectRemaining () <= 60000)
                {
                    gamefont::Print (
                        gamefont::RightBottom, gamefont::AlignRight,
                        GenericUtil::FormatTime (effect->GetEffectRemaining (),
                                                 true),
                        x - 57.0f, y - 2.0f, FONT_DEFAULT, 0.6f, 1.0f,
                        CRGBA (255, 255, 255, 200), 1, CRGBA (0, 0, 0, 200),
                        true, 9999.0f, false);
                }
            }
            else
            {
                gamefont::Print (gamefont::RightBottom, gamefont::AlignRight,
                                 GenericUtil::FormatTime (
                                     effect->GetEffectRemaining ()),
                                 x - 60.0f, y - 10.0f, FONT_DEFAULT, 0.6f, 0.8f,
                                 effect->GetTextColor (), 1,
                                 CRGBA (0, 0, 0, 255), true, 9999.0f, false);
            }
        }

        i++;
    }

#ifdef GTASA
    CFont::SetProportional (true);
#else
    CFont::SetPropOn ();
#endif
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
    float step = ((float) deg2rad (pie)) / (numCount - 1);
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
    RwIm2DVertexSetRealRGBA (&vertices[index], color.r, color.g, color.b,
                             color.a);
    vertices[index].x = coord.x;
    vertices[index].y = coord.y;
    vertices[index].z = 0;
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
