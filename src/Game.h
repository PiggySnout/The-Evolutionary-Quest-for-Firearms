#pragma once
#include "raylib.h"
#include "ui.h"
#include "Player.h"
#include "Bullet.h"
#include "textures.h"
#include "Camera.h"
#include <vector>
#include <fstream>
#include "WeaponData.h"
#include "Npc.h"

#define mob_cap 10

class Game{
public:
    Game();
    bool Logic();
    void Draw_all();

    void NextLevel();

    void SpawnEnemies();

    std::vector<weaponStat> ReadStats();

    void LevelUp();

    void killNpcs();

    void killBullets();

    void manageButtons();


private:

    int level;
    int timer;
    int MedkitPrice;

    

    std::vector<weaponStat> WeaponStats;
    Textures T;
    ui u;
    Player p;
    std::vector<Bullet> Bullets;
    
    std::vector<Npc> Npcs;
    std::time_t last;
    Weapon w;

    

    jtodd::Camera C;

};