#include "effects/OneTimeEffect.h"

#include <CStreaming.h>
#include <CTimer.h>
#include <CWorld.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class SpawnTreeEffect : public OneTimeEffect
{
private:
    std::vector<int> treeModels
        = {615,   616,   617,   618,   619,  620,  621,  622,   623,   624,
           629,   634,   641,   645,   648,  649,  652,  654,   655,   656,
           657,   658,   659,   660,   661,  664,  669,  670,   671,   672,
           673,   685,   687,   688,   689,  690,  691,  693,   694,   695,
           696,   697,   698,   700,   703,  704,  705,  706,   707,   708,
           709,   710,   711,   712,   713,  714,  715,  717,   719,   720,
           721,   722,   723,   724,   725,  726,  727,  728,   729,   730,
           731,   732,   733,   734,   735,  736,  737,  738,   739,   740,
           763,   764,   765,   766,   767,  768,  769,  770,   771,   772,
           773,   774,   775,   776,   777,  778,  779,  780,   782,   784,
           785,   789,   790,   791,   792,  8835, 8836, 8837,  886,   887,
           890,   892,   893,   894,   3505, 3506, 3507, 3508,  3509,  3510,
           3511,  3512,  3517,  3898,  9019, 9034, 9035, 16060, 16061, 18268,
           18269, 18270, 18271, 18272, 18273};

public:
    void
    OnStart (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player) return;

        CVector position
            = player->TransformFromObjectSpace (CVector (0.0f, 10.0f, -1.0f));

        CObject *treeObject;

        int model = treeModels[inst->Random (0, (int) treeModels.size () - 1)];
        CStreaming::RequestModel (model, 2);
        CStreaming::LoadAllRequestedModels (false);
        Command<eScriptCommands::COMMAND_CREATE_OBJECT> (model, position.x,
                                                         position.y, position.z,
                                                         &treeObject);
        CStreaming::SetModelIsDeletable (model);

        bool  worked = false;
        float newZ   = CWorld::FindGroundZFor3DCoord (position.x, position.y,
                                                      position.z + 2.0f, &worked,
                                                      nullptr);
        if (worked && newZ > position.z) position.z = newZ;

        CMatrix *matrix;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle)
            matrix = vehicle->GetMatrix ();
        else
            matrix = player->GetMatrix ();

        treeObject->SetMatrix (*matrix);
        treeObject->SetPosn (position);
        treeObject->m_nObjectType                         = OBJECT_MISSION2;
        treeObject->m_nColDamageEffect                    = 0x14;
        treeObject->m_pObjectInfo->m_fColDamageMultiplier = 0.5f;
    }
};

DEFINE_EFFECT (SpawnTreeEffect, "effect_spawn_tree", 0);