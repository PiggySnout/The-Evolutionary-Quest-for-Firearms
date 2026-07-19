#include "ui.hpp"
#include "WeaponData.hpp"
#include <raylib.h>
#include <memory>
#include<cassert>
#include <iostream>
ui::ui(Player& player, Weapon& weapon, std::vector<weaponStat>& VWS, Textures& textures, bool has_WeaponButton, bool has_EvolveButtons)  : T(textures.Left_Ui),
           T2(textures.Middle_Ui),
           T3(textures.Right_Ui),
           player(player),
           weapon(weapon),
           BarLength(GetScreenWidth()),
           BarProgressPercent(0.0f),
           BarTime(weapon.getReloadTime()),
           VWS(VWS),
           HealthBarLength(GetScreenWidth() * 0.75f),
           has_WeaponButton(has_WeaponButton),
           has_EvolveButtons(has_EvolveButtons),
           textures(textures)
{
}

void ui::Draw(){ //This means draw the box
    Vector2 pos { 0, GetScreenHeight() - 220.0f  };
    DrawTextureEx(T, pos, 0.0f, 10.0f, WHITE);
    for (float i = 50.0f  ; i < GetScreenWidth() - 50.0f  ; i += 10.0f ){
        pos = { i, GetScreenHeight() - 220.0f  };
        DrawTextureEx(T2, pos, 0.0f, 10.0f, WHITE);
    }
    pos = { GetScreenWidth() - 50.0f, GetScreenHeight() - 220.0f };
    DrawTextureEx(T3, pos, 0.0f, 10.0f, WHITE);
}
void ui::Input(){
    //nothing here yet
}
void ui::newButton(const char* text, bool goldCurrency){
    for (int i = 0 ; i < 4 ; ++i){
        if (buttons[i] == nullptr){
            Rectangle rec{
                (((GetScreenWidth()-100.0f) / 4.0f) * i) + 50,
                GetScreenHeight() - 140.0f,
                (GetScreenWidth()-100.0f) / 4.0f - 10.0f,
                100.0f
            };
            if (player.getNext().size() <= i)
                buttons[i] = std::make_unique<Button>(rec, text, goldCurrency, VWS, weapon.getak_number(), i == 0 && has_WeaponButton, has_EvolveButtons, nullptr);
            else
                buttons[i] = std::make_unique<Button>(rec, text, goldCurrency, VWS, weapon.getak_number(), i == 0 && has_WeaponButton, has_EvolveButtons, &SpeciesToTexture(player.getNext()[i]));
            break;
        }
    }
    
}

Button& ui::getButton(int i) const{
    assert(i >= 0);
    assert(i < buttons.size());
    assert(buttons[i] != nullptr);
    
    return *buttons[i];
}

void ui::DrawButtons() const{
    
    for (int i = 0 ; i < 4 ; ++i){
        if (buttons[i] == nullptr)
            continue;
        if (weapon.getak_number() != buttons[i]->getAk_number())
            if (weapon.getak_number() == buttons[i]->getAk_number() + 1)
                buttons[i]->LevelUp();
        Rectangle rec{
            (((GetScreenWidth()-100.0f) / 4.0f) * i) + 50,
            GetScreenHeight() - 170.0f,
            (GetScreenWidth()-100.0f) / 4.0f - 10.0f,
            100.0f
        };
        buttons[i]->setRec(rec);
        if (player.getNext().size() <= i)
            buttons[i]->setTexture(nullptr);
        else
            buttons[i]->setTexture(&SpeciesToTexture(player.getNext()[i]));
    }

    
}

void ui::deleteButton(int i){
    buttons[i] = nullptr;
}

