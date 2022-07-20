#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <filesystem>

#include <CFont.h>

class CustomFontEffect : public EffectBase
{
    std::string fileName = "";

    static inline std::string staticFileName = "";

public:
    CustomFontEffect (std::string fileName)
    {
        this->fileName = fileName;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        if (fileName.empty () || !FileExists (fileName)
            || !FileExists ("fonts.dat"))
        {
            inst->Disable ();
            return;
        }

        staticFileName = fileName;

        HOOK_ARGS (inst, Hooked_CTxdStore_LoadTxd, bool (int, char *),
                   0x5BA6A4);

        HOOK_ARGS (inst, Hooked_LoadFontsDat,
                   FILE * (const char *, const char *), 0x7187DB);

        CFont::Shutdown ();
        CFont::Initialise ();
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        CFont::Shutdown ();
        CFont::Initialise ();
    }

    bool
    FileExists (std::string fileName)
    {
        std::string file = "ChaosMod/" + fileName;
        std::string path = GAME_PATH ((char *) file.c_str ());

        return std::filesystem::exists (path);
    }

    static bool
    Hooked_CTxdStore_LoadTxd (auto &&cb, int index, char *&filename)
    {
        std::string txdPath ("ChaosMod\\");
        txdPath.append (staticFileName);

        filename = (char *) txdPath.c_str ();

        return cb ();
    }

    static FILE *
    Hooked_LoadFontsDat (auto &&cb, const char *&path, const char *access)
    {
        path = "ChaosMod\\fonts.dat";

        return cb ();
    }
};

// clang-format off
DEFINE_EFFECT (CustomFontEffect, "effect_font_comic_sans",  GROUP_CUSTOM_FONT, "font_comic_sans.txd");
DEFINE_EFFECT (CustomFontEffect, "effect_font_mario_64",    GROUP_CUSTOM_FONT, "font_mario_64.txd");
DEFINE_EFFECT (CustomFontEffect, "effect_font_yakuza",      GROUP_CUSTOM_FONT, "font_yakuza.txd");
// clang-format on