#pragma once

class GlobalRenderer
{
    typedef void (*BuildingRenderFunctionHook) (CBuilding *, RwFrame *);
    static inline std::vector<BuildingRenderFunctionHook> renderBuildingHooks
        = {};

    typedef void (*ObjectRenderFunctionHook) (CObject *, RwFrame *);
    static inline std::vector<ObjectRenderFunctionHook> renderObjectHooks = {};

    typedef void (*VehicleRenderFunctionHook) (CVehicle *, RwFrame *);
    static inline std::vector<VehicleRenderFunctionHook> renderVehicleHooks
        = {};

    static void Hooked_FrameSyncDirty ();

    static void RenderBuilding (CBuilding *building, bool reset = false);
    static void ResetBuildings ();

    static void RenderObject (CObject *object, bool reset = false);
    static void ResetObjects ();

    static void RenderVehicle (CVehicle *vehicle, bool reset = false);
    static void ResetVehicles ();

public:
    static inline struct RenderBuildingEventStruct
    {
        void
        operator+= (BuildingRenderFunctionHook function)
        {
            auto hook = std::find (renderBuildingHooks.begin (),
                                   renderBuildingHooks.end (), function);
            if (hook == renderBuildingHooks.end ())
            {
                renderBuildingHooks.push_back (function);
            }
        }

        void
        operator-= (BuildingRenderFunctionHook function)
        {
            renderBuildingHooks.erase (
                std::remove (renderBuildingHooks.begin (),
                             renderBuildingHooks.end (), function),
                renderBuildingHooks.end ());

            if (renderBuildingHooks.size () == 0)
            {
                ResetBuildings ();
            }
        }
    } RenderBuildingEvent;

    static inline struct RenderObjectEventStruct
    {
        void
        operator+= (ObjectRenderFunctionHook function)
        {
            auto hook = std::find (renderObjectHooks.begin (),
                                   renderObjectHooks.end (), function);
            if (hook == renderObjectHooks.end ())
            {
                renderObjectHooks.push_back (function);
            }
        }

        void
        operator-= (ObjectRenderFunctionHook function)
        {
            renderObjectHooks.erase (std::remove (renderObjectHooks.begin (),
                                                  renderObjectHooks.end (),
                                                  function),
                                     renderObjectHooks.end ());

            if (renderObjectHooks.size () == 0)
            {
                ResetObjects ();
            }
        }
    } RenderObjectEvent;

    static inline struct RenderVehicleEventStruct
    {
        void
        operator+= (VehicleRenderFunctionHook function)
        {
            auto hook = std::find (renderVehicleHooks.begin (),
                                   renderVehicleHooks.end (), function);
            if (hook == renderVehicleHooks.end ())
            {
                renderVehicleHooks.push_back (function);
            }
        }

        void
        operator-= (VehicleRenderFunctionHook function)
        {
            renderVehicleHooks.erase (std::remove (renderVehicleHooks.begin (),
                                                   renderVehicleHooks.end (),
                                                   function),
                                      renderVehicleHooks.end ());

            if (renderVehicleHooks.size () == 0)
            {
                ResetVehicles ();
            }
        }
    } RenderVehicleEvent;

    static void Initialise ();
};