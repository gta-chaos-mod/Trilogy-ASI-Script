#include "util/EffectBase.h"
#include "util/Globals.h"
#include "util/hooks/HookMacros.h"

#include <CFont.h>
#include <CText.h>

class ReplaceAllTextEffect : public EffectBase
{
    static inline std::string replacementText = "Shoutouts to SimpleFlips.";

    std::string text = "";

public:
    ReplaceAllTextEffect (std::string text)
    {
        this->text = text;
    }

    void
    OnStart (EffectInstance *inst) override
    {
        replacementText                        = text;
        Globals::replaceAllTextString          = text;
        Globals::isReplaceAllTextEffectEnabled = true;

        HOOK_METHOD_ARGS (inst, Hooked_CText_Get, char *(CText *, char *),
                          0x6A0050);

        HOOK_ARGS (inst, Hooked_PrintMoney, char (float, float, char *),
                   0x58F607);

        HOOK_ARGS (inst, Hooked_PrintClockAndAmmo, char (float, float, char *),
                   0x58EC21, 0x58962A);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        Globals::isReplaceAllTextEffectEnabled = false;
    }

    static char *
    Hooked_CText_Get (auto &&cb, CText *text, char *key)
    {
        return (char *) replacementText.c_str ();
    }

    static char
    Hooked_PrintClockAndAmmo (auto &&cb, float x, float y, char *&text)
    {
        text = (char *) replacementText.c_str ();

        CFont::SetProportional (true);
        char result = cb ();
        CFont::SetProportional (false);

        return result;
    }

    static char
    Hooked_PrintMoney (auto &&cb, float x, float y, char *&text)
    {
        std::string textWithDollar ("$");
        textWithDollar.append (replacementText);

        text = (char *) textWithDollar.c_str ();

        CFont::SetProportional (true);
        char result = cb ();
        CFont::SetProportional (false);

        return result;
    }
};

// clang-format off
DEFINE_EFFECT (ReplaceAllTextEffect, "effect_replace_all_text_simpleflips",     GROUP_REPLACE_ALL_TEXT, "Shoutouts To SimpleFlips.");
DEFINE_EFFECT (ReplaceAllTextEffect, "effect_replace_all_text_queer_rights",    GROUP_REPLACE_ALL_TEXT, "Queer Rights!");
// clang-format on