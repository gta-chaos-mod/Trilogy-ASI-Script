#include "ColorHelper.h"

#include "util/Config.h"
#include "util/GenericUtil.h"

void
ColorHelper::UpdateRainbowColor ()
{
    rainbowHueShift += GenericUtil::CalculateTick (0.025f);
    rainbowHueShift = fmod (rainbowHueShift, 360.0f);
}

CRGBA
ColorHelper::GetAdjustedColor (CRGBA color, float value)
{
    if (!Config::GetOrDefault ("Drawing.RainbowColors", true)) return color;

    CRGBA tempColor = CRGBA (color);

    int r = tempColor.r;
    int g = tempColor.g;
    int b = tempColor.b;

    ColorHelper::HueShift (r, g, b, rainbowHueShift, value);

    tempColor.r = r;
    tempColor.g = g;
    tempColor.b = b;

    return tempColor;
}

CRGBA
ColorHelper::GetForegroundColor ()
{
    return GetAdjustedColor (CHAOS_FOREGROUND_COLOR, 0.8f);
}

CRGBA
ColorHelper::GetBackgroundColor ()
{
    return GetAdjustedColor (CHAOS_BACKGROUND_COLOR, 0.4f);
}

void
ColorHelper::RGBtoHSV (float fR, float fG, float fB, float &fH, float &fS,
                       float &fV)
{
    float fCMax  = std::max (std::max (fR, fG), fB);
    float fCMin  = std::min (std::min (fR, fG), fB);
    float fDelta = fCMax - fCMin;

    if (fDelta > 0.0f)
    {
        if (fCMax == fR)
        {
            fH = 60.0f * (fmod (((fG - fB) / fDelta), 6.0f));
        }
        else if (fCMax == fG)
        {
            fH = 60.0f * (((fB - fR) / fDelta) + 2.0f);
        }
        else if (fCMax == fB)
        {
            fH = 60.0f * (((fR - fG) / fDelta) + 4.0f);
        }

        if (fCMax > 0.0f)
        {
            fS = fDelta / fCMax;
        }
        else
        {
            fS = 0.0f;
        }

        fV = fCMax;
    }
    else
    {
        fH = 0.0f;
        fS = 0.0f;
        fV = fCMax;
    }

    if (fH < 0.0f)
        fH += 360.0f;
    else if (fH >= 360.0f)
        fH -= 360.0f;
}

void
ColorHelper::HSVtoRGB (float &fR, float &fG, float &fB, float fH, float fS,
                       float fV)
{
    float fC      = fV * fS; // Chroma
    float fHPrime = fmod (fH / 60.0f, 6.0f);
    float fX      = fC * (1 - fabs (fmod (fHPrime, 2.0f) - 1.0f));
    float fM      = fV - fC;

    if (0.0f <= fHPrime && fHPrime < 1.0f)
    {
        fR = fC;
        fG = fX;
        fB = 0.0f;
    }
    else if (1.0 <= fHPrime && fHPrime < 2.0f)
    {
        fR = fX;
        fG = fC;
        fB = 0.0f;
    }
    else if (2.0f <= fHPrime && fHPrime < 3.0f)
    {
        fR = 0.0f;
        fG = fC;
        fB = fX;
    }
    else if (3.0f <= fHPrime && fHPrime < 4.0f)
    {
        fR = 0.0f;
        fG = fX;
        fB = fC;
    }
    else if (4.0f <= fHPrime && fHPrime < 5.0f)
    {
        fR = fX;
        fG = 0.0f;
        fB = fC;
    }
    else if (5.0f <= fHPrime && fHPrime <= 6.0f)
    {
        fR = fC;
        fG = 0.0f;
        fB = fX;
    }
    else
    {
        fR = 0.0f;
        fG = 0.0f;
        fB = 0.0f;
    }

    fR += fM;
    fG += fM;
    fB += fM;
}

void
ColorHelper::HueShift (int &r, int &g, int &b, float shift, float value)
{
    float fR = (float) r / 255;
    float fG = (float) g / 255;
    float fB = (float) b / 255;

    float h, s, v;
    RGBtoHSV (fR, fG, fB, h, s, v);

    h += shift;
    if (h > 360.0f) h -= 360.0f;

    float retR, retG, retB;
    HSVtoRGB (retR, retG, retB, h, value, value);

    r = (int) (retR * 255);
    g = (int) (retG * 255);
    b = (int) (retB * 255);
}