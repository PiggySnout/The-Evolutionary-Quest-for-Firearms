#pragma once
#include <raylib.h>
#include <string>
#include "WeaponData.hpp"
#include <vector>
class Button{

public:
    Button(Rectangle rec, std::string text, bool goldCurrency, std::vector<weaponStat>& VWS, int ak_number, bool isWeaponButton);
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

private:
    std::string text; //cannot be const, we wanna change it
    Rectangle rec;

    bool hovered;
    bool locked;
    bool WasClicked;
    bool isWeaponButton;

    int Price;

    bool goldCurrency;

    std::vector<weaponStat>& VWS;

    int ak_number;
    
};