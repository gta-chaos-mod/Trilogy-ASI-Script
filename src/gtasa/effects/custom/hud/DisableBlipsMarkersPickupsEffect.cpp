#include "util/EffectBase.h"

using namespace plugin;

class DisableBlipsMarkersPickupsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        injector::MakeJMP (0x58AA2D, Hooked_CRadar_DrawBlips);
        injector::MakeCALL (0x575B44, Hooked_CRadar_DrawBlips);

        injector::MakeCALL (0x53E18E, Hooked_CCoronas_Render);

        injector::MakeJMP (0x59F1ED, Hooked_CEntity_Render);

        injector::MakeCALL (0x7250B1, Hooked_C3dMarker_Render);
        injector::MakeCALL (0x72606F, Hooked_CCheckpoint_Render);
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        // TODO: Unhook
    }

    static void
    Hooked_CRadar_DrawBlips ()
    {
    }

    static void
    Hooked_CCoronas_Render ()
    {
    }

    static void
    Hooked_CEntity_Render (CEntity *thisEntity)
    {
        if (!thisEntity
            || thisEntity->m_nType == eEntityType::ENTITY_TYPE_OBJECT
                   && static_cast<CObject *> (thisEntity)->m_nObjectType == 5)
        {
            // Rendern't
            return;
        }

        CallMethod<0x534310, CEntity *> (thisEntity);
    }

    static void
    Hooked_C3dMarker_Render ()
    {
    }

    static void
    Hooked_CCheckpoint_Render ()
    {
    }
};

DEFINE_EFFECT (DisableBlipsMarkersPickupsEffect,
               "effect_disable_blips_markers_pickups", GROUP_HUD);