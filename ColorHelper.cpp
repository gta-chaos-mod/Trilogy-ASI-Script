#include "ColorHelper.h"

/*! \brief Convert RGB to HSV color space

  Converts a given set of RGB values `r', `g', `b' into HSV
  coordinates. The input RGB values are in the range [0, 1], and the
  output HSV values are in the ranges h = [0, 360], and s, v = [0,
  1], respectively.

  \param fR Red component, used as input, range: [0, 1]
  \param fG Green component, used as input, range: [0, 1]
  \param fB Blue component, used as input, range: [0, 1]
  \param fH Hue component, used as output, range: [0, 360]
  \param fS Hue component, used as output, range: [0, 1]
  \param fV Hue component, used as output, range: [0, 1]

*/
void ColorHelper::RGBtoHSV(float fR, float fG, float fB, float& fH, float& fS, float& fV) {
	float fCMax = max(max(fR, fG), fB);
	float fCMin = min(min(fR, fG), fB);
	float fDelta = fCMax - fCMin;

	if (fDelta > 0.0f) {
		if (fCMax == fR) {
			fH = 60.0f * (fmod(((fG - fB) / fDelta), 6.0f));
		}
		else if (fCMax == fG) {
			fH = 60.0f * (((fB - fR) / fDelta) + 2.0f);
		}
		else if (fCMax == fB) {
			fH = 60.0f * (((fR - fG) / fDelta) + 4.0f);
		}

		if (fCMax > 0.0f) {
			fS = fDelta / fCMax;
		}
		else {
			fS = 0.0f;
		}

		fV = fCMax;
	}
	else {
		fH = 0.0f;
		fS = 0.0f;
		fV = fCMax;
	}

	if (fH < 0.0f) {
		fH += 360.0f;
	}
	else if (fH >= 360.0f) {
		fH -= 360.0f;
	}
}

/*! \brief Convert HSV to RGB color space

  Converts a given set of HSV values `h', `s', `v' into RGB
  coordinates. The output RGB values are in the range [0, 1], and
  the input HSV values are in the ranges h = [0, 360], and s, v =
  [0, 1], respectively.

  \param fR Red component, used as output, range: [0, 1]
  \param fG Green component, used as output, range: [0, 1]
  \param fB Blue component, used as output, range: [0, 1]
  \param fH Hue component, used as input, range: [0, 360]
  \param fS Hue component, used as input, range: [0, 1]
  \param fV Hue component, used as input, range: [0, 1]

*/
void ColorHelper::HSVtoRGB(float& fR, float& fG, float& fB, float fH, float fS, float fV) {
	float fC = fV * fS; // Chroma
	float fHPrime = fmod(fH / 60.0f, 6.0f);
	float fX = fC * (1 - fabs(fmod(fHPrime, 2.0f) - 1.0f));
	float fM = fV - fC;

	if (0.0f <= fHPrime && fHPrime < 1.0f) {
		fR = fC;
		fG = fX;
		fB = 0.0f;
	}
	else if (1.0 <= fHPrime && fHPrime < 2.0f) {
		fR = fX;
		fG = fC;
		fB = 0.0f;
	}
	else if (2.0f <= fHPrime && fHPrime < 3.0f) {
		fR = 0.0f;
		fG = fC;
		fB = fX;
	}
	else if (3.0f <= fHPrime && fHPrime < 4.0f) {
		fR = 0.0f;
		fG = fX;
		fB = fC;
	}
	else if (4.0f <= fHPrime && fHPrime < 5.0f) {
		fR = fX;
		fG = 0.0f;
		fB = fC;
	}
	else if (5.0f <= fHPrime && fHPrime <= 6.0f) {
		fR = fC;
		fG = 0.0f;
		fB = fX;
	}
	else {
		fR = 0.0f;
		fG = 0.0f;
		fB = 0.0f;
	}

	fR += fM;
	fG += fM;
	fB += fM;
}

void ColorHelper::HueShift(int& r, int& g, int& b, float shift, float value) {
	float fR = (float)r / 255;
	float fG = (float)g / 255;
	float fB = (float)b / 255;

	float h, s, v;
	RGBtoHSV(fR, fG, fB, h, s, v);

	h += shift;
	if (h > 360.0f) {
		h -= 360.0f;
	}

	float retR, retG, retB;
	HSVtoRGB(retR, retG, retB, h, value, value);

	r = (int)(retR * 255);
	g = (int)(retG * 255);
	b = (int)(retB * 255);
}
