#pragma once
#include "raylib.h"
#include "textures.h"
#include "raymath.h"
#include <vector>
#include "Bullet.h"
#include "WeaponData.h"

class Weapon{

public:
    Weapon(Textures& T, std::vector<weaponStat>& VWS);
    void LevelUp();
    void Draw(Vector2 pos) const;
    Texture2D* getTexture() const;
    float getAngle(Vector2 v1, Vector2 v2)const;
    bool SpawnBullet(Vector2 playerPos, Vector2 mousePos, std::vector<Bullet>& Bullets);
    int getak_number() const;
    void PrintAmmo() const;
    bool hasAmmo() const;
    void reload();
    int getReloadTime() const;
    int getPrice() const;

    type getType() const;
private:
    int ak_number;
    Texture2D* texture;
    Texture2D* bulletTexture;
    Textures& T;
    std::vector<weaponStat>& VWS;

    bool isLoaded;
    int ammo;
    int maxammo;

    type Type;
    int damage;
    float speed; //at least those 2 work

    int range; //maybe? it should.
    int rechargeTime;
    int price; 
};