#pragma once
#include "raylib.h"
#include "ui.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "textures.hpp"
#include "Camera.hpp"
#include <vector>
#include <fstream>
#include "WeaponData.hpp"
#include "Npc.hpp"
#include "EvoData.hpp"

#define mob_cap 10

class Game{
public:
    Game();
    bool Logic();
    void Draw_all();

    void NextLevel();

    void SpawnEnemies();

    std::vector<weaponStat> ReadStats();
    std::vector<EvoData> ReadEvoData();

    void LevelUp();

    void killNpcs();

    void killBullets();

    void manageButtons();

    const char* SpeciesToString(Species S) const;

private:

    int level;
    int timer;
    int MedkitPrice;

    

    std::vector<weaponStat> WeaponStats;
    std::vector<EvoData> EvoStats;
    Textures T;
    Player p;
    Weapon w;
    ui u;
    ui evoUi;
    
    std::vector<Bullet> Bullets;
    
    std::vector<Npc> Npcs;
    std::time_t last;
    

    

    jtodd::Camera C;

};