#include "GenericUtil.h"

#include "util/Globals.h"
#include "util/Version.h"

std::string
GenericUtil::GetModVersion ()
{
    if (Globals::isShoutoutsToSimpleFlipsEffectEnabled)
        return "Shoutouts to SimpleFlips.";

    std::string version = "Chaos Mod v3.0";

#ifdef _DEBUG
    version.append ("-debug");
#elif VERSION_SUFFIX
    version.append ("-git.").append (VERSION_SUFFIX);
#endif

    return version;
}

double
GenericUtil::CalculateTick (double multiplier)
{
    unsigned diff = CTimer::m_snTimeInMilliseconds
                    - CTimer::m_snPreviousTimeInMilliseconds;

    float timeScale = std::max (0.000001f, CTimer::ms_fTimeScale);

    return diff / timeScale * multiplier;
}

std::string
GenericUtil::FormatTime (int duration, bool onlySeconds)
{
    int seconds = std::max (0, duration) / 1000, minutes = 0;
    while (seconds >= 60)
    {
        minutes += 1;
        seconds -= 60;
    }

    if (minutes > 99)
    {
        minutes = 99;
        seconds = 59;
    }

    std::string time;
    if (!onlySeconds)
    {
        if (minutes < 10) time.append ("0");

        time.append (std::to_string (minutes));
        time.append (":");
    }
    if (seconds < 10) time.append ("0");

    time.append (std::to_string (seconds));
    return time;
}

bool
GenericUtil::IsMenuActive ()
{
#ifdef GTASA
    return FrontEndMenuManager.m_bMenuActive;
#elif GTAVC
    return FrontendMenuManager.m_bMenuVisible;
#elif GTA3
    return FrontEndMenuManager.m_bMenuActive;
#endif
}

float
GenericUtil::EaseOutBack (float t)
{
    t -= 1;
    return 1 + t * t * (2.70158f * t + 1.70158f);
}

float
GenericUtil::EaseInOutQubic (float t)
{
    if (t < 0.5)
        return 4 * t * t * t;
    else
        return 1 - powf (-2 * t + 2, 3) / 2;
}

std::string
GenericUtil::ToUpper (std::string string)
{
    std::transform (string.begin (), string.end (), string.begin (),
                    [] (unsigned char c) { return std::toupper (c); });
    return string;
}
