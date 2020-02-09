#include "DisableOneMovementKeyEffect.h"

int DisableOneMovementKeyEffect::mode = 0;

DisableOneMovementKeyEffect::DisableOneMovementKeyEffect ()
    : EffectBase ("effect_disable_one_movement_key")
{
    AddType ("controls");
}

void
DisableOneMovementKeyEffect::InitializeHooks ()
{
    EffectBase::InitializeHooks ();

    for (int address :
         {0x0056EC9F, 0x006447B2, 0x006448DA, 0x006AD805, 0x006AD81A,
          0x006AD846, 0x006AD907, 0x006B4DA9, 0x006B4E9B, 0x006BE411,
          0x006BE43F, 0x006BE488, 0x006BE5D9, 0x006C1783, 0x006C17BB,
          0x006C17E9, 0x006C490F, 0x006C4930, 0x006C497C, 0x006C4A78,
          0x006CAE97, 0x006CAEC5, 0x006CAF0F, 0x006CB04F, 0x006CB191,
          0x006CE0BA, 0x006CE81E, 0x006D8B42, 0x006DA2EC, 0x006DA44B,
          0x006F0B50, 0x006F0B65, 0x006F0B91, 0x006F0C3C})
    {
        HookCall (address, HookedGetSteeringLeftRight);
    }

    for (int address :
         {0x00523C67, 0x00523C90, 0x00523CD0, 0x00528E6C, 0x005714DE,
          0x005803FA, 0x00580444, 0x005E1A33, 0x0060DD75, 0x0060DDCD,
          0x0061EA2A, 0x0061EA49, 0x0064F457, 0x0067BF14, 0x0067CFD3,
          0x0067E867, 0x0068700F, 0x0068702E, 0x00687585, 0x00687CD7,
          0x00687F75, 0x00688416, 0x00688AD6, 0x00691E4D})
    {
        HookCall (address, HookedPedWalkLeftRight);
    }

    for (int address :
         {0x00523CE2, 0x00528E86, 0x005E1A53, 0x0060DD96, 0x0060DDB7,
          0x0061E9EC, 0x0061EA0B, 0x0064F441, 0x0067BF2A, 0x0067CFF2,
          0x0067E851, 0x00686FD1, 0x00686FF0, 0x0068759B, 0x00687CC1,
          0x00687F5F, 0x0068842C, 0x00688AC0, 0x00691E37})
    {
        HookCall (address, HookedPedWalkUpDown);
    }

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
}

void
DisableOneMovementKeyEffect::Enable ()
{
    EffectBase::Enable ();

    /*
     * 0 = Move Forward / Accelerate
     * 1 = Move Backward / Brake
     * 2 = Move Left / Turn Left
     * 3 = Move Right / Turn Right
     */
    mode = RandomHelper::Random (0, 3);
}

__int16 __fastcall DisableOneMovementKeyEffect::HookedGetSteeringLeftRight (
    CPad *thisPad)
{
    __int16 ret = CallMethodAndReturn<__int16, 0x53FB80, CPad *> (thisPad);
    if (ret < 0 && mode == 2 || ret > 0 && mode == 3)
        ret = 0;
    return ret;
}

__int16 __fastcall DisableOneMovementKeyEffect::HookedPedWalkLeftRight (
    CPad *thisPad)
{
    __int16 ret = CallMethodAndReturn<__int16, 0x53FC90, CPad *> (thisPad);
    if (ret < 0 && mode == 2 || ret > 0 && mode == 3)
        ret = 0;
    return ret;
}

__int16 __fastcall DisableOneMovementKeyEffect::HookedPedWalkUpDown (
    CPad *thisPad)
{
    __int16 ret = CallMethodAndReturn<__int16, 0x53FD30, CPad *> (thisPad);
    if (ret > 0 && mode == 0 || ret < 0 && mode == 1)
        ret = 0;
    return ret;
}

__int16 __fastcall DisableOneMovementKeyEffect::HookedGetAccelerate (
    CPad *thisPad)
{
    __int16 ret = CallMethodAndReturn<__int16, 0x5403F0, CPad *> (thisPad);
    if (ret > 0 && mode == 1)
        ret = 0;
    return ret;
}

__int16 __fastcall DisableOneMovementKeyEffect::HookedGetBrake (CPad *thisPad)
{
    __int16 ret = CallMethodAndReturn<__int16, 0x540080, CPad *> (thisPad);
    if (ret > 0 && mode == 0)
        ret = 0;
    return ret;
}
