#pragma once
#include <raylib.h>
#include <string>
#include "WeaponData.hpp"
#include <vector>
class Button{

public:
    Button(Rectangle rec, std::string text, bool goldCurrency, std::vector<weaponStat>& VWS, int ak_number, bool isWeaponButton, bool has_EvolveButtons, Texture2D* T = nullptr);
    bool Update();
    bool Input();
    void Draw();
    void setRec(Rectangle rec);
    void ToggleLock();
    bool isLocked() const;
    bool isHovered() const;

    int getPrice() const;
    void setPrice(int Price);
    void setText(std::string text);

    void LevelUp();

    int getAk_number();

    void setTexture(Texture2D* a);

    Vector2 Correct(Vector2 V) const;

private:
    std::string text; //cannot be const, we wanna change it
    Rectangle rec;

    bool hovered;
    bool locked;
    bool isWeaponButton;

    int Price;

    const bool goldCurrency;
    const bool has_EvolveButtons;

    std::vector<weaponStat>& VWS;

    int ak_number;
    Texture2D* T;
    
};