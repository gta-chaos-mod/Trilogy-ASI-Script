#include "util/EffectBase.h"
#include "util/GenericUtil.h"
#include "util/Teleportation.h"

class RubberbandingEffect : public EffectBase
{
    struct RewindData
    {
        CVector  location;
        int      currArea;
        bool     wasInVehicle;
        CVector  moveSpeed;
        CVector  turnSpeed;
        RwMatrix matrix;
    };

    int        wait      = 0;
    int        nextStore = 0;
    RewindData rewindData;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        wait      = inst->Random (2000, 5000);
        nextStore = inst->Random (500, wait - 500);

        StoreLocationData ();
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        TeleportToPreviousLocation ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        wait -= (int) GenericUtil::CalculateTick ();
        if (wait > nextStore) StoreLocationData ();

        if (wait > 0) return;

        TeleportToPreviousLocation ();

        wait      = inst->Random (2000, 5000);
        nextStore = inst->Random (500, wait - 500);
    }

    void
    TeleportToPreviousLocation ()
    {
        if (Teleportation::CanTeleport ())
        {
            CGame::currArea = rewindData.currArea;

            CVehicle *vehicle = FindPlayerVehicle (-1, false);
            if (vehicle && rewindData.wasInVehicle)
            {
                vehicle->m_nAreaCode = rewindData.currArea;
                vehicle->SetPosn (rewindData.location);
                vehicle->m_vecMoveSpeed = rewindData.moveSpeed;
                vehicle->m_vecTurnSpeed = rewindData.turnSpeed;
                CallMethod<0x59AD20, CMatrix *, RwMatrix *> (
                    vehicle->GetMatrix (), &rewindData.matrix);
            }

            CPlayerPed *player = FindPlayerPed ();
            if (player)
            {
                player->m_nAreaCode = rewindData.currArea;

                if (!vehicle)
                {
                    player->SetPosn (rewindData.location);
                    player->m_vecMoveSpeed = rewindData.moveSpeed;
                    player->m_vecTurnSpeed = rewindData.turnSpeed;
                }
            }
        }
    }

    void
    StoreLocationData ()
    {
        rewindData.currArea = CGame::currArea;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle)
        {
            rewindData.wasInVehicle = true;
            rewindData.location     = vehicle->GetPosition ();
            rewindData.moveSpeed    = vehicle->m_vecMoveSpeed;
            rewindData.turnSpeed    = vehicle->m_vecTurnSpeed;
            vehicle->GetMatrix ()->CopyToRwMatrix (&rewindData.matrix);
        }

        CPlayerPed *player = FindPlayerPed ();
        if (player && !vehicle)
        {
            rewindData.wasInVehicle = false;
            rewindData.location     = player->GetPosition ();
            rewindData.moveSpeed    = player->m_vecMoveSpeed;
            rewindData.turnSpeed    = player->m_vecTurnSpeed;
        }
    }
};

DEFINE_EFFECT (RubberbandingEffect, "effect_rubberbanding", 0);
