#include "GameUtil.h"

bool *GameUtil::extraSplash = reinterpret_cast<bool *> (0x86966C);
char *GameUtil::loadPath    = reinterpret_cast<char *> (0xA0CE9C);
char *GameUtil::savePath    = reinterpret_cast<char *> (0x978428);

void
GameUtil::SaveToFile (std::string fileName)
{
    // TODO: Cut path at `GTAVCsf` and append `chaos_mod\\`

    CClock::ms_nMillisecondsPerGameMinute = 1000;

    /*CPlayerPed* player = FindPlayerPed();
    int tempMoney = -1;
    if (player) {
            tempMoney = LongLiveTheRichEffect::isEnabled ?
    LongLiveTheRichEffect::storedMoney :
    player->GetPlayerInfoForThisPlayerPed()->m_nMoney;
    }

    player->GetPlayerInfoForThisPlayerPed()->m_nMoney = tempMoney;*/

    Call<0x61A630> (9); // MakeValidSaveName - Slot "9"
    Call<0x602240> ();  // Ensure save folders exist
    int file = CFileMgr::OpenFile (savePath, "wb");
    if (file)
    {
        Call<0x61A690> ();     // DoGameSpecificStuffBeforeSave
        Call<0x61D8FD> (file); // GenericSave
        CFileMgr::CloseFile (file);
    }

    /*if (player) {
            player->GetPlayerInfoForThisPlayerPed()->m_nMoney =
    LongLiveTheRichEffect::isEnabled ? (int)LongLiveTheRichEffect::gainedMoney :
    tempMoney;
    }*/
}

bool
GameUtil::LoadFromFile (std::string fileName)
{
    // TODO: Cut path at `GTAVCsf` and append `chaos_mod\\`

    if (CallAndReturn<bool, 0x61A6C0> (9))
    { // CheckSlotDataValid
        *extraSplash = true;
        CGame::InitialiseWhenRestarting ();
        return true;
    }
    return false;
}

void
GameUtil::SetVehiclesToRealPhysics ()
{
    for (CVehicle *vehicle : CPools::ms_pVehiclePool)
    {
        if (vehicle->m_pDriver && !vehicle->IsDriver (FindPlayerPed ()))
        {
            CCarCtrl::SwitchVehicleToRealPhysics (vehicle);
        }
    }
}
