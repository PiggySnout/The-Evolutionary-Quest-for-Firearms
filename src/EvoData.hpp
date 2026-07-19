#pragma once
#include "Species.hpp"

struct EvoData{
    Species species;
    float speed;
    float health;
    unsigned int passive_xp;
    unsigned int passive_gold;
    int price;

    EvoData(Species species, float speed, float health, unsigned int passive_xp, unsigned int passive_gold, int price)
        : species(species), speed(speed), health(health), passive_xp(passive_xp), passive_gold(passive_gold), price(price) {}
};