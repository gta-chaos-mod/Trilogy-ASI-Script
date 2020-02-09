#include "Teleport.h"

Teleport::Teleport (CVector destination) : EffectBase ("teleport")
{
    this->destination = destination;
}

void
Teleport::Enable ()
{
    EffectBase::Enable ();

    CEntity *entity = FindPlayerEntity ();
    if (entity)
    {
        entity->Teleport (destination);

        CWorld::Remove (entity);
        CWorld::Add (entity);

        CPed *player = FindPlayerPed ();
        if (player)
        {
            CWorld::Remove (player);
            CWorld::Add (player);
        }

        CStreaming::StreamZoneModels (destination);
    }
}
