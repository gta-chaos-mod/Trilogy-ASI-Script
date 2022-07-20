#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <regex>

#include <CText.h>

class ButtsbotEffect : public EffectBase
{
    static const inline double BUTT_FREQUENCY = 8;

    static inline std::string lowerReplacement    = "butt";
    static inline std::string upperReplacement    = "Butt";
    static inline std::string allUpperReplacement = "BUTT";

    static inline std::map<char *, std::string> buttMap = {};

    static inline EffectInstance *instance = nullptr;

    template <typename Out>
    static void
    split (const std::string &s, char delim, Out result)
    {
        std::istringstream iss (s);
        std::string        item;
        while (std::getline (iss, item, delim))
        {
            *result++ = item;
        }
    }

    static std::vector<std::string>
    split (const std::string &s, char delim)
    {
        std::vector<std::string> elems;
        split (s, delim, std::back_inserter (elems));
        return elems;
    }

public:
    void
    OnStart (EffectInstance *inst) override
    {
        buttMap = {};

        HOOK_METHOD_ARGS (inst, Hooked_CText_Get, char *(CText *, char *),
                          0x6A0050);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        instance = inst;
    }

    static std::string
    ReplaceWithButt (std::string word)
    {
        std::regex groupRegex (
            "^([a-z]\\w+)|([A-Z])\\W+|([A-Z][a-z]+)|([A-Z][A-Z]+)");

        std::smatch match;
        std::regex_search (word, match, groupRegex);

        if (match.ready () && !match.empty ())
        {
            // All lowercase
            if (match.size () > 1 && match[1].matched)
            {
                return std::regex_replace (word, std::regex (match[1].str ()),
                                           lowerReplacement);
            }

            // Single word uppercase
            if (match.size () > 2 && match[2].matched)
            {
                return std::regex_replace (word, std::regex (match[2].str ()),
                                           upperReplacement);
            }

            // Starting with uppercase, rest lowercase
            if (match.size () > 3 && match[3].matched)
            {
                return std::regex_replace (word, std::regex (match[3].str ()),
                                           upperReplacement);
            }

            // All uppercase
            if (match.size () > 4 && match[4].matched)
            {
                return std::regex_replace (word, std::regex (match[4].str ()),
                                           allUpperReplacement);
            }
        }

        // Just return the normal word if we can't replace it properly.
        return word;
    }

    static int
    GetRandomVectorPosition (std::vector<std::string> strings,
                             std::set<int>            exclude)
    {
        int random = instance->Random (0, (int) strings.size () - 1);

        return exclude.contains (random)
                   ? GetRandomVectorPosition (strings, exclude)
                   : random;
    }

    static char *
    Buttify (char *text)
    {
        if (buttMap.contains (text)) return (char *) buttMap[text].c_str ();

        std::string strText (text);
        if (strText.empty ()
            || strText.find_first_of (" ") == std::string::npos)
        {
            return text;
        }

        std::vector<std::string> splitText = split (strText, ' ');

        if (splitText.size () > 1)
        {
            int buttFrequency
                = (int) std::ceil (splitText.size () / BUTT_FREQUENCY);

            std::set<int> exclude = {};
            for (int i = 0; i < buttFrequency; i++)
            {
                int random = GetRandomVectorPosition (splitText, exclude);

                splitText[random] = ReplaceWithButt (splitText[random]);

                exclude.insert (random);
            }
        }

        std::string buttText = splitText[0];
        if (splitText.size () > 1)
        {
            for (int i = 1; i < splitText.size (); i++)
            {
                buttText.append (" ").append (splitText[i]);
            }
        }

        buttMap[text] = buttText;

        return (char *) buttMap[text].c_str ();
    }

    static char *
    Hooked_CText_Get (auto &&cb, CText *text, char *key)
    {
        char *textToRender = cb ();

        return Buttify (textToRender);
    }
};

DEFINE_EFFECT (ButtsbotEffect, "effect_buttsbot", 0);