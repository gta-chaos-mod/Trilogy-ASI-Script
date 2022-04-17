#include "BoneHelper.h"

RwMatrixTag *
BoneHelper::GetBoneRwMatrix (CPed *ped, unsigned int boneId)
{
    auto clump = ped->m_pRwClump;
    if (!clump)
    {
        return nullptr;
    }

    RpHAnimHierarchy *hAnimHier = GetAnimHierarchyFromSkinClump (clump);
    if (hAnimHier && hAnimHier->pNodeInfo)
    {
        int boneAnimIdIndex = RpHAnimIDGetIndex (hAnimHier, boneId);
        if (boneAnimIdIndex != -1 && boneAnimIdIndex < hAnimHier->numNodes)
        {
            return &RpHAnimHierarchyGetMatrixArray (hAnimHier)[boneAnimIdIndex];
        }
    }
    return nullptr;
}

RwV3d
BoneHelper::GetBonePosition (CPed *ped, unsigned int boneId)
{
    RwV3d position = {0, 0, 0};

    RwMatrixTag *rwBoneMatrix = GetBoneRwMatrix (ped, boneId);
    if (rwBoneMatrix)
    {
        const RwV3d &pos = rwBoneMatrix->pos;
        position         = {pos.x, pos.y, pos.z};
    }

    return position;
}

void
BoneHelper::SetBonePosition (CPed *ped, unsigned int boneId, RwV3d position)
{
    RwMatrixTag *rwBoneMatrix = GetBoneRwMatrix (ped, boneId);
    if (rwBoneMatrix)
    {
        CMatrix boneMatrix (rwBoneMatrix, false);
        boneMatrix.SetTranslateOnly (position.x, position.y, position.z);
        boneMatrix.UpdateRW ();
    }
}

void
BoneHelper::SetBoneScale (CPed *ped, unsigned int boneId, RwV3d scale)
{
    RwMatrixTag *rwBoneMatrix = GetBoneRwMatrix (ped, boneId);
    if (rwBoneMatrix)
    {
        RwMatrixScale (rwBoneMatrix, &scale, rwCOMBINEPRECONCAT);
    }
}

void
BoneHelper::ScaleWithRoot (RwMatrix *matrix, RwMatrix *root, RwV3d scale)
{
    if (!matrix || !root)
    {
        return;
    }

    RwMatrixScale (matrix, &scale, rwCOMBINEPRECONCAT);

    matrix->pos = {(root->pos.x + ((matrix->pos.x - root->pos.x) * scale.x)),
                   (root->pos.y + ((matrix->pos.y - root->pos.y) * scale.y)),
                   (root->pos.z + ((matrix->pos.z - root->pos.z) * scale.z))};
}

AnimBlendFrameData *
BoneHelper::GetBoneById (CPed *ped, unsigned int boneId)
{
    auto clump = ped->m_pRwClump;
    if (!clump)
    {
        return nullptr;
    }

    return RpAnimBlendClumpFindBone (clump, boneId);
}

RwV3d
BoneHelper::GetBoneRotation (CPed *ped, unsigned int boneId)
{
    RwV3d angles = {0, 0, 0};

    auto frameData = GetBoneById (ped, boneId);
    if (frameData)
    {
        RpHAnimBlendInterpFrame *iFrame
            = (RpHAnimBlendInterpFrame *) frameData->m_pIFrame;

        if (iFrame)
        {
            RtQuat *quat = &iFrame->orientation;
            QuatToEuler (quat, &angles);
        }
    }

    return angles;
}

void
BoneHelper::SetBoneRotation (CPed *ped, unsigned int boneId, RwV3d angles)
{
    auto frameData = GetBoneById (ped, boneId);
    if (frameData)
    {
        RpHAnimBlendInterpFrame *iFrame
            = (RpHAnimBlendInterpFrame *) frameData->m_pIFrame;

        if (iFrame)
        {
            RtQuat *boneOrientation = &iFrame->orientation;
            EulerToQuat (&angles, boneOrientation);
        }
    }
}

void
BoneHelper::QuatToEuler (RtQuat *quat, RwV3d *angles)
{
    // BoneNode_c_QuatToEuler
    Call<0x617080> (quat, angles);
}

void
BoneHelper::EulerToQuat (RwV3d *angles, RtQuat *quat)
{
    // BoneNode_c_EulerToQuat
    Call<0x6171F0> (angles, quat);
}

void
BoneHelper::UpdatePed (CPed *ped)
{
    if (ped && ped->m_pRwClump)
    {
        ped->m_bDontUpdateHierarchy = false;

        // This is the wrong address - PR a fix to plugin-sdk?
        // ped->UpdateRpHAnim ();
        CallMethod<0x532B20, CPed *> (ped);

        // We need to safe-guard ourselves for cutscenes. If one of these bones
        // can't be found don't continue to the "ShoulderBoneRotation" call,
        // otherwise we crash.
        std::vector<unsigned int> validBones = {21, 22, 301, 31, 32, 302};
        for (unsigned int i = 0; i < validBones.size (); i++)
        {
            if (!GetBoneById (ped, i))
            {
                return;
            }
        }

        // CPed::ShoulderBoneRotation - PR a fix to plugin-sdk?
        Call<0x5DF560> (ped->m_pRwClump);
    }
}