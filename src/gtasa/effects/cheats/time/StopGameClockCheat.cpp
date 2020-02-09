#include "StopGameClockCheat.h"

StopGameClockCheat::StopGameClockCheat ()
    : TimedAddressEffect ("cheat_stop_game_clock", 0x969168)
{
    AddType ("time");
}

void
StopGameClockCheat::Enable ()
{
    TimedAddressEffect::Enable ();

    this->hours   = CClock::ms_nGameClockHours;
    this->minutes = CClock::ms_nGameClockMinutes;
    this->seconds = CClock::ms_nGameClockSeconds;
}

void
StopGameClockCheat::HandleTick ()
{
    TimedAddressEffect::HandleTick ();

    CClock::ms_nGameClockHours   = this->hours;
    CClock::ms_nGameClockMinutes = this->minutes;
    CClock::ms_nGameClockSeconds = this->seconds;

    // TODO: Store weather and keep setting it to prevent timecycle weirdness
}
