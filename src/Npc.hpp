#pragma once
#include "raylib.h"
#include <vector>
#include <ctime>
#include "textures.hpp"
#include "Species.hpp"
enum class AIType{Coward, Hunter, Tank, Pack, Ambush};




class Npc{

public:

    Npc(Textures& T, Species S, Vector2 Pos, int hp, int gold, int xp, float speed, float damage, AIType AI, std::vector<Npc>* Npcs);
    int getHp() const;
    int getGoldDrops() const;
    int getXpDrops() const;
    Vector2 getPos() const;

    void TakeDamage(int damage);
    bool ChangeTexture(); //returns whether the NPC should be deleted or not

    void Draw(Vector2 POS) const;

    bool shouldDie() const;
    bool shouldDespawn() const;

    Vector2 GetWH()const;
    void Update();

    void UpdatePlayerPos(Vector2 playerPos);
    void UpdatePlayerSize(Vector2 playerSize);

    bool CheckPlayerCollision();

    void Move();

    void HunterMove(); //fast, aggro if it can see u
    void CowardMove(); //very fast, runs away, if you are far away enough it forgets
    void PackMove(); //aggroes all other Npcs within a certain radius
    void TankMove(); //slow, more hp
    void AmbushMove(); //agroes if very close.


    void Aggro();

    AIType getAI() const;

    float getDamage() const;

    Vector2 getPlayerPos() const;
    
private:

    AIType AI;

    Species S;
    Family F;
    
    std::vector<Npc>* Npcs;
    const Texture2D* Frame1;
    const Texture2D* Frame2;
    const Texture2D* DeathFrame1;
    const Texture2D* DeathFrame2;
    Vector2 Pos;
    Vector2 playerPos;
    Vector2 playerSize;

    Vector2 Destination;

    bool aggroed;

    int hp;
    int max_hp;
    int goldDrops;
    int xpDrops;
    int timer;
    float damage;
    bool CurrentT;
    int IsTakingDamageTimer;

    float speed;

    int MoveTimer;

    time_t TextureTimer;

    bool facingRight;
    Vector2 Correct(Vector2 V) const;


};