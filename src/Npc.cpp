#include "Npc.hpp"
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <algorithm>
Vector2 WorldToScreen(Vector2 V, Vector2 PlayerPos){
    const float cx = GetScreenWidth() / 2; 
    const float cy = GetScreenHeight() / 2; 

    V.x += cx;
    V.y += cy;
    V.x -= PlayerPos.x;
    V.y -= PlayerPos.y;
    return V;
}
Npc::Npc(Textures& T, Species S, Vector2 Pos, int hp, int gold, int xp, float speed, float damage, AIType AI, std::vector<Npc>* Npcs) : 
                                                        S(S),
                                                        Pos(Pos),
                                                        hp(hp),
                                                        timer(180),
                                                        CurrentT(false),
                                                        Frame1(&T.Single_Cell_1),
                                                        Frame2(&T.Single_Cell_2),
                                                        DeathFrame1(&T.Single_Cell_1_Death),
                                                        DeathFrame2(&T.Single_Cell_2_Death),
                                                        IsTakingDamageTimer(0),
                                                        goldDrops(gold),
                                                        xpDrops(xp),
                                                        playerPos({0,0}),
                                                        playerSize({0,0}),
                                                        aggroed(false),
                                                        speed(speed),
                                                        Destination(Pos),
                                                        MoveTimer(0),
                                                        AI(AI),
                                                        damage(damage),
                                                        max_hp(hp),
                                                        TextureTimer(std::time(nullptr)),
                                                        facingRight(true),
                                                        Npcs(Npcs)

{
}
int Npc::getHp() const{
    return hp;
}
int Npc::getGoldDrops() const{
    return goldDrops;
}
int Npc::getXpDrops() const{
    return xpDrops;
}

void Npc::TakeDamage(int damage){
    hp -= damage;
    if (hp > 0)
        IsTakingDamageTimer = 30;
    else
        timer = 120;
    Aggro();
}
bool Npc::ChangeTexture(){

    if (hp > 0 && std::time(nullptr) - TextureTimer >= 1){
        CurrentT = !CurrentT;
        TextureTimer = std::time(nullptr);
    }
    if (hp <= 0)
        return true;
    return false;
}

void Npc::Update(){
    if (timer > 0)
        --timer;
    if (IsTakingDamageTimer > 0)
        --IsTakingDamageTimer;
}
void Npc::Draw(Vector2 POS) const{
    const Texture2D* Texture;
    if (!CurrentT && hp > 0)
        Texture = Frame1;
    else if (hp > 0)
        Texture = Frame2;
    else if (!CurrentT)
        Texture = DeathFrame1;
    else
        Texture = DeathFrame2;
    
    Rectangle Src{
        facingRight ? 0 : static_cast<float>(Texture->width),
        0,
        facingRight ? static_cast<float>(Texture->width) : -static_cast<float>(Texture->width),
        static_cast<float>(Texture->height)
    };
    Rectangle Dest{
        POS.x,
        POS.y,
        Texture->width * 10.0f,
        Texture->height * 10.0f
    };

    DrawTexturePro(*Texture, Src, Dest, {0,0}, 0.0f, IsTakingDamageTimer > 0 && hp > 0 ? RED : WHITE);
}
Vector2 Npc::getPos() const{
    return Pos;
}
Vector2 Npc::GetWH()const{
    return {static_cast<float>(Frame1->width), static_cast<float>(Frame1->height)};
}

bool Npc::shouldDie() const{
    return hp <= 0 && timer <= 0;
}

bool Npc::shouldDespawn() const{
    return Vector2Distance(playerPos, Pos) > 2500;
}

void Npc::UpdatePlayerPos(Vector2 playerPos){

    this->playerPos = playerPos;
}
void Npc::UpdatePlayerSize(Vector2 playerSize){
    this->playerSize = playerSize;
}

