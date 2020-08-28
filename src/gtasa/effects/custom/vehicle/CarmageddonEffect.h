#pragma once

#include "util/EffectBase.h"
#include "util/GameUtil.h"
#include "util/RandomHelper.h"

class CarmageddonEffect : public EffectBase
{
private:
    int                       wait        = 0;
    std::map<CVehicle *, int> vehicleList = {};
    std::vector<int>          possibleVehicles
        = {
        400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410, 411, 412,
        413, 414, 415, 416, 418, 419, 420, 421, 422, 423, 424, 426, 427,
        428, 429, 431, 433, 434, 436, 437, 438, 439, 440, 442, 443, 444,
        445, 448, 451, 455, 456, 457, 458, 459, 461, 462, 463, 466, 467,
        468, 470, 471, 474, 475, 477, 478, 479, 480, 482, 483, 485, 489,
        490, 491, 492, 494, 495, 496, 498, 499, 500, 502, 503, 504, 505,
        506, 507, 508, 516, 517, 518, 521, 522, 523, 525, 526, 527, 528,
        529, 530, 531, 533, 534, 535, 536, 538, 540, 541, 542, 543, 545,
        546, 547, 549, 550, 551, 552, 554, 555, 558, 559, 560, 561, 562,
        565, 566, 567, 568, 571, 572, 574, 575, 576, 579, 580, 581, 582,
        583, 585, 586, 587, 588, 589, 596, 597, 598, 599, 600, 602, 603
    };

    void  RemoveExplodedVehicles (int step);
    float GetSpawnDistance ();

public:
    CarmageddonEffect ();

    void HandleTick ();
};
