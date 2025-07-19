#include "effects/OneTimeEffect.h"

#include <CStreaming.h>
#include <CTimer.h>
#include <CWorld.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class SpawnTreeEffect : public OneTimeEffect
{
private:
    // Separate list of trees for spawning since not all are a good fit
    static inline std::vector<int> treeModels
        = {615, 616, 617, 618, 619, 620, 621, 622, 623, 645, 648, 652, 654, 655,
           656, 657, 658, 664, 670, 672, 673, 685, 687, 693, 696, 697, 700, 704,
           713, 719, 720, 739, 740, 763, 770, 771, 775, 780, 792, 892};

    float
    getTreeHealthMultiplier (int modelID)
    {
        switch (modelID)
        {
                // Small trees
            case 655:
            case 657:
            case 673:
            case 770:
            case 780:
            case 792:
            case 892:
                return 0.5f;

                // Medium trees
            case 615:
            case 616:
            case 617:
            case 619:
            case 620:
            case 622:
            case 623:
            case 652:
            case 654:
            case 656:
            case 658:
            case 672:
            case 685:
            case 687:
            case 700:
            case 763:
            case 771:
            case 775:
                return 0.25f;

                // Large trees
            case 621:
            case 645:
            case 648:
            case 664:
            case 670:
            case 693:
            case 696:
            case 697:
            case 704:
            case 713:
            case 719:
            case 720:
            case 739:
            case 740:
                return 0.16f;

                // Fallback
            default: return 0.5f;
        }
    }

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

        // Lower the tree into the ground a bit so it has a lower chance of
        // popping out
        newZ -= 0.5f;

        CMatrix *matrix;

        CVehicle *vehicle = FindPlayerVehicle (-1, false);
        if (vehicle)
            matrix = vehicle->GetMatrix ();
        else
            matrix = player->GetMatrix ();

        treeObject->SetMatrix (*matrix);
        treeObject->SetPosn (position);
        treeObject->m_nObjectType      = OBJECT_MISSION2;
        treeObject->m_nColDamageEffect = 0x14;
        treeObject->m_pObjectInfo->m_fColDamageMultiplier
            = getTreeHealthMultiplier (model);
    }
};

DEFINE_EFFECT (SpawnTreeEffect, "effect_spawn_tree", 0);