bool ui::AdvanceBar(){

    BarLength = GetScreenWidth();
    BarTime = weapon.getReloadTime();
    if (BarProgressPercent < 100.0f && weapon.getType() == type::AK_47){
        BarProgressPercent = 100.0f;
        return false;
    }

    if (weapon.getType() == type::Rock || weapon.getType() == type::Sharp_Rock || weapon.getType() == type::Knife){
        
        if (BarProgressPercent < 100.0f){
            BarProgressPercent += (BarLength / static_cast<float>(BarTime)) / (BarLength / 100);
            if (IsbarFull())
                weapon.reload();
        }
        return false;
    }

    if ((weapon.getType() == type::SlingShot || weapon.getType() == type::Bow)){
        if (IsKeyDown(KEY_SPACE) && BarProgressPercent < 100.0f){
            BarProgressPercent += 100.0f / static_cast<float>(BarTime);
            if (IsbarFull())
                weapon.reload();
        }
        else if (IsKeyUp(KEY_SPACE)){
            ResetBar();
            if (weapon.hasAmmo())
                return true;
        }
        return false;
    }

    else if (weapon.getType() == type::Crossbow){
        if (IsKeyDown(KEY_SPACE) && BarProgressPercent < 100.0f){
            BarProgressPercent += (BarLength / static_cast<float>(BarTime)) / (BarLength / 100);
            if (IsbarFull())
                weapon.reload();
        }
        else if (IsKeyUp(KEY_SPACE) && !IsbarFull()){
            ResetBar();
        }
        return false;
    }
    return false;
}
void ui::DrawBar(){
    Rectangle rec{
        0.0f,
        GetScreenHeight() - 29.0f,
        BarLength/100 * BarProgressPercent,
        20.0f
    };
    DrawRectangle(0.0f, GetScreenHeight() - 29.0f, BarProgressPercent * BarLength/100, 20.0f, BarProgressPercent >= 100 ? GREEN : RED);
}
void ui::ResetBar(){
    BarProgressPercent = 0.0f;
}
void ui::SetBarTime(int time){
    BarTime = time;
}
bool ui::IsbarFull() const { 
    return BarProgressPercent >= 100.0f; 
}
void ui::EvalCursor(){
    for (int i = 0 ; i < 4 ; ++i){
        if (buttons[i] == nullptr)
            continue;
        if (buttons[i]->isHovered()){
            if (buttons[i]->isLocked())
                SetMouseCursor(MOUSE_CURSOR_NOT_ALLOWED);
            else
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        }
    }
}

void ui::PrintStats() const{
    DrawText(TextFormat("Weapon Level: %d", weapon.getak_number()), 10, 10, 20, LIGHTGRAY);
    DrawText(TextFormat("XP: %d", player.getXP()), 10, 40, 20, GREEN);
    DrawText(TextFormat("Gold: %d", player.getGold()), 10, 70, 20, GOLD); 
    DrawText(TextFormat("Passive Xp: %d", player.getPassiveXp()), 10, 100, 20, DARKGREEN);  
    DrawText(TextFormat("Passive Gold: %d", player.getPassiveGold()), 10, 130, 20, YELLOW);
    

}

bool ui::isNull(int i) const{
    if (buttons[i] == nullptr)
        return true;
    return false;
}

void ui::DrawHealth(){
    HealthBarLength = GetScreenWidth() * 0.70;
    const float x_BarPos = GetScreenWidth() / 8 + 70;

    DrawRectangle(x_BarPos, 10.0f, HealthBarLength, 30, RED);
    DrawRectangle(x_BarPos, 10.0f, player.getHealth()/player.getMaxHealth() * HealthBarLength, 30, GREEN);
    DrawText(TextFormat("Hp: %d", static_cast<int>(player.getHealth())), GetScreenWidth() / 2 - 10, 50, 20, RED);
}

Texture2D& ui::SpeciesToTexture(Species S) const{
    switch (S){
        case Species::Amphibian:
            return textures.Amphibian_1;
        case Species::Bird:
            return textures.Bird_1;
        case Species::Bush:
            return textures.Bush_1;
        case Species::Canine:
            return textures.Canine_1;
        case Species::Crocodile:
            return textures.Crocodile_1;
        case Species::Feline:
            return textures.Feline_1;
        case Species::Fungus:
            return textures.Fungus_1;
        case Species::Grass:
            return textures.Grass_1;
        case Species::Human:
            return textures.Human_1;
        case Species::Late_Dinosaur:
            return textures.Late_Dinosaur_1;
        case Species::Mold:
            return textures.Mould_1;
        case Species::Rat:
            return textures.Rat_1;
        case Species::Shark:
            return textures.Shark_1;
        case Species::Single_Cell:
            return textures.Single_Cell_1;
        case Species::Mushroom:
            return textures.Mushroom_1;
        case Species::Mycellium:
            return textures.Mycellium_1;
        case Species::Primate:
            return textures.Primate_1;
        case Species::Flower:
            return textures.Flower_1;
        case Species::Snake:
            return textures.Snake_1;
        case Species::Tree:
            return textures.Tree_1;
        case Species::Weed:
            return textures.Weed_1;
        case Species::Fish:
            return textures.Fish_1;
    }
    return textures.Single_Cell_2_Death; //default case, should never happen
}