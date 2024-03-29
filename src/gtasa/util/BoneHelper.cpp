#include "BoneHelper.h"

#include <CCutsceneMgr.h>
#include <CTimer.h>

void
BoneHelper::Initialise ()
{
    Events::pedRenderEvent += RenderPed;
    cutscenePedRenderEvent += RenderPed;

    Events::pedCtorEvent += PedConstructor;

    // Hook so we don't mess up shoulders in cutscenes
    // CCutsceneObject::PreRender
    injector::MakeCALL (0x5B1F94, BoneHelper::Hooked_CPed_ShoulderBoneRotation);
    // CPed::PreRenderAfterTest
    injector::MakeCALL (0x5E6913, BoneHelper::Hooked_CPed_ShoulderBoneRotation);
}

CMatrix *__fastcall BoneHelper::Hooked_CPed_ShoulderBoneRotation (
    RpClump *clump)
{
    return nullptr;
}

void
BoneHelper::PedConstructor (CPed *ped)
{
    _clearBoneMaps (ped);
    if (pedLastRendered.contains (ped)) pedLastRendered.erase (ped);
}

void
BoneHelper::RenderPed (CPed *ped)
{
    if (!ped || pedLastRendered[ped] >= CTimer::m_FrameCounter) return;

    pedLastRendered[ped] = CTimer::m_FrameCounter;

    if (renderHooks.size () > 0)
    {
        for (auto &hookedFunction : renderHooks)
        {
            hookedFunction (ped);
        }

        _setBonePositions (ped);
        _setBoneRotations (ped);

        UpdatePed (ped);

        _setBoneScales (ped);
        _setBonePositions (ped);

        _clearBoneMaps (ped);
    }
    else if (!ped->m_nModelIndex
             || ped->m_nModelIndex == MODEL_CSPLAY
                    && CCutsceneMgr::ms_cutsceneTimer)
    {
        ShoulderBoneRotation (ped);
    }
}

AnimBlendFrameData *
BoneHelper::GetBoneById (CPed *ped, unsigned int boneId)
{
    auto clump = ped->m_pRwClump;
    if (!clump) return nullptr;

    return RpAnimBlendClumpFindBone (clump, boneId);
}

bool
BoneHelper::IsValidBone (CPed *ped, unsigned int boneId)
{
    return GetBoneById (ped, boneId) != nullptr;
}

RwMatrix *
BoneHelper::GetBoneRwMatrix (CPed *ped, unsigned int boneId)
{
    auto clump = ped->m_pRwClump;
    if (!clump) return nullptr;

    RwMatrix *matrix = nullptr;

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
    // Default position
    RwV3d position = {0, 0, 0};
    if (!IsValidBone (ped, boneId)) return position;

    if (bonePositions.contains (ped))
    {
        auto &boneMap = bonePositions[ped];
        if (boneMap.contains (boneId)) return boneMap[boneId];
    }

    RwMatrix *rwBoneMatrix = GetBoneRwMatrix (ped, boneId);
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
    if (!IsValidBone (ped, boneId)) return;

    bonePositions[ped][boneId] = position;
}

RwV3d
BoneHelper::GetBoneScale (CPed *ped, unsigned int boneId)
{
    // Default scale
    RwV3d scale = {1, 1, 1};
    if (!IsValidBone (ped, boneId)) return scale;

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
    if (!IsValidBone (ped, boneId)) return;

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
    if (!IsValidBone (ped, boneId)) return;

    boneScales[ped].push_back (BoneScaleInfo{.boneId        = boneId,
                                             .scale         = scale,
                                             .rootBone      = rootBone,
                                             .scaleWithRoot = scaleWithRoot});
}

RwV3d
BoneHelper::GetBoneRotation (CPed *ped, unsigned int boneId)
{
    RwV3d angles = {0, 0, 0};
    if (!IsValidBone (ped, boneId)) return angles;

    if (boneRotations.contains (ped))
    {
        auto &boneMap = boneRotations[ped];
        if (boneMap.contains (boneId)) return boneMap[boneId];
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
    if (!IsValidBone (ped, boneId)) return;

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
BoneHelper::UpdatePed (CPed *ped, bool updateHierarchy)
{
    if (ped && ped->m_pRwClump)
    {
        ped->m_bDontUpdateHierarchy = updateHierarchy;

        // This is the wrong address - PR a fix to plugin-sdk?
        // ped->UpdateRpHAnim ();
        CallMethod<0x532B20, CPed *> (ped);

        if (!ped->m_nModelIndex
            || ped->m_nModelIndex == MODEL_CSPLAY
                   && CCutsceneMgr::ms_cutsceneTimer)
        {
            ShoulderBoneRotation (ped);
        }
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
        // std::vector<unsigned int> validBones = {21, 22, 301, 31, 32, 302};
        // for (unsigned int i = 0; i < validBones.size (); i++)
        // {
        //     if (!IsValidBone (ped, i)) return;
        // }

        // CPed::ShoulderBoneRotation - PR a fix to plugin-sdk?
        Call<0x5DF560> (ped->m_pRwClump);

        ped->m_bDontUpdateHierarchy = true;
    }
}

bool
BoneHelper::_hasAnyModifications (CPed *ped)
{
    return bonePositions.contains (ped) || boneRotations.contains (ped)
           || boneScales.contains (ped);
}

void
BoneHelper::_setBonePositions (CPed *ped)
{
    if (bonePositions.contains (ped))
    {
        auto &boneMap = bonePositions[ped];
        for (auto const &[boneId, position] : boneMap)
        {
            RwMatrix *rwBoneMatrix = GetBoneRwMatrix (ped, boneId);
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
            RwMatrix *rwBoneMatrix = GetBoneRwMatrix (ped, scaleInfo.boneId);
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
    if (bonePositions.contains (ped)) bonePositions.erase (ped);
    if (boneRotations.contains (ped)) boneRotations.erase (ped);
    if (boneScales.contains (ped)) boneScales.erase (ped);
}