#include "util/BoneHelper.h"
#include "util/EffectBase.h"
#include "util/GenericUtil.h"
#include "util/Teleportation.h"

#include <deque>

#include <ePedBones.h>

class ItsRewindTimeEffect : public EffectBase
{
    struct RewindData
    {
        CVector                       location;
        float                         playerHealth;
        int                           currArea;
        std::map<unsigned int, RwV3d> bonePositions;
        std::map<unsigned int, RwV3d> boneRotations;

        bool     wasInVehicle;
        float    vehicleHealth;
        CVector  moveSpeed;
        CVector  turnSpeed;
        RwMatrix matrix;
    };

    int                    wait              = 0;
    int                    startStoring      = 0;
    bool                   isTeleportingBack = false;
    unsigned int           currentRewindID   = 0;
    std::deque<RewindData> rewindDataList    = {};

public:
    void
    OnStart (EffectInstance *inst) override
    {
        wait              = inst->Random (2000, 15000);
        startStoring      = inst->Random (1000, wait - 1000);
        isTeleportingBack = false;
        currentRewindID   = 0;
        rewindDataList.clear ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > 0)
        {
            if (wait <= startStoring) StoreLocationData ();

            return;
        }

        TeleportToNextLocation ();

        if (!isTeleportingBack)
        {
            wait         = inst->Random (2000, 15000);
            startStoring = inst->Random (1000, wait - 1000);

            CPlayerPed *player = FindPlayerPed ();
            if (player) player->m_nPhysicalFlags.bCollidable = true;

            CVehicle *vehicle = FindPlayerVehicle (-1, false);
            if (vehicle) vehicle->m_nPhysicalFlags.bCollidable = true;
        }
    }

    void
    TeleportToNextLocation ()
    {
        isTeleportingBack = true;

        RewindData rewindData = rewindDataList[currentRewindID];

        CGame::currArea = rewindData.currArea;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle && rewindData.wasInVehicle)
        {
            vehicle->m_fHealth   = rewindData.vehicleHealth;
            vehicle->m_nAreaCode = rewindData.currArea;
            vehicle->SetPosn (rewindData.location);
            vehicle->m_vecMoveSpeed = rewindData.moveSpeed;
            vehicle->m_vecTurnSpeed = rewindData.turnSpeed;

            CallMethod<0x59AD20, CMatrix *, RwMatrix *> (vehicle->GetMatrix (),
                                                         &rewindData.matrix);

            vehicle->m_nPhysicalFlags.bCollidable = false;
        }

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            player->m_fHealth   = rewindData.playerHealth;
            player->m_nAreaCode = rewindData.currArea;
            for (int i = 0; i < ePedBones::BONE_RIGHTFOOT + 1; i++)
            {
                BoneHelper::SetBonePosition (player, i,
                                             rewindData.bonePositions[i]);
                BoneHelper::SetBoneRotation (player, i,
                                             rewindData.boneRotations[i]);
            }

            if (!vehicle)
            {
                player->SetPosn (rewindData.location);
                player->m_vecMoveSpeed = rewindData.moveSpeed;
                player->m_vecTurnSpeed = rewindData.turnSpeed;
            }

            player->m_nPhysicalFlags.bCollidable = false;
        }

        currentRewindID += 3;
        if (currentRewindID >= rewindDataList.size ())
        {
            isTeleportingBack = false;
            currentRewindID   = 0;
            rewindDataList.clear ();
        }
    }

    void
    StoreLocationData ()
    {
        RewindData rewindData;

        rewindData.currArea = CGame::currArea;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle)
        {
            rewindData.wasInVehicle  = true;
            rewindData.vehicleHealth = vehicle->m_fHealth;
            rewindData.location      = vehicle->GetPosition ();
            rewindData.moveSpeed     = vehicle->m_vecMoveSpeed;
            rewindData.turnSpeed     = vehicle->m_vecTurnSpeed;
            vehicle->GetMatrix ()->CopyToRwMatrix (&rewindData.matrix);
        }

        CPlayerPed *player = FindPlayerPed ();
        if (player)
        {
            rewindData.playerHealth = player->m_fHealth;
            for (int i = 0; i < ePedBones::BONE_RIGHTFOOT + 1; i++)
            {
                rewindData.bonePositions[i]
                    = BoneHelper::GetBonePosition (player, i);
                rewindData.boneRotations[i]
                    = BoneHelper::GetBoneRotation (player, i);
            }

            if (!vehicle)
            {
                rewindData.wasInVehicle = false;
                rewindData.location     = player->GetPosition ();
                rewindData.moveSpeed    = player->m_vecMoveSpeed;
                rewindData.turnSpeed    = player->m_vecTurnSpeed;
            }
        }

        rewindDataList.push_front (rewindData);
    }
};

DEFINE_EFFECT (ItsRewindTimeEffect, "effect_its_rewind_time", 0);
