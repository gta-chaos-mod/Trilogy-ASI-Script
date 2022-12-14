#include "effects/OneTimeEffect.h"

#include <CRadar.h>

class ShuffleBlipsEffect : public OneTimeEffect
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        std::vector<unsigned char> validTraces = {};
        for (int i = 0; i < MAX_RADAR_TRACES; i++)
        {
            tRadarTrace trace = CRadar::ms_RadarTrace[i];
            if (trace.m_nBlipType != eBlipType::BLIP_NONE)
                validTraces.push_back (trace.m_nRadarSprite);
        }

        std::shuffle (std::begin (validTraces), std::end (validTraces),
                      inst->GetRNG ());

        for (int i = 0; i < validTraces.size (); i++)
        {
            CRadar::ms_RadarTrace[i].m_nRadarSprite = validTraces[i];
        }
    }
};

DEFINE_EFFECT (ShuffleBlipsEffect, "effect_shuffle_blips", 0);