#pragma once

enum class type{Rock, Sharp_Rock, SlingShot, Knife, Bow, Crossbow, AK_47};
struct weaponStat{
    type T;
    int damage;
    float speed;
    int range;
    int rechargeTime;
    int price;

    weaponStat() : T(type::Rock),
                   damage(0),
                   speed(0.0f),
                   range(0),
                   rechargeTime(0),
                   price(0)
    {}

    weaponStat(type T, int damage, float speed, int range, int rechargeTime, int price) : 
                   T(T),
                   damage(damage),
                   speed(speed),
                   range(range),
                   rechargeTime(rechargeTime),
                   price(price)
    {}
};