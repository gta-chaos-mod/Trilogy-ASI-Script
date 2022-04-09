#include "GenericUtil.h"

std::string
GenericUtil::GetModVersion ()
{
    return "Chaos Mod v3.0";
}

float
GenericUtil::CalculateTick (float multiplier)
{
    return (CTimer::ms_fTimeStepNonClipped
            / std::max (0.000001f, CTimer::ms_fTimeScale))
           * 0.02005f * 1000.0f * multiplier;
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
        if (minutes < 10)
        {
            time.append ("0");
        }
        time.append (std::to_string (minutes));
        time.append (":");
    }
    if (seconds < 10)
    {
        time.append ("0");
    }
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
    return 1 + (--t) * t * (2.70158f * t + 1.70158f);
}

std::string
GenericUtil::ToUpper (std::string string)
{
    std::transform (string.begin (), string.end (), string.begin (),
                    [] (unsigned char c) { return std::toupper (c); });
    return string;
}

void
GenericUtil::ScaleWithRoot (RwMatrix *matrix, RwMatrix *root, RwV3d scale)
{
    RwMatrixScale (matrix, &scale, rwCOMBINEPRECONCAT);

    matrix->pos = {(root->pos.x + ((matrix->pos.x - root->pos.x) * scale.x)),
                   (root->pos.y + ((matrix->pos.y - root->pos.y) * scale.y)),
                   (root->pos.z + ((matrix->pos.z - root->pos.z) * scale.z))};
}

void
GenericUtil::RotateWithRoot (RwMatrix *matrix, RwMatrix *root, int axis,
                             float angleDegrees)
{
    // TODO: Implement this with some ped effect maybe?
    // Code seems to not work properly sadly...
    // Peds can't be scaled / rotated as a single object, instead we need to do
    // it to every single one of their bones

    RwV3d axis3d = {axis == 0 ? 1.0f : 0.0f, axis == 1 ? 1.0f : 0.0f,
                    axis == 2 ? 1.0f : 0.0f};

    RwMatrixRotate (matrix, &axis3d, angleDegrees, rwCOMBINEPRECONCAT);

    float x = matrix->pos.x - root->pos.x;
    float y = matrix->pos.y - root->pos.y;
    float z = matrix->pos.z - root->pos.z;

    float angle = MathHelper::ToRadians (angleDegrees);

    if (axis == 0)
    {
        matrix->pos.y = root->pos.y + (y * cos (angle)) - (z * sin (angle));
        matrix->pos.z = root->pos.z + (z * cos (angle)) + (y * sin (angle));
    }
    else if (axis == 1)
    {
        matrix->pos.x = root->pos.x + (x * cos (angle)) - (z * sin (angle));
        matrix->pos.z = root->pos.z + (z * cos (angle)) + (x * sin (angle));
    }
    else if (axis == 2)
    {
        matrix->pos.x = root->pos.x + (x * cos (angle)) - (y * sin (angle));
        matrix->pos.y = root->pos.y + (y * cos (angle)) + (x * sin (angle));
    }
}