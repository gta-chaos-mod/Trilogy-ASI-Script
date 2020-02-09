#include "Teleport.h"

Teleport::Teleport (CVector destination) : EffectPlaceholder ("teleport")
{
    this->destination = destination;
}

void
Teleport::Enable ()
{
    EffectPlaceholder::Enable ();

    CEntity *entity = FindPlayerEntity ();
    if (entity)
    {
        entity->Teleport (destination);

        CGame::currArea     = 0;
        entity->m_nInterior = 0;

        CStreaming::RemoveBuildingsNotInArea (0);

        CWorld::Remove (entity);
        CWorld::Add (entity);

        CPed *player = FindPlayerPed ();
        if (player)
        {
            player->m_nInterior = 0;

            CWorld::Remove (player);
            CWorld::Add (player);
        }

        CStreaming::StreamZoneModels (&destination);
        CTimeCycle::StopExtraColour (false);
    }
}
