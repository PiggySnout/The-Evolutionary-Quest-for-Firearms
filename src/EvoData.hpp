#pragma once
#include "Species.hpp"

struct EvoData{
    Species species;
    float speed;
    float health;
    unsigned int passive_xp;
    unsigned int passive_gold;

    EvoData(Species species, float speed, float health, unsigned int passive_xp, unsigned int passive_gold)
        : species(species), speed(speed), health(health), passive_xp(passive_xp), passive_gold(passive_gold) {}
};