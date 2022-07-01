#include "GlobalRenderer.h"

#include "util/GlobalHooksInstance.h"
#include "util/hooks/HookMacros.h"

using namespace plugin;

void
GlobalRenderer::Initialise ()
{
    patch::RedirectCall (0x7EF37C, Hooked_FrameSyncDirty);
    // HOOK (globalHooksInstance.Get (), Hooked_FrameSyncDirty, void (),
    // 0x7EF37C);
}

void
GlobalRenderer::Hooked_FrameSyncDirty ()
{
    if (renderBuildingHooks.size () > 0)
        for (CBuilding *building : CPools::ms_pBuildingPool)
            RenderBuilding (building);

    if (renderObjectHooks.size () > 0)
        for (CObject *object : CPools::ms_pObjectPool)
            RenderObject (object);

    if (renderVehicleHooks.size () > 0)
        for (CVehicle *object : CPools::ms_pVehiclePool)
            RenderVehicle (object);

    // _rwFrameSyncDirty
    Call<0x809550> ();
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