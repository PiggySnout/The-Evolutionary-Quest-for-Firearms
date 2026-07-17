
#pragma once

#include <raylib.h>
#include <ctime>
#include "Bullet.h"
#include "textures.h"
#include "Weapon.h"
#include "Species.h"



class Player {

public:
    Player(const Textures& T);
    void Draw(Vector2 pos) const;
    void UpdateTexture();
    bool Input();
    Vector2 getPos() const;
    int getGold() const;
    int getXP() const;

    void giveGold(int gold);
    void giveXp(int xp);

    Vector2 getTextureDim();

    void TakeDamage(float damage);

    float getHealth() const;

    bool KillIfNec();

    bool IsDead() const;

    void Heal(float a);

    void Evolve();
    

private:

    Species S;
    Texture2D& texture1;
    Texture2D& texture2;
    Texture2D& texture1_death;
    Texture2D& texture2_death;
    float x, y;
    
    bool textureToUse;
    Family F;
    float speed;

    unsigned int xp;
    unsigned int gold;

    float hp;

    bool facingRight;

    int damageTimer;

    bool dead;
    
    int evo_level;

    Vector2 Correct(Vector2 V) const;

    const Textures& T;

    
};