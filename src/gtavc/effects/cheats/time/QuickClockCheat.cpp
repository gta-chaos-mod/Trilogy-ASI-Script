#include "QuickClockCheat.h"

QuickClockCheat::QuickClockCheat ()
    : TimedAddressEffect ("cheat_quick_clock", 0xA10B87)
{
    AddType ("time");
}
