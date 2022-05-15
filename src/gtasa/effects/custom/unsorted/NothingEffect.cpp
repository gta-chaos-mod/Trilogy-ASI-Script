#include "effects/OneTimeEffect.h"

class NothingEffect : public OneTimeEffect
{
    std::vector<std::string> randomNames = {"Nothing",
                                            "404: Effect Not Found",
                                            "All Peds Are Peds",
                                            "Teleport To Current Location",
                                            "Spawn Air",
                                            "Destroy All Destroyed Vehicles",
                                            "Kill All Dead Peds",
                                            "+0 Wanted Stars",
                                            "Jesus Watches Over You",
                                            "Set Time To Current Time",
                                            "Set Player Into Current Vehicle",
                                            "All Cops Are Cops",
                                            "Aim To Point Gun",
                                            "Give Everyone A Nose",
                                            "Flying Birds",
                                            "Teleport All Elephants To Player",
                                            "PC Experience",
                                            "All Enemies Attack Player",
                                            "No Crash",
                                            " "};

public:
    void
    OnStart (EffectInstance *inst) override
    {
        int randomNameID = inst->Random (0, (int) randomNames.size () - 1);

        inst->OverrideName (randomNames[randomNameID]);
    }
};

DEFINE_EFFECT (NothingEffect, "effect_nothing", 0);