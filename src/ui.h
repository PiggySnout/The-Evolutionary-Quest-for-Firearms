#pragma once
#include <raylib.h>
#include "Button.h"
#include <array>
#include <memory>
#include "Player.h"
#include "Weapon.h"
class ui{
public:

    ui(Player& player, Weapon& weapon, std::vector<weaponStat>& VWS);
    ~ui();
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

    
    
private:

    Texture2D T;
    Texture2D T2;
    Texture2D T3;

    std::array<std::unique_ptr<Button>, 4> buttons;

    Player& player;
    Weapon& weapon;

    float BarProgressPercent;
    float BarLength;
    int BarTime;

    float HealthBarLength;

    std::vector<weaponStat>& VWS;
};