bool Npc::CheckPlayerCollision(){
    if (hp <= 0)
        return false;
    Vector2 V{
        playerSize.x,
        playerSize.y
    };
    V = Correct(V);
    //playerPos = Correct(playerPos); //WRONG just keeping it here as a
    Rectangle PLAYER{
        playerPos.x - 50,
        playerPos.y - 45,
        V.x,
        V.y
    };
    Rectangle NPC{
        Pos.x,
        Pos.y,
        Correct({static_cast<float>(Frame1->width), 0}).x * 2,
        Correct({0,static_cast<float>(Frame1->height)}).y * 2,
    };
    return CheckCollisionRecs(PLAYER, NPC);
}

void Npc::Move(){
    if (hp <= 0)
        return;

    
    switch (AI){
        case AIType::Coward:
            CowardMove();
            break;
        case AIType::Ambush:
            AmbushMove();
            break;
        case AIType::Hunter:
            HunterMove();
            break;
        case AIType::Pack:
            PackMove();
            break;
        case AIType::Tank:
            TankMove();
            break;
    }
}
void Npc::Aggro(){
    aggroed = true;
    Destination = playerPos;
}


void Npc::HunterMove(){ //fast, aggro if it can see u
    if (hp <= 0)
        return;
    if (Vector2Distance(playerPos, Pos) <= 250)
        aggroed = true;
    else 
        aggroed = false;

    if (speed != 0.9f)
        speed = 0.9f;

    if (aggroed)
        Destination = {playerPos.x - 50, playerPos.y - 45};
    else if (Vector2Distance(Pos, Destination) < 2.0f){
        if (aggroed)
            return;
        else if (MoveTimer == -1)
            MoveTimer = 180;
        else if (MoveTimer <= 0){
            Destination.x = Pos.x + GetRandomValue(-200, 200);
            Destination.y = Pos.y + GetRandomValue(-200, 200);
            MoveTimer = -1;
        }
        else if (MoveTimer > 0)
            --MoveTimer;
    }

    Vector2 move = Vector2Subtract(Destination, Pos);
    move = Vector2Normalize(move);
    move = Vector2Scale(move, speed);
    if (move.x < 0 && facingRight && MoveTimer == -1)
        facingRight = false;
    if (move.x > 0 && !facingRight && MoveTimer == -1)
        facingRight = true;
    Pos = Vector2Add(Pos, move);
}
void Npc::CowardMove(){ //very fast, runs away, if you are far away enough it forgets
    if (hp <= 0)
        return;
    if (Vector2Distance(playerPos, Pos) > 250 && aggroed)
        aggroed = false;

    if (speed != 1.0f)
        speed = 1.0f;

    if (aggroed)
        Destination = {playerPos.x - 50, playerPos.y - 45};
    else if (Vector2Distance(Pos, Destination) < 2.0f){
        if (MoveTimer == -1)
            MoveTimer = 180;
        else if (MoveTimer <= 0){
            Destination.x = Pos.x + GetRandomValue(-200, 200);
            Destination.y = Pos.y + GetRandomValue(-200, 200);
            MoveTimer = -1;
        }
        else if (MoveTimer > 0)
            --MoveTimer;
    }

    Vector2 move = Vector2Subtract(Pos, Destination);
    move = Vector2Normalize(move);
    move = Vector2Scale(move, speed);
    if (move.x < 0 && facingRight && MoveTimer == -1)
        facingRight = false;
    if (move.x > 0 && !facingRight && MoveTimer == -1)
        facingRight = true;
    Pos = Vector2Add(Pos, move);
} 
void Npc::PackMove(){ //aggroes all other Npcs within a certain radius
    if (hp <= 0)
        return;
    if (Vector2Distance(playerPos, Pos) > 250 && aggroed)
        aggroed = false;

    if (speed != 0.7f)
        speed = 0.7f;

    if (aggroed){
        Destination = {playerPos.x - 50, playerPos.y - 45};
        for (Npc& i : *Npcs){
            if (&i == this)
                continue;
            if (Vector2Distance(i.getPos(), Pos) <= 200)
                i.Aggro();
        }
    }
    else if (Vector2Distance(Pos, Destination) < 2.0f){
        if (MoveTimer == -1)
            MoveTimer = 180;
        else if (MoveTimer <= 0){
            Destination.x = Pos.x + GetRandomValue(-200, 200);
            Destination.y = Pos.y + GetRandomValue(-200, 200);
            MoveTimer = -1;
        }
        else if (MoveTimer > 0)
            --MoveTimer;
    }

    Vector2 move = Vector2Subtract(Pos, Destination);
    move = Vector2Normalize(move);
    move = Vector2Scale(move, speed);
    if (move.x < 0 && facingRight && MoveTimer == -1)
        facingRight = false;
    if (move.x > 0 && !facingRight && MoveTimer == -1)
        facingRight = true;
    Pos = Vector2Add(Pos, move);


    
}
void Npc::TankMove(){ //slow, more hp
    if (hp <= 0)
        return;
    if (Vector2Distance(playerPos, Pos) > 250)
        aggroed = false;

    if (speed != 0.5f)
        speed = 0.5f;
    
    if (hp == max_hp){
        max_hp *= 2.0f;
        hp = max_hp;
        ++max_hp;
    }
    if (aggroed)
        Destination = {playerPos.x - 50, playerPos.y - 45};
    else if (Vector2Distance(Pos, Destination) < 2.0f){
        if (MoveTimer == -1)
            MoveTimer = 180;
        else if (MoveTimer <= 0){
            Destination.x = Pos.x + GetRandomValue(-200, 200);
            Destination.y = Pos.y + GetRandomValue(-200, 200);
            MoveTimer = -1;
        }
        else if (MoveTimer > 0)
            --MoveTimer;
    }

    Vector2 move = Vector2Subtract(Destination, Pos);
    move = Vector2Normalize(move);
    move = Vector2Scale(move, speed);
    if (move.x < 0 && facingRight && MoveTimer == -1)
        facingRight = false;
    if (move.x > 0 && !facingRight && MoveTimer == -1)
        facingRight = true;
    Pos = Vector2Add(Pos, move);
}
void Npc::AmbushMove(){
    if (hp <= 0)
        return;
    if (Vector2Distance(playerPos, Pos) <= 50)
        aggroed = true;
    else if (Vector2Distance(playerPos, Pos) > 250)
        aggroed = false;

    if (speed != 0.7f)
        speed = 0.7f;
    

    
    if (aggroed)
        Destination = {playerPos.x - 50, playerPos.y - 45};
    else if (Vector2Distance(Pos, Destination) < 2.0f){
        if (MoveTimer == -1)
            MoveTimer = 180;
        else if (MoveTimer <= 0){
            Destination.x = Pos.x + GetRandomValue(-200, 200);
            Destination.y = Pos.y + GetRandomValue(-200, 200);
            MoveTimer = -1;
        }
        else if (MoveTimer > 0)
            --MoveTimer;
    }

    Vector2 move = Vector2Subtract(Destination, Pos);
    move = Vector2Normalize(move);
    move = Vector2Scale(move, speed);

    if (move.x < 0 && facingRight && MoveTimer == -1)
        facingRight = false;
    if (move.x > 0 && !facingRight && MoveTimer == -1)
        facingRight = true;


    Pos = Vector2Add(Pos, move);
}

float Npc::getDamage() const{
    return damage;
} 

AIType Npc::getAI() const{
    return AI;
}

Vector2 Npc::Correct(Vector2 V) const{

    float proportionW = playerSize.x / 100.0f;
    float proportionH = playerSize.y / 90.0f;

    float scale = proportionW > proportionH ? proportionW : proportionH;
    scale = 1.0f / scale;
    V = Vector2Scale(V, scale);

    return V;
}


Vector2 Npc::getPlayerPos() const{
    return playerPos;
}