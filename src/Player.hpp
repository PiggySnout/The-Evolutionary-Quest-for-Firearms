
#pragma once

#include <raylib.h>
#include <ctime>
#include "Bullet.hpp"
#include "textures.hpp"
#include "Weapon.hpp"
#include "Species.hpp"

#include <memory>
#include "EvoData.hpp"

class Player {

public:
    Player(Textures& T, std::vector<EvoData>& EvoStats);
    void Draw(Vector2 pos) const;
    void UpdateTexture();
    bool Input();
    Vector2 getPos() const;
    int getGold() const;
    int getXP() const;
    int getPassiveGold() const;
    int getPassiveXp() const;

    void giveGold(int gold);
    void giveXp(int xp);

    Vector2 getTextureDim();

    void TakeDamage(float damage);

    float getHealth() const;

    bool KillIfNec();

    bool IsDead() const;

    void Heal(float a);

    bool Evolve();
    void Evolve(int choice);
    
    float getMaxHealth() const;

    const EvoData& findInEvoStats(Species S, int i);

    bool getEvolving() const;

    std::vector<Species> getNext() const;

    void setTextureFor(Species S);

    void StopEvol();

    int getEvo_Level() const;

    Species getSpecies() const;

    float getSpeed() const;

private:


    std::vector<Species> Next;
    std::vector<EvoData>& EvoStats;
    Species S;
    Texture2D* texture1;
    Texture2D* texture2;
    Texture2D* texture1_death;
    Texture2D* texture2_death;
    float x, y;
    bool evolving;
    
    bool textureToUse;
    float speed;

    unsigned int xp;
    unsigned int gold;

    int passiveXp;
    int passiveGold;

    float hp;
    float max_hp;

    bool facingRight;

    int damageTimer;

    bool dead;
    
    int evo_level;

    Vector2 Correct(Vector2 V) const;

    Textures& T;

    
};