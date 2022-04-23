#include <util/EffectBase.h>
#include <util/GenericUtil.h>

#include <extensions/ScriptCommands.h>

using namespace plugin;

class SwapVehiclesOnImpactEffect : public EffectBase
{
    static inline ThiscallEvent<
        AddressList<0x54BDB2, H_CALL, 0x54BF78, H_CALL, 0x54C23A, H_CALL,
                    0x54C435, H_CALL, 0x54D17E, H_CALL, 0x54D27E, H_CALL,
                    0x54D3FE, H_CALL, 0x54D4D2, H_CALL>,
        PRIORITY_AFTER,
        ArgPick<ArgTypes<CPhysical *, CPhysical *, int, float *, int>, 0, 1, 2,
                3, 4>,
        void (CPhysical *, CPhysical *, int, float *, int)>
        applyCollisionEvent;

    static inline std::map<CVehicle *, int> vehicleCooldowns;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        vehicleCooldowns.clear ();

        applyCollisionEvent += ApplyCollision;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        applyCollisionEvent -= ApplyCollision;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        std::vector<CVehicle *> toErase;

        int wait = (int) GenericUtil::CalculateTick ();
        for (auto const &[vehicle, vehicleWait] : vehicleCooldowns)
        {
            vehicleCooldowns[vehicle] -= wait;
            if (vehicleCooldowns[vehicle] < 0) toErase.push_back (vehicle);
        }

        for (CVehicle *erase : toErase)
            vehicleCooldowns.erase (erase);
    }

    static void
    ApplyCollision (CPhysical *thisEntity, CPhysical *otherEntity, int a3,
                    float *a4, int a5)
    {
        if (thisEntity->m_nType != eEntityType::ENTITY_TYPE_VEHICLE
            || otherEntity->m_nType != eEntityType::ENTITY_TYPE_VEHICLE)
        {
            return;
        }

        CVehicle *thisVehicle  = (CVehicle *) thisEntity;
        CVehicle *otherVehicle = (CVehicle *) otherEntity;

        if (vehicleCooldowns[thisVehicle] > 0
            || vehicleCooldowns[otherVehicle] > 0)
        {
            return;
        }

        CPed *thisDriver  = thisVehicle->m_pDriver;
        CPed *otherDriver = otherVehicle->m_pDriver;

        // Get peds out of their vehicles
        if (thisDriver)
        {
            Command<eScriptCommands::
                        COMMAND_REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION> (
                thisDriver, thisVehicle);
        }
        if (otherDriver)
        {
            Command<eScriptCommands::
                        COMMAND_REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION> (
                otherDriver, otherVehicle);
        }

        CPlayerPed *player = FindPlayerPed ();
        bool        wasPlayerADriver
            = player && (player == thisDriver || player == otherDriver);

        if (thisDriver)
        {
            eCarDrivingStyle drivingStyle
                = (wasPlayerADriver && player == otherDriver)
                      ? eCarDrivingStyle::DRIVINGSTYLE_PLOUGH_THROUGH
                      : eCarDrivingStyle::DRIVINGSTYLE_STOP_FOR_CARS;

            WarpPedIntoCar (thisDriver, otherVehicle, drivingStyle);
        }
        if (otherDriver)
        {
            eCarDrivingStyle drivingStyle
                = (wasPlayerADriver && player == thisDriver)
                      ? eCarDrivingStyle::DRIVINGSTYLE_PLOUGH_THROUGH
                      : eCarDrivingStyle::DRIVINGSTYLE_STOP_FOR_CARS;

            WarpPedIntoCar (otherDriver, thisVehicle, drivingStyle);
        }

        if (wasPlayerADriver)
        {
            Command<eScriptCommands::COMMAND_RESTORE_CAMERA_JUMPCUT> ();
        }

        // Set vehicle cooldowns
        vehicleCooldowns[thisVehicle]  = 1000;
        vehicleCooldowns[otherVehicle] = 1000;
    }

    static void
    WarpPedIntoCar (CPed *ped, CVehicle *vehicle, eCarDrivingStyle drivingStyle)
    {
        CPlayerPed *player = FindPlayerPed ();

        Command<eScriptCommands::COMMAND_WARP_CHAR_INTO_CAR> (ped, vehicle);

        if (ped != player)
        {
            Command<eScriptCommands::COMMAND_TASK_CAR_DRIVE_WANDER> (
                ped, vehicle, 20.0f, drivingStyle);
        }
    }
};

DEFINE_EFFECT (SwapVehiclesOnImpactEffect, "effect_swap_vehicles_on_impact", 0);