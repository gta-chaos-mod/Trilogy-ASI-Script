#pragma once

class ColorHelper
{
    static inline float rainbowHueShift = 0.0f;

public:
    static void UpdateRainbowColor ();

    static CRGBA GetAdjustedColor (CRGBA color, float value);

    static CRGBA GetForegroundColor ();

    static CRGBA GetBackgroundColor ();

    static void RGBtoHSV (float fR, float fG, float fB, float &fH, float &fS,
                          float &fV);

    static void HSVtoRGB (float &fR, float &fG, float &fB, float fH, float fS,
                          float fV);

    static void HueShift (int &r, int &g, int &b, float shift, float value);
};
