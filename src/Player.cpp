#include "Player.hpp"

#include  <ctime>
#include <algorithm>
#include <iostream>
Player::Player(Textures& T, std::vector<EvoData>& EvoStats) :  
    EvoStats(EvoStats),
    S(EvoStats[0].species), 
    x(0),
    y(0),
    textureToUse(false),
    speed(EvoStats[0].speed),
    xp(0),
    gold(0),
    hp(42.5f),
    max_hp(42.5f),
    damageTimer(0),
    dead(false),
    facingRight(true),
    evo_level(0),
    T(T),
    texture1(nullptr),
    texture2(nullptr),
    texture1_death(nullptr),
    texture2_death(nullptr),
    passiveXp(EvoStats[0].passive_xp),
    passiveGold(EvoStats[0].passive_gold),
    Next({}),
    evolving(false)
{
    Evolve();
}


void Player::Draw(Vector2 pos) const{
    // pos is treated as the center of the 100x90 box
    Vector2 WH{
        (textureToUse ? static_cast<float>(texture1->width) : static_cast<float>(texture2->width)),
        (textureToUse ? static_cast<float>(texture1->height) : static_cast<float>(texture2->height))
    };
    Vector2 scaledWH = Correct(WH);

    Rectangle Src{
        facingRight ? 0 : textureToUse ? static_cast<float>(texture1->width) : static_cast<float>(texture2->width),
        0,
        facingRight ? textureToUse ? static_cast<float>(texture1->width) : static_cast<float>(texture2->width) :
            textureToUse ? static_cast<float>(-texture1->width) : static_cast<float>(-texture2->width),
        textureToUse ? static_cast<float>(texture1->height) : static_cast<float>(texture2->height)
    };

    // Box: 100 wide, 90 tall, centered horizontally on pos.x, bottom edge at pos.y + 45
    float boxBottom = pos.y + 45.0f;

    Rectangle Dest{
        pos.x - scaledWH.x / 2.0f,   // still centered horizontally
        boxBottom - scaledWH.y,      // bottom-aligned: top = bottom - actual height
        scaledWH.x,
        scaledWH.y
    };

    DrawTexturePro(textureToUse ? *texture1 : *texture2, Src, Dest, {0,0}, 0.0f, damageTimer > 0 ? RED : WHITE);
}
void Player::UpdateTexture(){
    textureToUse = !textureToUse;
    xp += passiveXp;
    gold += passiveGold;

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
    if (gold > 0)
        PlaySound(T.Gold);
    this->gold += gold;
}
void Player::giveXp(int xp){
    this->xp += xp;
}

Vector2 Player::getTextureDim(){
    Vector2 raw{
        (textureToUse ? static_cast<float>(texture1->width) : static_cast<float>(texture2->width)),
        (textureToUse ? static_cast<float>(texture1->height) : static_cast<float>(texture2->height))
    };
    return Correct(raw);
}


