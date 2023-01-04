#pragma once

#include <CVector.h>

enum class eJumpState : int
{
    START_POINT_INTERSECTED,
    IN_FLIGHT,
    END_POINT_INTERSECTED,
};

struct CStuntJump
{
    CBoundingBox start;
    CBoundingBox end;
    CVector      camera;
    int          reward;
    bool         done;
    bool         found;
};

VALIDATE_SIZE (CStuntJump, 0x44);