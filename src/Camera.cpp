#include "Camera.hpp"
#include "Game.hpp"
#include "WeaponData.hpp"
#include <cmath>
namespace jtodd{
    Camera::Camera(Player& p, std::vector<Bullet>& Bullets, Textures& T, ui& u, ui& evoUi, Weapon& w, std::vector<weaponStat>& VWS, std::vector<Npc>& Npcs) : p(p),
                                                                                  Bullets(Bullets),
                                                                                  T(T),
                                                                                  Background(T.Background),
                                                                                  u(u),
                                                                                  w(w),
                                                                                  VWS(VWS),
                                                                                  Npcs(Npcs),
                                                                                  evoUi(evoUi)

    {
    }

    void Camera::Draw_All(){
        bool check = true;
        if (!p.getEvolving()){
            for (int i = 0 ; i < 4 ; ++i){
                if (!u.isNull(i)){
                    bool hovered = u.getButton(i).Update();
                    if(hovered && !u.getButton(i).isLocked()){
                        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                        check = false;
                    }
                    else if (hovered){
                        SetMouseCursor(MOUSE_CURSOR_NOT_ALLOWED);
                        check = false;
                    }

                }
            }
        }
        else{
            for (int i = 0 ; i < 4 ; ++i){
                if (!evoUi.isNull(i)){
                    bool hovered = evoUi.getButton(i).Update();
                    if(hovered && !evoUi.getButton(i).isLocked()){
                        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                        check = false;
                    }
                    else if (hovered){
                        SetMouseCursor(MOUSE_CURSOR_NOT_ALLOWED);
                        check = false;
                    }

                }
            }
    }
        if (check)
            SetMouseCursor(MOUSE_CURSOR_ARROW);

        

            BackgroundStuff();
            
            

            p.Draw(WorldToScreen(p.getPos()));
            
            for (Npc& i : Npcs)
                i.Draw(WorldToScreen(i.getPos()));

            for (Bullet& b : Bullets)
                b.Draw(WorldToScreen(b.getPos()), VWS[w.getak_number()-1].T == type::Knife || VWS[w.getak_number()-1].T == type::Bow || VWS[w.getak_number()-1].T == type::Crossbow);
            //everything else doesn't care abt player

            if (!p.getEvolving()) u.Draw();
            else evoUi.Draw();

            DrawRecPointingAtMouse();
            if (!p.getEvolving()){
                for (int i = 0 ; i< 4 ; ++i){
                    if (u.isNull(i))
                        continue;
                    u.getButton(i).Draw();
                }
            }
            else{
                for (int i = 0 ; i< 4 ; ++i){
                    if (evoUi.isNull(i))
                        continue;
                    evoUi.getButton(i).Draw();
                }
            }
            
            u.PrintStats();
            w.PrintAmmo();
            u.DrawBar();
            u.DrawHealth();
        
    }
    void Camera::BackgroundStuff(){

        ClearBackground(DARKGREEN);
        Vector2 v{0,0};
        float offsetX = std::fmod(p.getPos().x, 5000.0f);
        if (offsetX < 0)
            offsetX += 5000.0f;
        v.x -= offsetX;

        float offsetY = std::fmod(p.getPos().y, 5000.0f);
        if (offsetY < 0)
            offsetY += 5000.0f;
        v.y -= offsetY;

        v.x = GetScreenWidth() / 2.0f - 5000.0f - offsetX;
        v.y = GetScreenHeight() / 2.0f - 5000.0f - offsetY;

        float x = v.x;
        for (int i = 0 ; i < 3 ; ++i){
            v.x = x;
            for (int j = 0 ; j < 3 ; ++j){
                DrawTextureEx(Background, v, 0.0f, 25.0f, WHITE);
                v.x += 5000; 
            }
            v.y += 5000;
        }
        
    }
    Vector2 Camera::WorldToScreen(Vector2 V){
        const float cx = GetScreenWidth() / 2; //gets x coordinate of the centre of the screen, ie. where the player is Drawn.
        const float cy = GetScreenHeight() / 2; //same but for y

        V.x += cx;
        V.y += cy;

        V.x -= Pos.x;
        V.y -= Pos.y;
        return V;
    }

    void Camera::UpdateCameraPos(){
        Pos = p.getPos();
    }
    Vector2 Camera::ScreenToWorld(Vector2 V){
        V.x += Pos.x;
        V.y += Pos.y;

        V.x -= GetScreenWidth() / 2; 
        V.y -= GetScreenHeight() / 2;

        return V;
    }
    void Camera::DrawRecPointingAtMouse(){
        w.Draw(WorldToScreen(p.getPos()));
    }
}