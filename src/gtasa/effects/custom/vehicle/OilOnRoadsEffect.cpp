#include "CCamera.h"
#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/GenericUtil.h"

#include <set>
#include <vector>

#include <CPathFind.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;
namespace
{
bool
pointInRadius (const CVector &p1, const CVector &center, const float R)
{
    auto dx = std::abs (p1.x - center.x);
    auto dy = std::abs (p1.y - center.y);
    auto dz = std::abs (p1.z - center.z);
    if ((dx + dy + dz) <= R) return true;

    return ((dx * dx + dy * dy + dz * dz) <= R * R);
}
} // namespace

enum class OilSpotState
{
    APPEAR,
    IDLE,
    DISAPPEAR,
    DEAD
};

struct OilSpot
{
    const float SPOT_SIZE      = 5.0f;
    const float APPEAR_TIME    = 750.0f;
    const float DISAPPEAR_TIME = 750.0f;
    const float MAX_LIFETIME   = 10000.0f;

    CVehicle        *lastVehicle = nullptr;
    OilSpotState     state       = OilSpotState::DEAD;
    CompressedVector compressedPos{};
    CVector          pos{};
    float            radius   = 0.0f;
    float            lifetime = 0.0f;
    float            angle    = 0.0f;

    OilSpot (const CompressedVector &originPos, const CVector &p,
             float r = 1.0f, float a = 0.0f)
        : compressedPos (originPos), pos (p), radius (r), angle (a)
    {
        state = OilSpotState::APPEAR;
    }

    OilSpot &
    operator= (const OilSpot &right)
    {
        if (this == &right)
        {
            return *this;
        }

        lastVehicle   = right.lastVehicle;
        state         = right.state;
        compressedPos = right.compressedPos;
        pos           = right.pos;
        radius        = right.radius;
        lifetime      = right.lifetime;
        angle         = right.angle;

        return *this;
    }

    void
    Update (float dt)
    {
        if (IsDead ()) return;
        lifetime += dt;

        if (lifetime >= APPEAR_TIME && state == OilSpotState::APPEAR)
        {
            state = OilSpotState::IDLE;
        }
        if (lifetime >= (MAX_LIFETIME - DISAPPEAR_TIME)
            && state == OilSpotState::IDLE)
        {
            state = OilSpotState::DISAPPEAR;
        }

        if (lifetime >= MAX_LIFETIME) state = OilSpotState::DEAD;
    }

    void
    Render () const
    {
        if (IsDead ()) return;

        unsigned char alpha = 255;

        if (state == OilSpotState::APPEAR)
        {
            alpha = (unsigned char) (255.0f * (lifetime / APPEAR_TIME));
        }
        if (state == OilSpotState::DISAPPEAR)
        {
            alpha = (unsigned char) (255.0f
                                     * ((MAX_LIFETIME - lifetime)
                                        / DISAPPEAR_TIME));
        }

        Command<eScriptCommands::COMMAND_DRAW_SHADOW> (6, pos.x, pos.y, pos.z,
                                                       angle, radius, alpha, 0,
                                                       0, 0);
    }

    bool
    IsDead () const
    {
        return state == OilSpotState::DEAD;
    }

    bool
    CheckCollision (CVehicle *vehicle)
    {
        if (state != OilSpotState::IDLE) return false;
        if (!vehicle || IsDead () || lastVehicle == vehicle)
        {
            return false;
        }
        if (pointInRadius (pos, vehicle->GetPosition (), SPOT_SIZE * 0.5f))
        {
            lastVehicle = vehicle;
            return true;
        }

        return false;
    }
};

bool
operator<(const CompressedVector &lhs, const CompressedVector &rhs)
{
    if (lhs.x != rhs.x)
    {
        return lhs.x < rhs.x;
    }
    if (lhs.y != rhs.y)
    {
        return lhs.y < rhs.y;
    }
    return lhs.z < rhs.z;
}

class OilOnRoadsEffect : public EffectBase
{
private:
    const float      AFFECTED_RADIUS = 128.0f;
    static const int MAX_NODES_COUNT = 1024;
    CNodeAddress     resultNodes[MAX_NODES_COUNT];
    float            gpsDistance = 0.0f;
    short            nodesCount  = 0;

    std::set<CompressedVector> pathOrigin;
    std::set<CompressedVector> oilSpotsOrigin;
    std::vector<OilSpot>       oilSpots;

