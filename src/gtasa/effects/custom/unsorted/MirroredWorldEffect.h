#pragma once

#include "util/EffectBase.h"

class MirroredWorldEffect : public EffectBase
{
	static RwRaster* raster;
	static RwIm2DVertex vertices[4];

	static void ResetRaster();

	static __int16 __fastcall HookedGetSteeringLeftRight(CPad* thisPad);
	static __int16 __fastcall HookedPedWalkLeftRight(CPad* thisPad);
	static char __fastcall HookedGedLookLeft(CPad* thisPad);
	static char __fastcall HookedGedLookRight(CPad* thisPad);
	static int HookedSetVertices(int primType, RwD3D9Vertex* vertices, int numVertices);

public:
	MirroredWorldEffect();

	void InitializeHooks() override;

	void Enable() override;
	void Disable() override;

	static void RenderEffectsEvent();
};
