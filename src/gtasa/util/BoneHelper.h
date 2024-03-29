// Ped bone related methods with the help of mtasa-blue
// https://github.com/multitheftauto/mtasa-blue/blob/16769b8d1c94e2b9fe6323dcba46d1305f87a190/Client/game_sa/CEntitySA.cpp#L615
#pragma once

using namespace plugin;

class BoneHelper
{
    static inline ThiscallEvent<AddressList<0x5B1F31, H_CALL>, PRIORITY_AFTER,
                                ArgPickN<CPed *, 0>, void (CPed *)>
        cutscenePedRenderEvent;

    typedef void (*PedRenderFunctionHook) (CPed *);
    static inline std::vector<PedRenderFunctionHook> renderHooks = {};

    struct RpHAnimBlendInterpFrame
    {
        RtQuat orientation;
        RwV3d  translation;
    };

    struct BoneScaleInfo
    {
        unsigned int boneId = 0;
        RwV3d        scale;
        unsigned int rootBone      = 0;
        bool         scaleWithRoot = true;
    };

    static inline std::map<CPed *, std::map<unsigned int, RwV3d>> bonePositions
        = {};
    static inline std::map<CPed *, std::map<unsigned int, RwV3d>> boneRotations
        = {};
    static inline std::map<CPed *, std::vector<BoneScaleInfo>> boneScales = {};

    static inline std::map<CPed *, unsigned int> pedLastRendered = {};

public:
    static inline struct RenderEventStruct
    {
        void
        operator+= (PedRenderFunctionHook function)
        {
            auto hook = std::find (renderHooks.begin (), renderHooks.end (),
                                   function);
            if (hook == renderHooks.end ())
            {
                renderHooks.push_back (function);
            }
        }

        void
        operator-= (PedRenderFunctionHook function)
        {
            renderHooks.erase (std::remove (renderHooks.begin (),
                                            renderHooks.end (), function),
                               renderHooks.end ());
        }
    } RenderEvent;

    static void Initialise ();

    static void PedConstructor (CPed *ped);

    static void RenderPed (CPed *ped);

    static bool IsValidBone (CPed *ped, unsigned int boneId);

    static AnimBlendFrameData *GetBoneById (CPed *ped, unsigned int boneId);

    static RwMatrix *GetBoneRwMatrix (CPed *ped, unsigned int boneId);

    static RwV3d GetBonePosition (CPed *ped, unsigned int boneId);

    static void SetBonePosition (CPed *ped, unsigned int boneId,
                                 RwV3d position);

    static RwV3d GetBoneScale (CPed *ped, unsigned int boneId);

    static void SetBoneScale (CPed *ped, unsigned int boneId, RwV3d scale,
                              unsigned int rootBone      = 0,
                              bool         scaleWithRoot = true);

    static void ScaleBone (CPed *ped, unsigned int boneId, RwV3d scale,
                           unsigned int rootBone      = 0,
                           bool         scaleWithRoot = true);

    static RwV3d GetBoneRotation (CPed *ped, unsigned int boneId);

    static void SetBoneRotation (CPed *ped, unsigned int boneId, RwV3d angles);

    static void QuatToEuler (RtQuat *quat, RwV3d *angles);

    static void EulerToQuat (RwV3d *angles, RtQuat *quat);

    static void UpdatePed (CPed *ped, bool updateHierarchy = false);

    static void ShoulderBoneRotation (CPed *ped);

private:
    static CMatrix *__fastcall Hooked_CPed_ShoulderBoneRotation (
        RpClump *clump);

    static bool _hasAnyModifications (CPed *ped);
    static void _setBonePositions (CPed *ped);
    static void _setBoneRotations (CPed *ped);
    static void _setBoneScales (CPed *ped);
    static void _clearBoneMaps (CPed *ped);
};
