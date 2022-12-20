#include "GlobalRenderer.h"

#include "util/GlobalHooksInstance.h"
#include "util/hooks/HookMacros.h"

#include <CModelInfo.h>

using namespace plugin;

void
GlobalRenderer::Initialise ()
{
    HOOK (GlobalHooksInstance::Get (), Hooked_FrameSyncDirty, void (),
          0x7EF37C);

    HOOK_METHOD_ARGS (GlobalHooksInstance::Get (), Hooked_RenderBuilding,
                      void (CEntity *), 0x534310);

    HOOK_METHOD_ARGS (GlobalHooksInstance::Get (), Hooked_RenderObject,
                      void (CObject *), 0x59F180);
}

void
GlobalRenderer::Hooked_FrameSyncDirty (auto &&cb)
{
    // _rwFrameSyncDirty
    cb ();

    if (renderVehicleHooks.size () > 0)
        for (CVehicle *vehicle : CPools::ms_pVehiclePool)
            RenderVehicle (vehicle);
}

void
GlobalRenderer::Hooked_RenderBuilding (auto &&cb, CEntity *entity)
{
    bool isBuilding = entity && entity->m_nType == ENTITY_TYPE_BUILDING
                      && renderBuildingHooks.size () > 0;

    if (isBuilding) RenderBuilding ((CBuilding *) entity);

    cb ();

    if (isBuilding) RenderBuilding ((CBuilding *) entity, true);
}

void
GlobalRenderer::Hooked_RenderObject (auto &&cb, CObject *object)
{
    bool hasObjectHooks = renderObjectHooks.size () > 0;
    if (hasObjectHooks) RenderObject (object);

    cb ();

    if (hasObjectHooks) RenderObject (object, true);
}

void
GlobalRenderer::RenderBuilding (CBuilding *building, bool reset)
{
    if (!IsEntityPointerValid (building) || !building->m_matrix
        || !building->m_pRwObject)
        return;

    auto frame = GetObjectParent (building->m_pRwObject);
    if (!frame) return;

    auto matrix = &frame->modelling;
    if (!matrix) return;

    building->m_matrix->CopyToRwMatrix (matrix);

    if (!reset)
    {
        for (auto &hookedFunction : renderBuildingHooks)
        {
            hookedFunction (building, frame);
        }
    }

    building->UpdateRwFrame ();
}

void
GlobalRenderer::ResetBuildings ()
{
    for (CBuilding *building : CPools::ms_pBuildingPool)
    {
        RenderBuilding (building, true);
    }
}

void
GlobalRenderer::RenderObject (CObject *object, bool reset)
{
    if (!IsObjectPointerValid (object) || !object->m_matrix
        || !object->m_pRwObject)
        return;

    auto frame = GetObjectParent (object->m_pRwObject);
    if (!frame) return;

    auto matrix = &frame->modelling;
    if (!matrix) return;

    object->m_matrix->CopyToRwMatrix (matrix);

    if (!reset)
    {
        for (auto &hookedFunction : renderObjectHooks)
        {
            hookedFunction (object, frame);
        }
    }

    object->UpdateRwFrame ();
}

void
GlobalRenderer::ResetObjects ()
{
    for (CObject *object : CPools::ms_pObjectPool)
    {
        RenderObject (object, true);
    }
}

void
GlobalRenderer::RenderVehicle (CVehicle *vehicle, bool reset)
{
    if (!IsVehiclePointerValid (vehicle) || !vehicle->m_matrix
        || !vehicle->m_pRwObject)
        return;

    if (CModelInfo::IsTrailerModel (vehicle->m_nModelIndex)) return;

    auto frame = GetObjectParent (vehicle->m_pRwObject);
    if (!frame) return;

    auto matrix = &frame->modelling;
    if (!matrix) return;

    vehicle->m_matrix->CopyToRwMatrix (matrix);

    if (!reset)
    {
        for (auto &hookedFunction : renderVehicleHooks)
        {
            hookedFunction (vehicle, frame);
        }
    }

    vehicle->UpdateRwFrame ();
}

void
GlobalRenderer::ResetVehicles ()
{
    for (CVehicle *vehicle : CPools::ms_pVehiclePool)
    {
        RenderVehicle (vehicle, true);
    }
}