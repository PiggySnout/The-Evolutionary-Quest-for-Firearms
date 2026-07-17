#pragma once
#include "raylib.h"
#include "textures.h"
#include "Npc.h"
#include <vector>
class Bullet{

public:

    Bullet();
    Bullet(int damage, int LifeTime, Vector2 pos, Vector2 Velocity, Texture2D* T, float angle);
    void Update_Pos();
    void Draw(Vector2 POS, bool special_angle);
    
    bool CheckCollisions(std::vector<Npc>& Npcs);

    Vector2 getPos();


private:

    int damage;
    int Lifetime;
    Vector2 pos;
    Vector2 Velocity;
    Texture2D* texture;
    float angle;
};