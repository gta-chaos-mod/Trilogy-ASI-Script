#include "PedalToTheMetalEffect.h"

PedalToTheMetalEffect::PedalToTheMetalEffect ()
    : EffectBase ("effect_pedal_to_the_metal")
{
    AddType ("controls");
}

void
PedalToTheMetalEffect::InitializeHooks ()
{
    EffectBase::InitializeHooks ();

    for (int address :
         {0x004F51BA, 0x00500A00, 0x00500A2F, 0x00500BB3, 0x00500BE4,
          0x00500BF2, 0x005010E8, 0x00501108, 0x005714F3, 0x0063A49E,
          0x0063F401, 0x0064478F, 0x006448B7, 0x00666E81, 0x0067ED45,
          0x0067EDDA, 0x006AD992, 0x006ADAD7, 0x006ADB2B, 0x006B5011,
          0x006B50E2, 0x006BE6E4, 0x006BE748, 0x006BE7A5, 0x006C18BC,
          0x006C484B, 0x006CB2EF, 0x006CB6DB, 0x006CE961, 0x006D8DDC,
          0x006D98F0, 0x006D9CF1, 0x006F0AC9, 0x006F87D5, 0x006F8827,
          0x006F885C})
    {
        HookCall (address, HookedGetAccelerate);
    }

    for (int address :
         {0x004F51C9, 0x00500A0A, 0x00500A41, 0x00500BBA, 0x00500BCE,
          0x00500BEB, 0x005010F2, 0x005010FF, 0x0063A4B0, 0x0063F423,
          0x006447D5, 0x006448FD, 0x00666E90, 0x0067ED33, 0x0067EDC8,
          0x006AD9A5, 0x006ADB03, 0x006ADB52, 0x006BE6F7, 0x006BE774,
          0x006BE7CC, 0x006C4855, 0x006CB302, 0x006CB61E, 0x006CB644,
          0x006CB66F, 0x006CB6C5, 0x006D8DE6, 0x006D98FA, 0x006D9CFB,
          0x006F0A38, 0x006F87DF, 0x006F880F, 0x6F8842})
    {
        HookCall (address, HookedGetBrake);
    }

    for (int address :
         {0x6AD77F, 0x6B4F69, 0x6BE368, 0x6CB2B6, 0x6DC491, 0x6DCCA5})
    {
        HookCall (address, HookedGetHandBrake);
    }
}

__int16 __fastcall PedalToTheMetalEffect::HookedGetAccelerate (CPad *thisPad)
{
    return 255;
}

__int16 __fastcall PedalToTheMetalEffect::HookedGetBrake (CPad *thisPad)
{
    return 0;
}

__int16 __fastcall PedalToTheMetalEffect::HookedGetHandBrake (CPad *thisPad)
{
    return 0;
}
