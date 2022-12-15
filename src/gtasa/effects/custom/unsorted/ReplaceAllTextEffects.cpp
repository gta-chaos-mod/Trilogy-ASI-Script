#include "util/EffectBase.h"
#include "util/Globals.h"
#include "util/hooks/HookMacros.h"

#include <CFont.h>
#include <CText.h>

class ReplaceAllTextEffect : public EffectBase
{
    static inline std::string replacementText = "Your Text Could Be Here";

public:
    void
    OnStart (EffectInstance *inst) override
    {
        replacementText = CONFIG ("Effects.ReplaceAllText.Text",
                                  (std::string) "Your Text Could Be Here");

        Globals::replaceAllTextString          = replacementText;
        Globals::isReplaceAllTextEffectEnabled = true;

        HOOK_METHOD_ARGS (inst, Hooked_CKeyArray_Search,
                          char *(CText *, unsigned __int8 *, int), 0x6A0070,
                          0x6A00A4);

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
    Hooked_CKeyArray_Search (auto &&cb, CText *text, unsigned __int8 *key,
                             int pFound)
    {
        char *textToRender = cb ();

        if (textToRender != nullptr && pFound)
        {
            return (char *) replacementText.c_str ();
        }

        return textToRender;
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

DEFINE_EFFECT (ReplaceAllTextEffect, "effect_replace_all_text", 0);