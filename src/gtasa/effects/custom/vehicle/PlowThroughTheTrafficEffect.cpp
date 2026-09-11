#include "util/EffectBase.h"
#include "util/hooks/HookMacros.h"

#include <extensions/ScriptCommands.h>

using namespace plugin;

namespace
{
bool
isPointInArea (const CVector &pos, const CVector &corner1,
               const CVector &corner2)
{
    float minX = std::min (corner1.x, corner2.x);
    float maxX = std::max (corner1.x, corner2.x);
    float minY = std::min (corner1.y, corner2.y);
    float maxY = std::max (corner1.y, corner2.y);

    return (pos.x >= minX && pos.x <= maxX && pos.y >= minY && pos.y <= maxY);
}

std::vector<CVehicle *>
GetRandomCarOfTypeInArea (const CVector &corner1, const CVector &corner2)
{
    std::vector<CVehicle *> candidates{};

    for (auto *car : CPools::ms_pVehiclePool)
    {
        if (!car || car->m_nStatus == STATUS_WRECKED) continue;

        if (isPointInArea (car->GetPosition (), corner1, corner2))
        {
            candidates.push_back (car);
        }
    }

    return candidates;
}
} // namespace

class PlowThroughTheTrafficEffect : public EffectBase
{
public:
    void
    PushCar (CVehicle *randomCar, CVehicle *playerCar)
    {
        float transSpeed = 0.0f;
        Command<eScriptCommands::COMMAND_GET_CAR_SPEED> (playerCar,
                                                         &transSpeed);
        transSpeed *= 0.01f;

        CVector inFront1{};
        Command<eScriptCommands::COMMAND_GET_CAR_FORWARD_X> (playerCar,
                                                             &inFront1.x);
        Command<eScriptCommands::COMMAND_GET_CAR_FORWARD_Y> (playerCar,
                                                             &inFront1.y);

        CVector inFront2;
        inFront2.x = inFront1.y;
        inFront2.y = inFront1.x * -1.0f;

        CVector offset{};
        CVector force{};
        Command<eScriptCommands::COMMAND_GET_CAR_COORDINATES> (randomCar,
                                                               &offset.x,
                                                               &offset.y,
                                                               &offset.z);
        Command<eScriptCommands::COMMAND_GET_CAR_COORDINATES> (playerCar,
                                                               &force.x,
                                                               &force.y,
                                                               &force.z);

        offset.x -= force.x;
        offset.y -= force.y;

        float temp1   = inFront2.x * offset.x;
        float temp2   = inFront2.y * offset.y;
        float dotProd = temp1 + temp2;

        if (dotProd < 2.5f && dotProd > -2.5)
        {
            if (dotProd > 0.0)
            {
                dotProd = 1.0f;
            }
            else
            {
                dotProd = -1.0f;
            }

            float temp1 = inFront1.x * transSpeed;
            float temp2 = dotProd * inFront2.x;
            temp2 *= 0.5f;
            float temp3 = transSpeed * temp2;
            force.x     = temp1 + temp3;

            temp1 = inFront1.y * transSpeed;
            temp2 = dotProd * inFront2.y;
            temp2 *= 0.5f;
            temp3   = transSpeed * temp2;
            force.y = temp1 + temp3;

            force.z = transSpeed + 0.008f;
            force.z *= 0.5f;

            offset.x = -1.0f;
            offset.x *= (dotProd * inFront2.x * transSpeed);
            offset.y = -1.0f;
            offset.y *= (dotProd * inFront2.y * transSpeed);
            offset.z = 0.0f;

            force *= 0.5f;

            CCarCtrl::SwitchVehicleToRealPhysics (randomCar);
            Command<eScriptCommands::COMMAND_APPLY_FORCE_TO_CAR> (
                randomCar, force.x, force.y, force.z, offset.x, offset.y,
                offset.z);
        }
    }

    void
    OnTick (EffectInstance *inst) override
    {
        auto *player = FindPlayerPed ();
        if (!player) return;

        auto *playerCar = player->m_pVehicle;
        if (!player->m_nPedFlags.bInVehicle && !playerCar)
        {
            return;
        }

        CVector inFront1{};
        CVector inFront2{};
        Command<eScriptCommands::COMMAND_GET_OFFSET_FROM_CAR_IN_WORLD_COORDS> (
            playerCar, -3.0f, 2.0f, 0.0f, &inFront1.x, &inFront1.y,
            &inFront1.z);
        Command<eScriptCommands::COMMAND_GET_OFFSET_FROM_CAR_IN_WORLD_COORDS> (
            playerCar, 3.0f, 11.0f, 0.0f, &inFront2.x, &inFront2.y,
            &inFront2.z);

        const auto &randomCars = GetRandomCarOfTypeInArea (inFront1, inFront2);

        for (auto *car : randomCars)
        {
            if (car && car != playerCar)
            {
                PushCar (car, playerCar);
            }
        }
    }
};

DEFINE_EFFECT (PlowThroughTheTrafficEffect, "effect_plow_through_the_traffic",
               0);