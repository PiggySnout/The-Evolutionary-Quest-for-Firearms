#include "Game.hpp"
#include "raymath.h"
#include <iostream>
#include <format>
#include <algorithm>
#include "Species.hpp"
Game::Game() : level(0),
               last(std::time(nullptr)),
               p(T, EvoStats),
               w(T, WeaponStats),
               C(p, Bullets, T, u, evoUi, w, WeaponStats, Npcs),
               u(p, w, WeaponStats, T, true, false),
               WeaponStats(ReadStats()),
               EvoStats(ReadEvoData()),
               timer(-1),
               MedkitPrice(10),
               evoUi(p, w, WeaponStats, T, false, true)
               
               
{
    u.newButton("Weapon_Button", true);
    u.newButton("Evolve", false);
    u.newButton("Medkit +10hp", true);

    evoUi.newButton("Evo_choice_1", false);
    evoUi.newButton("Evo_choice_2", false);
    evoUi.newButton("Evo_choice_3", false);


    u.SetBarTime(300);
}

bool Game::Logic(){
    if (!p.IsDead())
        if (p.KillIfNec())
            timer = 300;
    if (p.IsDead()){
        if (timer-- > 0){
            DrawRectangle(0,0, GetScreenWidth(), GetScreenHeight(), Fade(RED, 0.6f));
            DrawText("You Died!", GetScreenWidth()/2 - 20, GetScreenHeight()/2 - 150, 40, WHITE);
        }
        else{
            CloseWindow();
            return true;
        }
        return false;
    }
    if (p.Input() && u.IsbarFull() && w.hasAmmo() || u.AdvanceBar())
        w.SpawnBullet(p.getPos(), C.ScreenToWorld(GetMousePosition()), Bullets);
    
    if (u.IsbarFull() && !w.hasAmmo())
        u.ResetBar();
    
    if (!p.getEvolving()){
        u.DrawButtons();
    }
    else
        evoUi.DrawButtons();
    std::time_t now = std::time(nullptr);
    if (now - last >= 1){
        p.UpdateTexture();
        last = std::time(nullptr);
    }
    for (Npc& i : Npcs)
        i.ChangeTexture();
    Vector2 TruePos{
        p.getPos().x, //+ p.getTextureDim().x / 2
        p.getPos().y //+ p.getTextureDim().y / 2
    };
    for (Npc& i : Npcs){
        i.UpdatePlayerPos(TruePos);
        i.UpdatePlayerSize(p.getTextureDim());
        if (i.CheckPlayerCollision()){
            p.TakeDamage(i.getDamage() * (i.getAI() == AIType::Ambush ? 1.5f : 1.0f));
        }
        i.Move();
        
    }
    

    killBullets();

    killNpcs();

    manageButtons();

    u.EvalCursor();
    
    if (IsKeyDown(KEY_P) && IsKeyDown(KEY_I) && IsKeyPressed(KEY_G))
        LevelUp();
    
    SpawnEnemies();
    
    return false;
}
void Game::Draw_all(){
    C.UpdateCameraPos();
    
    C.Draw_All();
}
void Game::NextLevel(){

}

void Game::SpawnEnemies(){
    const float WORLD_WIDTH  = 138 * 20.0f;
    const float WORLD_HEIGHT = 138 * 20.0f;

    const float HALF_PLAYER_W = 9.0f / 2.0f;
    const float HALF_PLAYER_H = 10.0f / 2.0f;

    const float minX = -(WORLD_WIDTH/2 - HALF_PLAYER_W);
    const float maxX =  WORLD_WIDTH/2 - HALF_PLAYER_W;

    const float minY = -(WORLD_HEIGHT/2 - HALF_PLAYER_H);
    const float maxY =  WORLD_HEIGHT/2 - HALF_PLAYER_H;

    Vector2 NpcPos;

    while (Npcs.size() < mob_cap){
        NpcPos.x = GetRandomValue( p.getPos().x + minX, p.getPos().x + maxX );
        NpcPos.y = GetRandomValue( p.getPos().y + minY, p.getPos().y + maxY);

        if (Vector2Distance(NpcPos, p.getPos()) < 250)
            continue;

        AIType A = static_cast<AIType>(GetRandomValue(0, 4));

        Npc N(T, Species::Single_Cell, NpcPos, 5, 10, 5, 0.9f, 1.0f, A, &Npcs);
        Npcs.push_back(N);
    }
}

