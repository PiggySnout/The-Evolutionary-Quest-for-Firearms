#include "Player.h"

#include  <ctime>
#include <algorithm>
#include <iostream>
Player::Player(const Textures& T) :  
    S(Species::Single_Cell), 
    x(0),
    y(0),
    textureToUse(false),
    F(Family::Bacteria),
    speed(1.0f),
    xp(10),
    gold(0),
    hp(100.0f),
    damageTimer(0),
    dead(false),
    facingRight(true),
    evo_level(0),
    T(T)
{
    Evolve();
}


void Player::Draw(Vector2 pos) const{
    pos.x -= 45.0f;
    pos.y -= 50.0f;
    Rectangle Src{
        facingRight ? 0 : textureToUse ? static_cast<float>(texture1.width) : static_cast<float>(texture2.width),
        0,
        facingRight ? textureToUse ? static_cast<float>(texture1.width) : static_cast<float>(texture2.width) : 
            textureToUse ? static_cast<float>(-texture1.width) : static_cast<float>(-texture2.width),
        textureToUse ? static_cast<float>(texture1.height) : static_cast<float>(texture2.height)
    };
    Vector2 WH{
        (textureToUse ? static_cast<float>(texture1.width) : static_cast<float>(texture2.width)),
        (textureToUse ? static_cast<float>(texture1.height) : static_cast<float>(texture2.height))
    };
    Rectangle Dest{
        pos.x, 
        pos.y,
        Correct(WH).x,
        Correct(WH).y
    };

    DrawRectangleLines(
        pos.x,
        pos.y,
        Correct(WH).x,
        Correct(WH).y,
        GREEN
    );

    DrawTexturePro(textureToUse ? texture1 : texture2, Src, Dest, {0,0}, 0.0f, damageTimer > 0 ? RED : WHITE);
}
void Player::UpdateTexture(){
    textureToUse = !textureToUse;
}
bool Player::Input(){

    float dx = 0.0f;
    float dy = 0.0f;

    if (IsKeyDown(KEY_W)) dy -= speed;
    if (IsKeyDown(KEY_S)) dy += speed;
    if (IsKeyDown(KEY_A)) dx -= speed;
    if (IsKeyDown(KEY_D)) dx += speed;

    if (dx != 0.0f && dy != 0.0f)
    {
        dx *= 0.70710678f;
        dy *= 0.70710678f;
    }

    if (dx < 0 && facingRight)
        facingRight = false;
    if (dx > 0 && !facingRight)
        facingRight = true;

    x += dx;
    y += dy;

    if (damageTimer > 0)
        --damageTimer;
    if (IsKeyPressed(KEY_SPACE))
        return true;
    return false;
}

Vector2 Player::getPos() const{
    Vector2 v{x, y};
    return v;
}


int Player::getGold() const { 
    return gold;
}

int Player::getXP() const {
    return xp;
}
void Player::giveGold(int gold){
    this->gold += gold;
}
void Player::giveXp(int xp){
    this->xp += xp;
}

Vector2 Player::getTextureDim(){
    Vector2 One{
        static_cast<float>(texture1.width), 
        static_cast<float>(texture1.height)
    };
    Vector2 Two{
        static_cast<float>(texture2.width),
        static_cast<float>(texture2.height)
    };
    return textureToUse ? One : Two;
}


void Player::TakeDamage(float damage){
    if (damageTimer <= 0){
        hp -= damage;
        damageTimer = 30;
    }
}

float Player::getHealth() const{
    return hp;
}

bool Player::KillIfNec(){
    if (hp <= 0)
        dead = true;

    return dead;
}

bool Player::IsDead() const{
    return dead;
}

void Player::Heal(float a){
    hp += a;
    if (hp > 100.0f)
        hp = 100.0f;
    
}

Vector2 Player::Correct(Vector2 V) const{

    float proportionW = (textureToUse ? texture1.width : texture2.width) / 100.0f;
    float proportionH = (textureToUse ? texture1.height : texture2.height) / 90.0f;

    float scale = proportionW > proportionH ? proportionW : proportionH;
    scale = 1.0f / scale;
    V = Vector2Scale(V, scale);

    return V;
}

void Player::Evolve(){
    if (evo_level == 0){ //init
        evo_level = 1;
        texture1 = T.Single_Cell_1;
        texture2 = T.Single_Cell_2;
        texture1_death = T.Single_Cell_1_Death;
        texture2_death = T.Single_Cell_2_Death;
        return;
    }
    if (evo_level == 10){ //Species change
        evo_level = 1;
        //do loads of stuff like buttons for choosing next evolution and shit
        //I'll do the other stuff later but rn I'll do the texture settings
        switch (S){
            case Species::Amphibian:
                texture1 = T.Amphibian_1;
                texture2 = T.Amphibian_2;
                texture1_death = T.Amphibian_1_Death;
                texture2_death = T.Amphibian_2_Death;
                break;
            case Species::Bird:
                texture1 = T.Bird_1;
                texture2 = T.Bird_2;
                texture1_death = T.Bird_1_Death;
                texture2_death = T.Bird_2_Death;
                break;
            case Species::Bush:
                texture1 = T.Bush_1;
                texture2 = T.Bush_2;
                texture1_death = T.Bush_1_Death;
                texture2_death = T.Bush_2_Death;
                break;
            case Species::Canine:
                texture1 = T.Canine_1;
                texture2 = T.Canine_2;
                texture1_death = T.Canine_1_Death;
                texture2_death = T.Canine_2_Death;
                break;
            case Species::Crocodile:
                texture1 = T.Crocodile_1;
                texture2 = T.Crocodile_2;
                texture1_death = T.Crocodile_1_Death;
                texture2_death = T.Crocodile_2_Death;
                break;
            case Species::Feline:
                texture1 = T.Feline_1;
                texture2 = T.Feline_2;
                texture1_death = T.Feline_1_Death;
                texture2_death = T.Feline_2_Death;
                break;
            case Species::Fish
                texture1 = T.Fish_1;
                texture2 = T.Fish_2;
                texture1_death = T.Fish_1_Death;
                texture2_death = T.Fish_2_Death;
                break;
            case Species::
                texture1 = T.Amphibian_1;
                texture2 = T.Amphibian_2;
                texture1_death = T.Amphibian_1_Death;
                texture2_death = T.Amphibian_2_Death;
                break;
            case Species::Amphibian:
                texture1 = T.Amphibian_1;
                texture2 = T.Amphibian_2;
                texture1_death = T.Amphibian_1_Death;
                texture2_death = T.Amphibian_2_Death;
                break;
            case Species::Amphibian:
                texture1 = T.Amphibian_1;
                texture2 = T.Amphibian_2;
                texture1_death = T.Amphibian_1_Death;
                texture2_death = T.Amphibian_2_Death;
                break;
            case Species::Amphibian:
                texture1 = T.Amphibian_1;
                texture2 = T.Amphibian_2;
                texture1_death = T.Amphibian_1_Death;
                texture2_death = T.Amphibian_2_Death;
                break;
            case Species::Amphibian:
                texture1 = T.Amphibian_1;
                texture2 = T.Amphibian_2;
                texture1_death = T.Amphibian_1_Death;
                texture2_death = T.Amphibian_2_Death;
                break;
            
        }
        return;
    }

    ++evo_level;

}