void Player::TakeDamage(float damage){
    if (damageTimer <= 0){
        hp -= damage;
        damageTimer = 30;
        PlaySound(T.Damage);
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
    if (hp > max_hp)
        hp = max_hp;
    
}

Vector2 Player::Correct(Vector2 V) const{

    float proportionW = (textureToUse ? texture1->width : texture2->width) / 100.0f;
    float proportionH = (textureToUse ? texture1->height : texture2->height) / 90.0f;

    float scale = proportionW > proportionH ? proportionW : proportionH;
    scale = 1.0f / scale;
    V = Vector2Scale(V, scale);

    return V;
}

bool Player::Evolve(){
    if (evo_level == 0){ //init
        evo_level = 1;
        texture1 = &T.Single_Cell_1;
        texture2 = &T.Single_Cell_2;
        texture1_death = &T.Single_Cell_1_Death;
        texture2_death = &T.Single_Cell_2_Death;
        Next = {Species::Fungus, Species::Weed, Species::Fish};
        return false;
    }
    if (S != findInEvoStats(S, evo_level).species){ //Species change (evo_level is the next level)
        if (Next.empty())
            return false;
        evolving = true;
        return true;
    }

    ++evo_level;
    
    const EvoData& E = findInEvoStats(S, evo_level - 1);
    max_hp = E.health;
    hp = E.health;
    speed = E.speed;
    passiveXp = E.passive_xp;
    passiveGold = E.passive_gold;
    return false;

}

void Player::Evolve(int choice){
    if (choice < 0 || choice >= Next.size()){
        std::cout << "ERROR: Invalid choice in Player::Evolve(int choice)\n";
        return;
    }
    S = Next[choice];
    evolving = false;
    setTextureFor(S);
    const EvoData& E = findInEvoStats(S, 0);
    evo_level = 1; 
    max_hp = E.health;
    hp = E.health;
    speed = E.speed;
    passiveXp = E.passive_xp;
    passiveGold = E.passive_gold;

    PlaySound(T.Evolve);
    return;
}

int Player::getPassiveGold() const{
    return passiveGold;
}
int Player::getPassiveXp() const{
    return passiveXp;
}

float Player::getMaxHealth() const{
    return max_hp;
}

const EvoData& Player::findInEvoStats(Species S, int i){
    const EvoData* ref;
    for (const EvoData& j : EvoStats){
        if(j.species == S){
            ref = &j;
            break;
        }
    }
    ref += i;
    return *ref;
}

bool Player::getEvolving() const{
    return evolving;
}

std::vector<Species> Player::getNext() const{
    return Next;
}

void Player::setTextureFor(Species S){
    switch (S){
        case Species::Amphibian:
            texture1 = &T.Amphibian_1;
            texture2 = &T.Amphibian_2;
            texture1_death = &T.Amphibian_1_Death;
            texture2_death = &T.Amphibian_2_Death;
            Next = {Species::Rat, Species::Crocodile};
            break;
        case Species::Bird:
            texture1 = &T.Bird_1;
            texture2 = &T.Bird_2;
            texture1_death = &T.Bird_1_Death;
            texture2_death = &T.Bird_2_Death;
            Next = {};
            break;
        case Species::Bush:
            texture1 = &T.Bush_1;
            texture2 = &T.Bush_2;
            texture1_death = &T.Bush_1_Death;
            texture2_death = &T.Bush_2_Death;
            Next = {Species::Tree};
            break;
        case Species::Canine:
            texture1 = &T.Canine_1;
            texture2 = &T.Canine_2;
            texture1_death = &T.Canine_1_Death;
            texture2_death = &T.Canine_2_Death;
            Next = {};
            break;
        case Species::Crocodile:
            texture1 = &T.Crocodile_1;
            texture2 = &T.Crocodile_2;
            texture1_death = &T.Crocodile_1_Death;
            texture2_death = &T.Crocodile_2_Death;
            Next = {Species::Snake, Species::Late_Dinosaur, Species::Bird}; //should bird go somewhere else? this might be confusing.
            break;
        case Species::Feline:
            texture1 = &T.Feline_1;
            texture2 = &T.Feline_2;
            texture1_death = &T.Feline_1_Death;
            texture2_death = &T.Feline_2_Death;
            Next = {};
            break;
        case Species::Fish:
            texture1 = &T.Fish_1;
            texture2 = &T.Fish_2;
            texture1_death = &T.Fish_1_Death;
            texture2_death = &T.Fish_2_Death;
            Next = {Species::Shark, Species::Amphibian};
            break;
        case Species::Flower:
            texture1 = &T.Flower_1;
            texture2 = &T.Flower_2;
            texture1_death = &T.Flower_1_Death;
            texture2_death = &T.Flower_2_Death;
            Next = {};
            break;
        case Species::Fungus:
            texture1 = &T.Fungus_1;
            texture2 = &T.Fungus_2;
            texture1_death = &T.Fungus_1_Death;
            texture2_death = &T.Fungus_2_Death;
            Next = {Species::Mushroom, Species::Mycellium, Species::Mold};
            break;
        case Species::Grass:
            texture1 = &T.Grass_1;
            texture2 = &T.Grass_2;
            texture1_death = &T.Grass_1_Death;
            texture2_death = &T.Grass_2_Death;
            Next = {};
            break;
        case Species::Human:
            texture1 = &T.Human_1;
            texture2 = &T.Human_2;
            texture1_death = &T.Human_1_Death;
            texture2_death = &T.Human_2_Death;
            Next = {};
            break;
        case Species::Late_Dinosaur:
            texture1 = &T.Late_Dinosaur_1;
            texture2 = &T.Late_Dinosaur_2;
            texture1_death = &T.Late_Dinosaur_1_Death;
            texture2_death = &T.Late_Dinosaur_2_Death;
            Next = {};
            break;
        case Species::Mold:
            texture1 = &T.Mould_1;
            texture2 = &T.Mould_2;
            texture1_death = &T.Mould_1_Death;
            texture2_death = &T.Mould_2_Death;
            Next = {};
            break;
        case Species::Mushroom:
            texture1 = &T.Mushroom_1;
            texture2 = &T.Mushroom_2;
            texture1_death = &T.Mushroom_1_Death;
            texture2_death = &T.Mushroom_2_Death;
            Next = {};
            break;
        case Species::Mycellium:
            texture1 = &T.Mycellium_1;
            texture2 = &T.Mycellium_2;
            texture1_death = &T.Mycellium_1_Death;
            texture2_death = &T.Mycellium_2_Death;
            Next = {};
            break;
        case Species::Primate:
            texture1 = &T.Primate_1;
            texture2 = &T.Primate_2;
            texture1_death = &T.Primate_1_Death;
            texture2_death = &T.Primate_2_Death;
            Next = {Species::Human};
            break;
        case Species::Rat:
            texture1 = &T.Rat_1;
            texture2 = &T.Rat_2;
            texture1_death = &T.Rat_1_Death;
            texture2_death = &T.Rat_2_Death;
            Next = {Species::Feline, Species::Canine, Species::Primate};
            break;
        case Species::Shark:
            texture1 = &T.Shark_1;
            texture2 = &T.Shark_2;
            texture1_death = &T.Shark_1_Death;
            texture2_death = &T.Shark_2_Death;
            Next = {};
                break;
        case Species::Single_Cell:
            texture1 = &T.Single_Cell_1;
            texture2 = &T.Single_Cell_2;
            texture1_death = &T.Single_Cell_1_Death;
            texture2_death = &T.Single_Cell_2_Death;
            Next = {Species::Fungus, Species::Weed, Species::Fish};
            break;
        case Species::Snake:
            texture1 = &T.Snake_1;
            texture2 = &T.Snake_2;
            texture1_death = &T.Snake_1_Death;
            texture2_death = &T.Snake_2_Death;
            Next = {};
            break;
        case Species::Tree:
            texture1 = &T.Tree_1;
            texture2 = &T.Tree_2;
            texture1_death = &T.Tree_1_Death;
            texture2_death = &T.Tree_2_Death;
            Next = {};
            break;
        case Species::Weed:
            texture1 = &T.Weed_1;
            texture2 = &T.Weed_2;
            texture1_death = &T.Weed_1_Death;
            texture2_death = &T.Weed_2_Death;
            Next = {Species::Bush, Species::Flower, Species::Grass};
            break;
    }
}

void Player::StopEvol(){
    evolving = false;
}

int Player::getEvo_Level() const{
    return evo_level;
}

Species Player::getSpecies() const{
    return S;
}