std::vector<weaponStat> Game::ReadStats(){
    std::vector<weaponStat> V{};
    std::ifstream FILE(ASSETS_PATH"WeaponStats.txt");
    if (!FILE){
        std::cout << "ERROR: Failed to open WeaponStats.txt\n";
        return V;
    }   
    std::string Type;
    int damage, range, rechargeTime, price;
    float speed;
    while (FILE>>Type>>damage>>speed>>range>>rechargeTime>>price){
        type T;
        switch (Type.length()){
            case 4:
                T = type::Rock;
                break;
            case 10:
                T = type::Sharp_Rock;
                break;
            case 9:
                T = type::SlingShot;
                break;
            case 5:
                T = type::Knife;
                break;
            case 3:
                T = type::Bow;
                break;
            case 8:
                T = type::Crossbow;
                break;
            case 6:
                T = type::AK_47;
                break;
        }
        weaponStat WS(T, damage, speed, range, rechargeTime, price);
        V.push_back(WS);
    }
    std::cout << "Read " << V.size() << " weapon stats\n";
    return V;
}

void Game::LevelUp(){
    w.LevelUp();
}

void Game::killNpcs(){
    std::vector<int> npcsToKill;
    std::vector<int> npcsToDespawn;
    for (int i = 0 ; i < Npcs.size() ; ++i){
        Npcs[i].Update();
        if (Npcs[i].shouldDie())
            npcsToKill.push_back(i);
        else if (Npcs[i].shouldDespawn())
            npcsToDespawn.push_back(i);
    }
    std::sort(npcsToKill.rbegin(), npcsToKill.rend());
    for (int i : npcsToKill){
        p.giveGold(Npcs[i].getGoldDrops());
        p.giveXp(Npcs[i].getXpDrops());
        std::swap(Npcs[i], Npcs[Npcs.size()-1]);
        Npcs.pop_back();
    }
    std::sort(npcsToDespawn.rbegin(), npcsToDespawn.rend());
    for (int i : npcsToDespawn){
        std::cout
    << "Player: (" << p.getPos().x << ", " << p.getPos().y << ")\n"
    << "NPC:    (" << Npcs[i].getPos().x << ", " << Npcs[i].getPos().y << ")\n"
    << "Dist:   "
    << Vector2Distance(p.getPos(), Npcs[i].getPos())
    << '\n';
        std::swap(Npcs[i], Npcs[Npcs.size()-1]);
        Npcs.pop_back();
    }
}

void Game::killBullets(){
    std::vector<int> bulletsToDelete;
    for (int i = 0 ; i < Bullets.size() ; ++i){
        Bullets[i].Update_Pos();
        if (Bullets[i].CheckCollisions(Npcs))
            bulletsToDelete.push_back(i);
    }
    for (int i : bulletsToDelete){
        std::swap(Bullets[i], Bullets[Bullets.size()-1]);
        Bullets.pop_back();
    }
}

void Game::manageButtons(){
    std::cout << u.isNull(0) << u.isNull(1) << u.isNull(2) << '\n';
    if (!p.getEvolving()){
        if (w.getak_number() == 47)
            u.deleteButton(0);

        //Weapon Upgrade Button
        if (!u.isNull(0)){
            u.getButton(0).setText(std::format("UNLOCK LVL {}", w.getak_number()+1));
            u.getButton(0).setPrice(WeaponStats[w.getak_number()].price); //don't use -1 because we want the next weapon's price
            if (u.getButton(0).isLocked()){
                if (u.getButton(0).getPrice() <= p.getGold())
                    u.getButton(0).ToggleLock(); //unlock if the player has enough gold
            }
            else if (u.getButton(0).getPrice() > p.getGold())
                u.getButton(0).ToggleLock(); //this should lock it if the player doesn't have enough gold
            if (u.getButton(0).Input()){
                w.LevelUp();
                p.giveGold(-(u.getButton(0).getPrice()));
            }
        }
        //Evolve Button
        if (u.isNull(1))
            return;
        
        u.getButton(1).setPrice(10); //EvoPrice
        u.getButton(1).setText("Evolve");


        if (u.getButton(1).isLocked()){
            if (u.getButton(1).getPrice() <= p.getXP())
                u.getButton(1).ToggleLock();
        }
        else if (u.getButton(1).getPrice() > p.getXP())
            u.getButton(1).ToggleLock();

        if (u.getButton(1).Input()){
            p.giveXp(-(u.getButton(1).getPrice()));
            p.Evolve();
        }
        //Medkit Button
        if (u.isNull(2))
            return;
        
        u.getButton(2).setPrice(MedkitPrice);
        u.getButton(2).setText("GET MEDKIT (+15hp)");


        if (u.getButton(2).isLocked()){
            if (u.getButton(2).getPrice() <= p.getGold())
                u.getButton(2).ToggleLock();
        }
        else if (u.getButton(2).getPrice() > p.getGold()){
            u.getButton(2).ToggleLock();

            if (u.getButton(2).Input()&& p.getHealth() < 100.0f){
                MedkitPrice += 10;
                p.giveGold(-(u.getButton(2).getPrice()));
                p.Heal(15);
            }
        }
    }
    else if (p.getEvolving()){ //I use the if cuz it might just have switched and I don't wanna do both. I have no idea if that actually changes anything, but I don't wanna find out. I just reaslised it changes nothing lol. Still leaving it cuz it changes nothing.
        
        for(int i = 0 ; i < p.getNext().size() ; ++i){ //Ok, this is gonna be intense, just focus Joseph, focus.
            if (evoUi.isNull(i))
                continue;
            evoUi.getButton(i).setText(std::format("Evolve into {}", SpeciesToString(p.getNext()[i])));

            if (evoUi.getButton(i).Input()){
                p.Evolve(i);
                if (p.getNext().empty()){
                    for (int j = 0 ; j < 3 ; ++j)
                        evoUi.deleteButton(j);
                    u.deleteButton(1);
                    p.StopEvol();
                }
                break;
            }

            evoUi.getButton(i).setPrice(0);
        }
    }
}

