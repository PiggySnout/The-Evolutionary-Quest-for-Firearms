#include "Weapon.hpp"
#include "WeaponData.hpp"
#include <iostream>
#include <string>
#include <format>
Weapon::Weapon(Textures& T, std::vector<weaponStat>& VWS) : ak_number(1), 
                              texture(&T.Rock),
                              bulletTexture(&T.Rock),
                              T(T),
                              isLoaded(false),
                              ammo(0),
                              maxammo(1),
                              VWS(VWS),
                              damage(VWS[0].damage),
                              speed(VWS[0].speed),
                              range(VWS[0].range),
                              rechargeTime(VWS[0].rechargeTime),
                              price(VWS[0].price),
                              Type(VWS[0].T)
{
}

void Weapon::LevelUp(){
    std::cout << "Level " << ak_number
          << " type = " << static_cast<int>(VWS[ak_number-1].T)
          << '\n';
    if (ak_number != 47)
        ++ak_number;
    else
        return;


    if (VWS[ak_number-1].T == type::AK_47){
        texture = &T.AK_47;
        bulletTexture = &T.Bullet;
        maxammo = 500;
        ammo = 500;
    }
    else if (VWS[ak_number-1].T == type::Crossbow){
        texture = &T.Crossbow;
        bulletTexture = &T.Arrow;
        ammo = 0;
    }
    else if (VWS[ak_number-1].T == type::Bow){
        texture = &T.Bow;
        bulletTexture = &T.Arrow;
        maxammo = 1;
        ammo = 0;
    }
    else if (VWS[ak_number-1].T == type::Knife){
        texture = &T.Knife;
        bulletTexture = &T.Knife;
        maxammo = 3;
        ammo = 0;
    }
    else if (VWS[ak_number-1].T == type::SlingShot){
        texture = &T.SlingShot;
        bulletTexture = &T.Rock;
        ammo = 0;
    }
    else if (VWS[ak_number-1].T == type::Sharp_Rock){
        texture = &T.Sharp_Rock;
        bulletTexture = &T.Sharp_Rock;
        ammo = 0;
    }
    else{
        texture = &T.Rock;
        bulletTexture = &T.Rock;
        ammo = 0;
    }
    damage = VWS[ak_number-1].damage;
    speed = VWS[ak_number-1].speed;
    range = VWS[ak_number-1].range;
    rechargeTime = VWS[ak_number-1].rechargeTime;
    price = VWS[ak_number-1].price;
    Type = VWS[ak_number-1].T;
}
float Weapon::getAngle(Vector2 v1, Vector2 v2) const{
    Vector2 direction = Vector2Subtract(v2, v1);
    direction = Vector2Normalize(direction);
    float angle = atan2f(direction.y, direction.x) * RAD2DEG;
    return angle;
}
void Weapon::Draw(Vector2 pos) const{
    
    Vector2 Ppos = pos;
    Vector2 mousePos = GetMousePosition();
    if (ak_number != 47){
        pos.x += 23.0f + texture->width * 5.0f; // (/2*10)
        pos.y -= texture->height * 5.0f;
        //playerPos now is the pos of the centre of the weapon.
    }
    else {
        pos.x += 60;
        pos.y -= 44;
    }
    float angle = getAngle(pos, mousePos);

    
    Vector2 Origin {
        0.0f,
        15.0f
    };

    DrawRectanglePro({pos.x, pos.y, 100.0f, 30.0f}, Origin, angle, Fade(RED, 0.5f));
    float scale = 10.0f;
    float rot = 0.0f;
    switch (VWS[ak_number-1].T){
        case type::Rock:
            Ppos.x += 23.0f;
            Ppos.y -= 50.0f;
            break;
        case type::Sharp_Rock:
            Ppos.x += 13.0f;
            Ppos.y -= 60.0f;
            break;
        case type::SlingShot:
            Ppos.x += 23.0f;
            Ppos.y -= 100.0f;
            break;
            
        case type::Knife:
            Ppos.x += 43.0f;
            Ppos.y -= 70.0f;
            scale = 8.0f;
            break;
        case type::Bow:
            Ppos.x += 23.0f;
            Ppos.y -= 100.0f;
            break;
        case type::Crossbow:
            scale = 8.0f;
            Ppos.x += 20.0f;
            Ppos.y -= 103.0f;
            break;

        default:
            scale = 0.2f;
            rot = 315.0f;
            break;
    }

    DrawTextureEx(*texture, Ppos, rot, scale, WHITE);
    
}

Texture2D* Weapon::getTexture() const { 
    return texture; 
}
bool Weapon::SpawnBullet(Vector2 playerPos, Vector2 mousePos, std::vector<Bullet>& Bullets){
    if (ak_number != 47){
        playerPos.x += 23.0f + texture->width * 5.0f; // (/2*10)
        playerPos.y -= texture->height * 5.0f;
    }
    else{
        playerPos.x += 60;
        playerPos.y -= 44;
    }

    Vector2 direction = Vector2Subtract(mousePos, playerPos);
    direction = Vector2Normalize(direction);


    float angle = 0.0f;
    Vector2 velocity = Vector2Scale(direction, speed);
    if (VWS[ak_number-1].T == type::Bow || VWS[ak_number-1].T == type::Crossbow || VWS[ak_number-1].T == type::Knife)
        angle = atan2f(direction.y, direction.x) * RAD2DEG + 45.0f;

    Bullet b(damage, range, playerPos, velocity, bulletTexture, angle); ///keep fixing this stuff
    Bullets.push_back(b);
    if (--ammo == 0){
        isLoaded = false;
        return false;
    }
    return true;
    
}
int Weapon::getak_number() const { 
    return ak_number; 
}
void Weapon::PrintAmmo() const{
    DrawText(TextFormat("Ammo: %d", ammo), GetScreenWidth() - 75.0f, 10, 20, LIGHTGRAY);

    std::string PriceStr = std::format("{} DMG", damage);
    DrawText(PriceStr.c_str(), GetScreenWidth() - 70.0f, 30 , 20, RED);

    PriceStr = std::format("{:.0f} SPD", speed * 20);
    DrawText(PriceStr.c_str(), GetScreenWidth() - 80.0f, 50 , 20, DARKBLUE);

    PriceStr = std::format("{} DIST", range);
    DrawText(PriceStr.c_str(), GetScreenWidth() - 90.0f, 70 , 20, GREEN);

    PriceStr = std::format("{:.2f} RLD", static_cast<float>(rechargeTime) / 60.0f);
    DrawText(PriceStr.c_str(), GetScreenWidth() - 90.0f, 90 , 20, ORANGE);

}
bool Weapon::hasAmmo() const{
    return ammo > 0;
}
void Weapon::reload(){
    ammo = maxammo;
}

int Weapon::getReloadTime() const{
    return rechargeTime;
}

int Weapon::getPrice() const{
    return price;
}

type Weapon::getType() const{
    return Type;
}