#pragma once
#include "raylib.h"
#include "textures.hpp"
#include <vector>
#include <algorithm>
#include "Player.hpp"
#include "Bullet.hpp"
#include "ui.hpp"
#include "Npc.hpp"
namespace jtodd{
    class Camera{
    public:

        Camera(Player& p, std::vector<Bullet>& Bullets, Textures& T, ui& u, ui& evoUi, Weapon& w,  std::vector<weaponStat>& VWS, std::vector<Npc>& Npcs);
        void Draw_All();
        void UpdateCameraPos();
        Vector2 WorldToScreen(Vector2 V);
        Vector2 ScreenToWorld(Vector2 V);

    private:

        
        Player& p;
        ui& u;
        ui& evoUi;
        Weapon& w;
        std::vector<Bullet>& Bullets;
        Texture2D& Background;
        Textures& T;
        void BackgroundStuff();
        void DrawRecPointingAtMouse();
        Vector2 Pos; //WTF IS POS WHAT DOES IT DO????? oH iTs ThE pLaYeR pOsItIoN oF cOuRsE wE nEeD tHaT WTF
        std::vector<weaponStat>& VWS;
        std::vector<Npc>& Npcs;

    };
    
}