std::vector<EvoData> Game::ReadEvoData(){
    std::vector<EvoData> V{};
    std::ifstream FILE(ASSETS_PATH"EvolutionStats.txt");
    if (!FILE){
        std::cout << "ERROR: Failed to open EvolutionStats.txt\n";
        return V;
    }   
    std::string Str;
    
    Species S;
    
    float speed, health;
    unsigned int passive_xp, passive_gold;
    while (FILE>>Str>>speed>>health>>passive_xp>>passive_gold){
        if (Str == "Amphibian")
            S = Species::Amphibian;
        else if (Str == "Bird")
            S = Species::Bird;
        else if (Str == "Bush")
            S = Species::Bush;
        else if (Str == "Canine")
            S = Species::Canine;
        else if (Str == "Crocodile")
            S = Species::Crocodile;
        else if (Str == "Feline")
            S = Species::Feline;
        else if (Str == "Fungus")
            S = Species::Fungus;
        else if (Str == "Fish")
            S = Species::Fish;
        else if (Str == "Flower")
            S = Species::Flower;
        else if (Str == "Grass")
            S = Species::Grass;
        else if (Str == "Mold")
            S = Species::Mold;
        else if (Str == "Mushroom")
            S = Species::Mushroom;
        else if (Str == "Mycellium")
            S = Species::Mycellium;
        else if (Str == "Primate")
            S = Species::Primate;
        else if (Str == "Shark")
            S = Species::Shark;
        else if (Str == "Single_Cell")
            S = Species::Single_Cell;
        else if (Str == "Snake")
            S = Species::Snake;
        else if (Str == "Tree")
            S = Species::Tree;
        else if (Str == "Weed")
            S = Species::Weed;
        else{
            std::cout << "ERROR: Invalid species in EvolutionStats.txt\n";
            continue;
        }
        EvoData ED(S, speed, health, passive_xp, passive_gold);
        V.push_back(ED);
    }
    return V;
}

const char* Game::SpeciesToString(Species S) const{
    switch (S){
        case Species::Amphibian:
            return "Amphibian";
        case Species::Bird:
            return "Bird";
        case Species::Bush:
            return "Bush";
        case Species::Canine:
            return "Canine";
        case Species::Crocodile:
            return "Crocodile";
        case Species::Feline:
            return "Feline";
        case Species::Fungus:
            return "Fungus";
        case Species::Fish:
            return "Fish";
        case Species::Flower:
            return "Flower";
        case Species::Grass:
            return "Grass";
        case Species::Mold:
            return "Mold";
        case Species::Mushroom:
            return "Mushroom";
        case Species::Mycellium:
            return "Mycellium";
        case Species::Primate:
            return "Primate";
        case Species::Shark:
            return "Shark";
        case Species::Single_Cell:
            return "Single Cell";
        case Species::Snake:
            return "Snake";
        case Species::Tree:
            return "Tree";
        case Species::Weed:
            return "Weed";
    }
    return "";
}