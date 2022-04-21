#include "BoneHelper.h"

void
BoneHelper::Initialise ()
{
    Events::pedRenderEvent += RenderPed;
    cutscenePedRenderEvent += RenderPed;
}

void
BoneHelper::RenderPed (CPed *ped)
{
    for (auto &hookedFunction : renderHooks)
    {
        hookedFunction (ped);
    }

    if (ped)
    {
        /* Pre-Update Ped Section */
        // Set bone positions
        _setBonePositions (ped);

        // Set bone rotations
        _setBoneRotations (ped);
        /* ---------------------- */

        // DO render here
        UpdatePed (ped);

        /* Post-Update Ped Section */
        // Set bone scales
        _setBoneScales (ped);

        // Set positions and rotations again if they changed
        _setBonePositions (ped);
        _setBoneRotations (ped);

        _clearBoneMaps (ped);
        /* ----------------------- */
    }
}

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

    if (bonePositions.contains (ped))
    {
        auto &boneMap = bonePositions[ped];
        if (boneMap.contains (boneId))
        {
            return boneMap[boneId];
        }
    }

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
    bonePositions[ped][boneId] = position;
}

RwV3d
BoneHelper::GetBoneScale (CPed *ped, unsigned int boneId)
{
    // Default scale
    RwV3d scale = {1, 1, 1};

    if (boneScales.contains (ped))
    {
        auto &scaleList = boneScales[ped];
        for (auto const &scaleInfo : scaleList)
        {
            if (scaleInfo.boneId == boneId)
            {
                scale.x *= scaleInfo.scale.x;
                scale.y *= scaleInfo.scale.y;
                scale.z *= scaleInfo.scale.z;
            }
        }
    }

    return scale;
}

void
BoneHelper::SetBoneScale (CPed *ped, unsigned int boneId, RwV3d scale,
                          unsigned int rootBone, bool scaleWithRoot)
{
    boneScales[ped].clear ();
    boneScales[ped].push_back (BoneScaleInfo{.boneId        = boneId,
                                             .scale         = scale,
                                             .rootBone      = rootBone,
                                             .scaleWithRoot = scaleWithRoot});
}

void
BoneHelper::ScaleBone (CPed *ped, unsigned int boneId, RwV3d scale,
                       unsigned int rootBone, bool scaleWithRoot)
{
    boneScales[ped].push_back (BoneScaleInfo{.boneId        = boneId,
                                             .scale         = scale,
                                             .rootBone      = rootBone,
                                             .scaleWithRoot = scaleWithRoot});
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

    if (boneRotations.contains (ped))
    {
        auto &boneMap = boneRotations[ped];
        if (boneMap.contains (boneId))
        {
            return boneMap[boneId];
        }
    }

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
    boneRotations[ped][boneId] = angles;
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

void
BoneHelper::_setBonePositions (CPed *ped)
{
    if (bonePositions.contains (ped))
    {
        auto &boneMap = bonePositions[ped];
        for (auto const &[boneId, position] : boneMap)
        {
            RwMatrixTag *rwBoneMatrix = GetBoneRwMatrix (ped, boneId);
            if (rwBoneMatrix)
            {
                CMatrix boneMatrix (rwBoneMatrix, false);
                boneMatrix.SetTranslateOnly (position.x, position.y,
                                             position.z);
                boneMatrix.UpdateRW ();
            }
        }
    }
}

void
BoneHelper::_setBoneRotations (CPed *ped)
{
    if (boneRotations.contains (ped))
    {
        auto &boneMap = boneRotations[ped];
        for (auto const &[boneId, rotation] : boneMap)
        {
            auto frameData = GetBoneById (ped, boneId);
            if (frameData)
            {
                RpHAnimBlendInterpFrame *iFrame
                    = (RpHAnimBlendInterpFrame *) frameData->m_pIFrame;

                if (iFrame)
                {
                    RwV3d angles = rotation;

                    RtQuat *boneOrientation = &iFrame->orientation;
                    EulerToQuat (&angles, boneOrientation);
                }
            }
        }
    }
}

void
BoneHelper::_setBoneScales (CPed *ped)
{
    if (boneScales.contains (ped))
    {
        auto &boneList = boneScales[ped];
        for (auto const &scaleInfo : boneList)
        {
            RwMatrixTag *rwBoneMatrix = GetBoneRwMatrix (ped, scaleInfo.boneId);
            if (rwBoneMatrix)
            {
                RwV3d scale = scaleInfo.scale;

                CMatrix boneMatrix (rwBoneMatrix, false);
                // CMatrix::ScaleXYZ - not implemented in plugin-sdk
                CallMethod<0x5A2E60, CMatrix *> (&boneMatrix, scale.x, scale.y,
                                                 scale.z);
                boneMatrix.UpdateRW ();

                if (scaleInfo.scaleWithRoot)
                {
                    RwV3d bonePos = GetBonePosition (ped, scaleInfo.boneId);
                    RwV3d rootPos = GetBonePosition (ped, scaleInfo.rootBone);

                    RwV3d newPos
                        = {(rootPos.x + ((bonePos.x - rootPos.x) * scale.x)),
                           (rootPos.y + ((bonePos.y - rootPos.y) * scale.y)),
                           (rootPos.z + ((bonePos.z - rootPos.z) * scale.z))};

                    SetBonePosition (ped, scaleInfo.boneId, newPos);
                }
            }
        }
    }
}

void
BoneHelper::_clearBoneMaps (CPed *ped)
{
    bonePositions[ped].clear ();
    boneRotations[ped].clear ();
    boneScales[ped].clear ();
}