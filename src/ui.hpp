#pragma once
#include <raylib.h>
#include "Button.hpp"
#include <array>
#include <memory>
#include "Player.hpp"
#include "Weapon.hpp"
class ui{
public:

    ui(Player& player, Weapon& weapon, std::vector<weaponStat>& VWS, Textures& textures, bool has_WeaponButton, bool has_EvolveButtons);
    void Draw();
    void Input();
    void newButton(const char* text, bool goldCurrency);
    void EvalCursor();
    void deleteButton(int i);

    bool AdvanceBar();
    void DrawBar();
    void ResetBar();
    void SetBarTime(int time);
    bool IsbarFull() const;
    Button& getButton(int i) const;

    void DrawButtons() const;

    void PrintStats() const;

    bool isNull(int i) const;

    void DrawHealth();

    Texture2D& SpeciesToTexture(Species S) const;

    
    
private:

    Textures& textures;

    Texture2D T;
    Texture2D T2;
    Texture2D T3;

    Sound click;

    std::array<std::unique_ptr<Button>, 4> buttons;

    Player& player;
    Weapon& weapon;

    float BarProgressPercent;
    float BarLength;
    int BarTime;

    float HealthBarLength;

    std::vector<weaponStat>& VWS;

    const bool has_WeaponButton;
    const bool has_EvolveButtons;
};