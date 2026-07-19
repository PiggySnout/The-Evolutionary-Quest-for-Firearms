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
                                                        Frame1(nullptr),
                                                        Frame2(nullptr),
                                                        DeathFrame1(nullptr),
                                                        DeathFrame2(nullptr),
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
                                                        Npcs(Npcs),
                                                        T(&T)

{
    switch (S){
        case Species::Amphibian:
            Frame1 = &T.Amphibian_1;
            Frame2 = &T.Amphibian_2;
            DeathFrame1 = &T.Amphibian_1_Death;
            DeathFrame2 = &T.Amphibian_2_Death;
            break;
        case Species::Bird:
            Frame1 = &T.Bird_1;
            Frame2 = &T.Bird_2;
            DeathFrame1 = &T.Bird_1_Death;
            DeathFrame2 = &T.Bird_2_Death;
            break;
        case Species::Bush:
            Frame1 = &T.Bush_1;
            Frame2 = &T.Bush_2;
            DeathFrame1 = &T.Bush_1_Death;
            DeathFrame2 = &T.Bush_2_Death;
            break;
        case Species::Canine:
            Frame1 = &T.Canine_1;
            Frame2 = &T.Canine_2;
            DeathFrame1 = &T.Canine_1_Death;
            DeathFrame2 = &T.Canine_2_Death;
            break;
        case Species::Crocodile:
            Frame1 = &T.Crocodile_1;
            Frame2 = &T.Crocodile_2;
            DeathFrame1 = &T.Crocodile_1_Death;
            DeathFrame2 = &T.Crocodile_2_Death;
            break;
        case Species::Feline:
            Frame1 = &T.Feline_1;
            Frame2 = &T.Feline_2;
            DeathFrame1 = &T.Feline_1_Death;
            DeathFrame2 = &T.Feline_2_Death;
            break;
        case Species::Fish:
            Frame1 = &T.Fish_1;
            Frame2 = &T.Fish_2;
            DeathFrame1 = &T.Fish_1_Death;
            DeathFrame2 = &T.Fish_2_Death;
            break;
        case Species::Flower:
            Frame1 = &T.Flower_1;
            Frame2 = &T.Flower_2;
            DeathFrame1 = &T.Flower_1_Death;
            DeathFrame2 = &T.Flower_2_Death;
            break;
        case Species::Fungus:
            Frame1 = &T.Fungus_1;
            Frame2 = &T.Fungus_2;
            DeathFrame1 = &T.Fungus_1_Death;
            DeathFrame2 = &T.Fungus_2_Death;
            break;
        case Species::Grass:
            Frame1 = &T.Grass_1;
            Frame2 = &T.Grass_2;
            DeathFrame1 = &T.Grass_1_Death;
            DeathFrame2 = &T.Grass_2_Death;
            break;
        case Species::Human:
            Frame1 = &T.Human_1;
            Frame2 = &T.Human_2;
            DeathFrame1 = &T.Human_1_Death;
            DeathFrame2 = &T.Human_2_Death;
            break;
        case Species::Late_Dinosaur:
            Frame1 = &T.Late_Dinosaur_1;
            Frame2 = &T.Late_Dinosaur_2;
            DeathFrame1 = &T.Late_Dinosaur_1_Death;
            DeathFrame2 = &T.Late_Dinosaur_2_Death;
            break;
        case Species::Mold:
            Frame1 = &T.Mould_1;
            Frame2 = &T.Mould_2;
            DeathFrame1 = &T.Mould_1_Death;
            DeathFrame2 = &T.Mould_2_Death;
            break;
        case Species::Mushroom:
            Frame1 = &T.Mushroom_1;
            Frame2 = &T.Mushroom_2;
            DeathFrame1 = &T.Mushroom_1_Death;
            DeathFrame2 = &T.Mushroom_2_Death;
            break;
        case Species::Mycellium:
            Frame1 = &T.Mycellium_1;
            Frame2 = &T.Mycellium_2;
            DeathFrame1 = &T.Mycellium_1_Death;
            DeathFrame2 = &T.Mycellium_2_Death;
            break;
        case Species::Primate:
            Frame1 = &T.Primate_1;
            Frame2 = &T.Primate_2;
            DeathFrame1 = &T.Primate_1_Death;
            DeathFrame2 = &T.Primate_2_Death;
            break;
        case Species::Rat:
            Frame1 = &T.Rat_1;
            Frame2 = &T.Rat_2;
            DeathFrame1 = &T.Rat_1_Death;
            DeathFrame2 = &T.Rat_2_Death;
            break;
        case Species::Shark:
            Frame1 = &T.Shark_1;
            Frame2 = &T.Shark_2;
            DeathFrame1 = &T.Shark_1_Death;
            DeathFrame2 = &T.Shark_2_Death;
            break;
        case Species::Single_Cell:
            Frame1 = &T.Single_Cell_1;
            Frame2 = &T.Single_Cell_2;
            DeathFrame1 = &T.Single_Cell_1_Death;
            DeathFrame2 = &T.Single_Cell_2_Death;
            break;
        case Species::Snake:
            Frame1 = &T.Snake_1;
            Frame2 = &T.Snake_2;
            DeathFrame1 = &T.Snake_1_Death;
            DeathFrame2 = &T.Snake_2_Death;
            break;
        case Species::Tree:
            Frame1 = &T.Tree_1;
            Frame2 = &T.Tree_2;
            DeathFrame1 = &T.Tree_1_Death;
            DeathFrame2 = &T.Tree_2_Death;
            break;
        case Species::Weed:
            Frame1 = &T.Weed_1;
            Frame2 = &T.Weed_2;
            DeathFrame1 = &T.Weed_1_Death;
            DeathFrame2 = &T.Weed_2_Death;
            break;
    }
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
    PlaySound(T->Ping);
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
        Correct({static_cast<float>(Frame1->width), 0}).x,
        Correct({0,static_cast<float>(Frame1->height)}).y,
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
    //V = Correct(V); //also wrong, but keeping it here as a memorial
    //playerPos = Correct(playerPos); //WRONG just keeping it here as a memorial
    Rectangle PLAYER{
        playerPos.x - 50,
        playerPos.y - 45,
        V.x,
        V.y
    };
    Rectangle NPC{
        Pos.x,
        Pos.y,
        Correct({static_cast<float>(Frame1->width), 0}).x,
        Correct({0,static_cast<float>(Frame1->height)}).y,
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

    if (aggroed)
        Destination = {playerPos.x - 50, playerPos.y - 45};
    else if (Vector2Distance(Pos, Destination) < 5.0f){
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

    Vector2 toTarget = Vector2Subtract(Destination, Pos);
    float dist = Vector2Length(toTarget);

    Vector2 move;
    if (dist <= speed * 0.9f || dist < 0.001f) {
        // close enough — snap to it instead of overshooting
        move = toTarget;
    } else {
        move = Vector2Scale(Vector2Normalize(toTarget), speed * 0.9f);
    }
    Pos = Vector2Add(Pos, move);
    if (move.x < 0 && facingRight && MoveTimer == -1)
        facingRight = false;
    if (move.x > 0 && !facingRight && MoveTimer == -1)
        facingRight = true;
}
void Npc::CowardMove(){ //very fast, runs away, if you are far away enough it forgets
    if (hp <= 0)
        return;
    if (Vector2Distance(playerPos, Pos) > 250 && aggroed)
        aggroed = false;

    if (aggroed)
        Destination = {playerPos.x - 50, playerPos.y - 45};
    else if (Vector2Distance(Pos, Destination) < 5.0f){
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

    Vector2 toTarget = Vector2Subtract(Destination, Pos);
    float dist = Vector2Length(toTarget);

    Vector2 move;
    if (dist <= speed || dist < 0.001f) {
        // close enough — snap to it instead of overshooting
        move = toTarget;
    } else {
        move = Vector2Scale(Vector2Normalize(toTarget), speed);
    }
    Pos = Vector2Add(Pos, move);
    if (move.x < 0 && facingRight && MoveTimer == -1)
        facingRight = false;
    if (move.x > 0 && !facingRight && MoveTimer == -1)
        facingRight = true;
} 
void Npc::PackMove(){ //aggroes all other Npcs within a certain radius
    if (hp <= 0)
        return;
    if (Vector2Distance(playerPos, Pos) > 250 && aggroed)
        aggroed = false;

    if (aggroed){
        Destination = {playerPos.x - 50, playerPos.y - 45};
        for (Npc& i : *Npcs){
            if (&i == this)
                continue;
            if (Vector2Distance(i.getPos(), Pos) <= 200)
                i.Aggro();
        }
    }
    else if (Vector2Distance(Pos, Destination) < 5.0f){
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

    Vector2 toTarget = Vector2Subtract(Destination, Pos);
    float dist = Vector2Length(toTarget);

    Vector2 move;
    if (dist <= speed * 0.7f || dist < 0.001f) {
        // close enough — snap to it instead of overshooting
        move = toTarget;
    } else {
        move = Vector2Scale(Vector2Normalize(toTarget), speed * 0.7f);
    }
    Pos = Vector2Add(Pos, move);
    if (move.x < 0 && facingRight && MoveTimer == -1)
        facingRight = false;
    if (move.x > 0 && !facingRight && MoveTimer == -1)
        facingRight = true;


    
}
void Npc::TankMove(){ //slow, more hp
    if (hp <= 0)
        return;
    if (Vector2Distance(playerPos, Pos) > 250)
        aggroed = false;

    
    if (hp == max_hp){
        max_hp *= 2.0f;
        hp = max_hp;
        ++max_hp;
    }
    if (aggroed)
        Destination = {playerPos.x - 50, playerPos.y - 45};
    else if (Vector2Distance(Pos, Destination) < 5.0f){
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

    Vector2 toTarget = Vector2Subtract(Destination, Pos);
    float dist = Vector2Length(toTarget);

    Vector2 move;
    if (dist <= speed/2 || dist < 0.001f) {
        // close enough — snap to it instead of overshooting
        move = toTarget;
    } else {
        move = Vector2Scale(Vector2Normalize(toTarget), speed/2);
    }
    Pos = Vector2Add(Pos, move);
    if (move.x < 0 && facingRight && MoveTimer == -1)
        facingRight = false;
    if (move.x > 0 && !facingRight && MoveTimer == -1)
        facingRight = true;
}
void Npc::AmbushMove(){
    if (hp <= 0)
        return;
    if (Vector2Distance(playerPos, Pos) <= 50)
        aggroed = true;
    else if (Vector2Distance(playerPos, Pos) > 250)
        aggroed = false;

    
    if (aggroed)
        Destination = {playerPos.x - 50, playerPos.y - 45};
    else if (Vector2Distance(Pos, Destination) < 5.0f){
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

    Vector2 toTarget = Vector2Subtract(Destination, Pos);
    float dist = Vector2Length(toTarget);

    Vector2 move;
    if (dist <= speed * 0.7f || dist < 0.001f) {
        // close enough — snap to it instead of overshooting
        move = toTarget;
    } else {
        move = Vector2Scale(Vector2Normalize(toTarget), speed * 0.7f);
    }
    Pos = Vector2Add(Pos, move);

    if (move.x < 0 && facingRight && MoveTimer == -1)
        facingRight = false;
    if (move.x > 0 && !facingRight && MoveTimer == -1)
        facingRight = true;

}

float Npc::getDamage() const{
    return damage;
} 

AIType Npc::getAI() const{
    return AI;
}

Vector2 Npc::Correct(Vector2 V) const{

    float proportionW = Frame1->width / 100.0f;
    float proportionH = Frame1->height / 90.0f;

    float scale = proportionW > proportionH ? proportionW : proportionH;
    scale = 1.0f / scale;
    V = Vector2Scale(V, scale);

    return V;
}


Vector2 Npc::getPlayerPos() const{
    return playerPos;
}