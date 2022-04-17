// Ped bone related methods with the help of mtasa-blue
// https://github.com/multitheftauto/mtasa-blue/blob/16769b8d1c94e2b9fe6323dcba46d1305f87a190/Client/game_sa/CEntitySA.cpp#L615

using namespace plugin;

class BoneHelper
{
    struct RpHAnimBlendInterpFrame
    {
        RtQuat orientation;
        RwV3d  translation;
    };

public:
    static RwMatrixTag *GetBoneRwMatrix (CPed *ped, unsigned int boneId);

    static RwV3d GetBonePosition (CPed *ped, unsigned int boneId);

    static void SetBonePosition (CPed *ped, unsigned int boneId,
                                 RwV3d position);

    static void SetBoneScale (CPed *ped, unsigned int boneId, RwV3d scale);

    static void ScaleWithRoot (RwMatrix *matrix, RwMatrix *root, RwV3d scale);

    static AnimBlendFrameData *GetBoneById (CPed *ped, unsigned int boneId);

    static RwV3d GetBoneRotation (CPed *ped, unsigned int boneId);

    static void SetBoneRotation (CPed *ped, unsigned int boneId, RwV3d angles);

    static void QuatToEuler (RtQuat *quat, RwV3d *angles);

    static void EulerToQuat (RwV3d *angles, RtQuat *quat);

    static void UpdatePed (CPed *ped);
};
