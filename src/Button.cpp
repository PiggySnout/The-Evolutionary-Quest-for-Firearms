#include "Button.hpp"
#include <raylib.h>
#include <format>
Button::Button(Rectangle rec, std::string text, bool goldCurrency, std::vector<weaponStat>& VWS, int ak_number, bool isWeaponButton) : rec(rec),
                                                  text(text),
                                                  hovered(false),
                                                  locked(false),
                                                  WasClicked(false),
                                                  Price(0),
                                                  goldCurrency(goldCurrency),
                                                  VWS(VWS),
                                                  ak_number(ak_number),
                                                  isWeaponButton(isWeaponButton)

{                               
}
bool Button::Update(){
    hovered = CheckCollisionPointRec(GetMousePosition(), rec);
    return hovered;
}
bool Button::Input(){
    if (hovered && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !locked && !WasClicked){
        WasClicked = true;
        return true;
    }
    if (IsMouseButtonUp(MOUSE_BUTTON_LEFT))
        WasClicked = false;
    return false;
}
void Button::ToggleLock(){
    locked = !locked;
}
void Button::Draw(){
    
    DrawRectangleRounded(rec, 0.0f, 10, hovered ? DARKBLUE : SKYBLUE);
    if (locked)
        DrawRectangleRounded(rec, 0.0f, 10, GRAY);
    DrawText(text.c_str(), rec.x, rec.y + rec.height , 20, WHITE);

    std::string PriceStr = std::format("  {}\n  {}", Price, (goldCurrency ? "Gold" : "Xp"));

    DrawText(PriceStr.c_str(), rec.x, rec.y + rec.height/2 - 20 , 20, goldCurrency ? GOLD : GREEN);

    if (!isWeaponButton)
        return;

    //damage
    if (VWS[ak_number].damage != VWS[ak_number-1].damage){
        PriceStr = std::format("{}{} DMG", (VWS[ak_number].damage == VWS[ak_number-1].damage) ? " " : (VWS[ak_number].damage > VWS[ak_number-1].damage) ? "+" : "" ,VWS[ak_number].damage - VWS[ak_number-1].damage);
        DrawText(PriceStr.c_str(), rec.x + rec.width - 114.0f, rec.y + 10 , 20, 
        (VWS[ak_number].damage > VWS[ak_number-1].damage) ? GREEN : RED);
    }

    //speed
    if (VWS[ak_number].speed != VWS[ak_number-1].speed){
        PriceStr = std::format("{}{:.0f} SPD", (VWS[ak_number].speed == VWS[ak_number-1].speed) ? " " : (VWS[ak_number].speed > VWS[ak_number-1].speed) ? "+" : "" , (VWS[ak_number].speed - VWS[ak_number-1].speed) * 20);
        DrawText(PriceStr.c_str(), rec.x + rec.width - 114.0f, rec.y + 30 , 20, 
        (VWS[ak_number].speed > VWS[ak_number-1].speed) ? GREEN : RED);
    }
    //range
    if (VWS[ak_number].range != VWS[ak_number-1].range){
        PriceStr = std::format("{}{} DIST", (VWS[ak_number].range == VWS[ak_number-1].range) ? " " : (VWS[ak_number].range > VWS[ak_number-1].range) ? "+" : "" ,VWS[ak_number].range - VWS[ak_number-1].range);
        DrawText(PriceStr.c_str(), rec.x + rec.width - 114.0f, rec.y + 50 , 20, 
        (VWS[ak_number].range > VWS[ak_number-1].range) ? GREEN : RED);
    }
    //reload time
    if (VWS[ak_number].rechargeTime != VWS[ak_number-1].rechargeTime){
        PriceStr = std::format("{}{:.2f}s RLD", (VWS[ak_number].rechargeTime == VWS[ak_number-1].rechargeTime) ? " " : (VWS[ak_number].rechargeTime > VWS[ak_number-1].rechargeTime) ? "+" : "" ,(VWS[ak_number].rechargeTime - VWS[ak_number-1].rechargeTime) / 60.0f);
        DrawText(PriceStr.c_str(), rec.x + rec.width - 114.0f, rec.y + 70 , 20, 
        (VWS[ak_number].rechargeTime > VWS[ak_number-1].rechargeTime) ? RED : GREEN);
    }

}
void Button::setRec(Rectangle rec){
    this->rec = rec;
}
bool Button::isLocked() const { 
    return locked; 
}
bool Button::isHovered() const { 
    return hovered; 
}

int Button::getPrice() const {
    return Price;
}
void Button::setPrice(int Price){
    this->Price = Price;
}
void Button::setText(std::string text) {
    this->text = text;
}
void Button::LevelUp() {
    ++ak_number;
}

int Button::getAk_number() {
    return ak_number;
}