    void pathSearch ();
    void spawnNewOilSpot (EffectInstance *inst);

public:
    OilOnRoadsEffect ()
    {
        oilSpots.reserve (128);
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (!GameUtil::IsPlayerSafe ()) return;
        auto *player = FindPlayerPed ();
        if (!player || player->m_nAreaCode) return;

        pathSearch ();
        spawnNewOilSpot (inst);

        auto dt = float (GenericUtil::CalculateTick ());
        GameUtil::SetVehiclesToRealPhysics ();

        for (auto &spot : oilSpots)
        {
            if (!pointInRadius (spot.pos, player->GetPosition (),
                                AFFECTED_RADIUS))
            {
                continue;
            }
            spot.Update (dt);

            if (TheCamera.IsSphereVisible (&spot.pos,
                                           spot.SPOT_SIZE * spot.radius))
            {
                spot.Render ();
            }

            for (auto *vehicle : CPools::ms_pVehiclePool)
            {
                if (vehicle->m_pDriver && spot.CheckCollision (vehicle))
                {
                    auto f = vehicle->m_fMass * dt * 0.001f
                             * -inst->Random (1.1f, 2.1f);
                    vehicle->ApplyMoveForce (-f * vehicle->m_vecMoveSpeed);

                    float turnSpeed = inst->Random (-0.5f, 0.5f);
                    if (vehicle->m_pDriver == player)
                    {
                        turnSpeed = inst->Random (-0.12f, 0.12f);
                    }
                    vehicle->m_vecTurnSpeed.z
                        = turnSpeed * vehicle->m_vecMoveSpeed.Magnitude ();
                }
            }

            if (spot.IsDead ())
            {
                oilSpotsOrigin.erase (spot.compressedPos);
            }
        }

        oilSpots.erase (std::remove_if (oilSpots.begin (), oilSpots.end (),
                                        [] (const auto &spot)
                                        { return spot.IsDead (); }),
                        oilSpots.end ());
    }
};

void
OilOnRoadsEffect::pathSearch ()
{
    auto   *player          = FindPlayerPed ();
    float   playerPosOffset = 8.0f;
    float   nextPosOffset   = 256.0f;
    auto    pos             = player->GetPosition ();
    CVector nextPos[]       = {{pos.x, pos.y + nextPosOffset, pos.z},
                               {pos.x, pos.y - nextPosOffset, pos.z},
                               {pos.x + nextPosOffset, pos.y, pos.z},
                               {pos.x - nextPosOffset, pos.y, pos.z},
                               {pos.x + nextPosOffset, pos.y + nextPosOffset, pos.z},
                               {pos.x - nextPosOffset, pos.y + nextPosOffset, pos.z},
                               {pos.x + nextPosOffset, pos.y - nextPosOffset, pos.z},
                               {pos.x - nextPosOffset, pos.y - nextPosOffset, pos.z}};

    CVector playerPos[] = {{pos.x, pos.y + playerPosOffset, pos.z},
                           {pos.x, pos.y - playerPosOffset, pos.z},
                           {pos.x + playerPosOffset, pos.y, pos.z},
                           {pos.x - playerPosOffset, pos.y, pos.z}};

    for (const auto &p : playerPos)
    {
        for (int i = 0; i < std::size (nextPos); i++)
        {
            ThePaths.DoPathSearch (0, p, {}, nextPos[i], resultNodes,
                                   &nodesCount, MAX_NODES_COUNT, &gpsDistance,
                                   nextPosOffset, nullptr, nextPosOffset, false,
                                   {}, false, false);
            for (auto j = 0; j < nodesCount; j++)
            {
                auto p = ThePaths.GetPathNode (resultNodes[j])->m_vecPosn;
                pathOrigin.emplace (p);
            }
        }
    }
}

void
OilOnRoadsEffect::spawnNewOilSpot (EffectInstance *inst)
{
    auto *player = FindPlayerPed ();
    for (auto origin : pathOrigin)
    {
        auto originPos = origin.Uncompressed ();
        if (!pointInRadius (originPos, player->GetPosition (), AFFECTED_RADIUS))
        {
            continue;
        }

        if (oilSpotsOrigin.find (origin) == oilSpotsOrigin.end ())
        {
            originPos.x += inst->Random (-5.0f, 5.0f);
            originPos.y += inst->Random (-5.0f, 5.0f);
            originPos.z
                = CWorld::FindGroundZForCoord (originPos.x, originPos.y);
            originPos.z += 0.005f; // z fighting
            auto radius = inst->Random (1.5f, 2.5f);
            auto angle  = inst->Random (0.0f, 360.0f) * 0.01745f;

            oilSpots.emplace_back (OilSpot (origin, originPos, radius, angle));

            oilSpotsOrigin.emplace (origin);
        }
    }
}

DEFINE_EFFECT (OilOnRoadsEffect, "effect_oil_on_roads", GROUP_HANDLING);