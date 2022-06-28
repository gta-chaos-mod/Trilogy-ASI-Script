#pragma comment(lib, "d3dx9.lib")

#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <d3dx9.h>

class CustomTexturesEffect : public EffectBase
{
    static inline IDirect3DTexture9 *image        = nullptr;
    static inline std::string        filePath     = "";
    static inline int                loadAttempts = 0;

    const char *fileName = "";

public:
    CustomTexturesEffect (const char *fileName)
    {
        this->fileName = fileName;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        SetImageFile ();

        image        = nullptr;
        loadAttempts = 0;

        HOOK_ARGS (inst, Hooked_D3D9_SetRasterStage,
                   signed int (RwRaster *, int), 0x7FDFDA, 0x4CA8C4, 0x4CA9A6);
    }

    void
    SetImageFile ()
    {
        filePath = std::string ("ChaosMod\\").append (fileName);
    }

    static signed int
    Hooked_D3D9_SetRasterStage (auto &&cb, RwRaster *raster, int stage)
    {
        signed int ret = cb ();

        IDirect3DDevice9 *device = GetD3DDevice ();
        if (!device) return ret;

        if (!image && loadAttempts++ <= 5)
        {
            int width, height;
            LoadTextureFromFile (filePath.c_str (), &image, nullptr, nullptr);
        }

        if (image)
        {
            device->SetTexture (stage, image);
        }

        return ret;
    }

    static bool
    LoadTextureFromFile (const char *filename, PDIRECT3DTEXTURE9 *out_texture,
                         int *out_width, int *out_height)
    {
        PDIRECT3DTEXTURE9 texture;
        HRESULT           hr
            = D3DXCreateTextureFromFileA (GetD3DDevice (), filename, &texture);
        if (hr != S_OK) return false;

        D3DSURFACE_DESC my_image_desc;
        texture->GetLevelDesc (0, &my_image_desc);

        *out_texture = texture;
        if (out_width) *out_width = (int) my_image_desc.Width;
        if (out_height) *out_height = (int) my_image_desc.Height;
        return true;
    }
};

// clang-format off
DEFINE_EFFECT (CustomTexturesEffect, "effect_textures_its_morbin_time",         GROUP_CUSTOM_TEXTURES, "morbin.png");
DEFINE_EFFECT (CustomTexturesEffect, "effect_textures_counter_strike_source",   GROUP_CUSTOM_TEXTURES, "counter_strike_source.png");
DEFINE_EFFECT (CustomTexturesEffect, "effect_textures_custom",                  GROUP_CUSTOM_TEXTURES, "custom.png");
// clang-format on