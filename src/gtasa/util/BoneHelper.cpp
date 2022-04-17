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

// Not working properly in cutscenes.
// Are eyes and the mouth different bones that we can't control?
void
BoneHelper::SetBoneScale (CPed *ped, unsigned int boneId, RwV3d scale,
                          unsigned int rootBone, bool scaleWithRoot)
{
    RwMatrixTag *rwBoneMatrix = GetBoneRwMatrix (ped, boneId);
    if (rwBoneMatrix)
    {
        CMatrix boneMatrix (rwBoneMatrix, false);
        // CMatrix::SetScale_XYZ - PR to plugin-sdk maybe?
        CallMethod<0x5A2E60, CMatrix *> (&boneMatrix, scale.x, scale.y,
                                         scale.z);
        boneMatrix.UpdateRW ();

        if (scaleWithRoot)
        {
            RwV3d bonePos = GetBonePosition (ped, boneId);
            RwV3d rootPos = GetBonePosition (ped, rootBone);

            RwV3d newPos = {(rootPos.x + ((bonePos.x - rootPos.x) * scale.x)),
                            (rootPos.y + ((bonePos.y - rootPos.y) * scale.y)),
                            (rootPos.z + ((bonePos.z - rootPos.z) * scale.z))};

            SetBonePosition (ped, boneId, newPos);
        }
    }
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

// Use this whenever you do bone rotation.
// Scale bones AFTER calling this, otherwise they reset.
void
BoneHelper::UpdatePed (CPed *ped)
{
    if (ped && ped->m_pRwClump)
    {
        ped->m_bDontUpdateHierarchy = false;

        // This is the wrong address - PR a fix to plugin-sdk?
        // ped->UpdateRpHAnim ();
        CallMethod<0x532B20, CPed *> (ped);

        ShoulderBoneRotation (ped);
    }
}

void
BoneHelper::ShoulderBoneRotation (CPed *ped)
{
    if (ped && ped->m_pRwClump)
    {
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