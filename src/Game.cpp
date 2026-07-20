#include "path_funcs.hpp"
#include "Game.hpp"
#include "raymath.h"
#include <iostream>
#include <format>
#include <algorithm>
#include "Species.hpp"
#include <cassert>
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
               evoUi(p, w, WeaponStats, T, false, true),
               Click(T.Click),
               lastEvoOptionCount(-1),
               paused(false),
               Levels(ReadLevels()),
               mob_cap(Levels[0].getMob_cap())
               
               
{
    u.newButton("Weapon_Button", true);
    u.newButton("Evolve", false);
    u.newButton("Medkit +10hp", true);


    u.SetBarTime(300);
}

bool Game::Logic(){
    if (w.getak_number() == 48){
        if (timer == -1)
            timer = 300;
        if (timer != 0){
            DrawRectangle(0,0, GetScreenWidth(), GetScreenHeight(), Fade(GREEN, 0.6f));
            DrawText("You WIN", GetScreenWidth()/2 - 20, GetScreenHeight()/2 - 150, 40, WHITE);
        }
        if (timer-- == 0){
            CloseWindow();
            return true;
        }
    }
    if (!p.IsDead()){
        if (p.KillIfNec()){
            timer = 300;
            PlaySound(T.Game_Over);
        }
    }
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
    
    if (IsKeyPressed(KEY_ESCAPE)){
        paused = !paused;
    }
    
    if (!p.getEvolving() && !paused){
        u.DrawButtons();
    }
    else
        evoUi.DrawButtons();
    Vector2 TruePos{
        p.getPos().x, //+ p.getTextureDim().x / 2
        p.getPos().y //+ p.getTextureDim().y / 2
    };
    std::time_t now = std::time(nullptr);
    
    
    if (!p.getEvolving() && !paused){
        if (p.Input() && u.IsbarFull() && w.hasAmmo() || u.AdvanceBar())
            w.SpawnBullet(p.getPos(), C.ScreenToWorld(GetMousePosition()), Bullets);
    
        if (u.IsbarFull() && !w.hasAmmo())
            u.ResetBar();
        if (now - last >= 1){
            p.UpdateTexture();
            last = std::time(nullptr);
            for (Npc& i : Npcs)
                i.UpdatePlayerPos(TruePos);
        }
        for (Npc& i : Npcs){
            i.UpdatePlayerSize(p.getTextureDim());
            if (i.CheckPlayerCollision()){
                p.TakeDamage(i.getDamage() * (i.getAI() == AIType::Ambush ? 1.5f : 1.0f));
            }
            i.Move();
        }
        killBullets();
        killNpcs();
        for (Npc& i : Npcs)
            i.ChangeTexture();
    }

    manageButtons();
    
    if (p.getEvolving()) evoUi.EvalCursor();
    else u.EvalCursor();
    
    
    if (IsKeyDown(KEY_P) && IsKeyDown(KEY_I) && IsKeyPressed(KEY_G))
        LevelUp();
    
    SpawnEnemies();
    

    if (paused)
        DrawText("Paused...", GetScreenWidth() / 2 - 80, GetScreenHeight() /2 - 140, 40, LIGHTGRAY);
    return false;
}
void Game::Draw_all(){
    C.UpdateCameraPos();
    
    C.Draw_All();
}
void Game::NextLevel(){

}

void Game::SpawnEnemies(){
    const float WORLD_WIDTH  = 75 * 20.0f;
    const float WORLD_HEIGHT = 75 * 20.0f;

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

        Npc N(T, Levels[level].getNpctype(), NpcPos, p.findInEvoStats(Levels[level].getNpctype(), Levels[level].getNpc_evo_level() - 1).health / 7, Levels[level].getNpcGoldDrop(), Levels[level].getNpcXpDrop(), p.findInEvoStats(Levels[level].getNpctype(), Levels[level].getNpc_evo_level() - 1).speed * 0.8f, 1.0f, A, &Npcs);
        
        Npcs.push_back(N);
    }
}

std::vector<weaponStat> Game::ReadStats(){
    std::vector<weaponStat> V{};
    std::ifstream FILE(GetDataPath("WeaponStats.txt"));
    if (!FILE){
        std::cout << "ERROR: Failed to open WeaponStats.txt\n";
        return V;
    }   
    else 
        TraceLog(LOG_INFO, "IT WORKED");
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
            //default:
            //    T = type::Rock; //hopefully this doesn't happen
        }
        weaponStat WS(T, damage, speed, range, rechargeTime, price);
        V.push_back(WS);
    }
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
    if (!p.getEvolving()){
        if (w.getak_number() == 48)
            u.deleteButton(0);

        //Weapon Upgrade Button
        if (!u.isNull(0)){
            if (w.getak_number() + 1 != 48)
                u.getButton(0).setText(std::format("UNLOCK LVL {}", w.getak_number()+1));
            else
                u.getButton(0).setText(std::format("WIN!!!", w.getak_number()+1));
            u.getButton(0).setPrice(WeaponStats[w.getak_number()].price); //don't use -1 because we want the next weapon's price
            if (u.getButton(0).isLocked()){
                if (u.getButton(0).getPrice() <= p.getGold())
                    u.getButton(0).ToggleLock(); //unlock if the player has enough gold
            }
            else if (u.getButton(0).getPrice() > p.getGold())
                u.getButton(0).ToggleLock(); //this should lock it if the player doesn't have enough gold
            if (u.getButton(0).Input()){
                PlaySound(Click);
                w.LevelUp();
                p.giveGold(-(u.getButton(0).getPrice()));
            }
        }
        //Evolve Button
        if (u.isNull(1))
            return;
        
        if (p.findInEvoStats(p.getSpecies(), p.getEvo_Level() - 1).price == -1){
            u.deleteButton(1);
            return;
        }

        u.getButton(1).setPrice(EvoStats[p.getEvo_Level() - 1].price); //EvoPrice
        u.getButton(1).setText("Evolve");


        if (u.getButton(1).isLocked()){
            if (u.getButton(1).getPrice() <= p.getXP())
                u.getButton(1).ToggleLock();
        }
        else if (u.getButton(1).getPrice() > p.getXP())
            u.getButton(1).ToggleLock();

        if (u.getButton(1).Input()){
            PlaySound(Click);
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
        }
        if (u.getButton(2).Input() && p.getHealth() < p.getMaxHealth()){
                PlaySound(Click);
                MedkitPrice += 5;
                p.giveGold(-(u.getButton(2).getPrice()));
                p.Heal(15);
            }
    }
    else if (p.getEvolving()){
        int currentCount = p.getNext().size();
        if (currentCount != lastEvoOptionCount){
            for (int j = 0 ; j < 4 ; ++j)
                evoUi.deleteButton(j);          // clear whatever was there before
            for (int j = 0 ; j < currentCount ; ++j)
                evoUi.newButton("EvoButton", false);
            lastEvoOptionCount = currentCount;
        }

        for(int i = 0 ; i < p.getNext().size() ; ++i){
            if (evoUi.isNull(i))
                continue;
            evoUi.getButton(i).setText(SpeciesToString(p.getNext()[i]));

            if (evoUi.getButton(i).Input()){
                PlaySound(Click);
                p.Evolve(i);
                FindNextLevel();
                if (p.getNext().empty()){
                    for (int j = 0 ; j < 4 ; ++j)
                        evoUi.deleteButton(j);
                    p.StopEvol();
                    lastEvoOptionCount = -1;// reset for the next evolve cycle
                }
                break;
            }
            evoUi.getButton(i).setPrice(0);
        }
    }
}

std::vector<EvoData> Game::ReadEvoData(){
    std::vector<EvoData> V{};
    std::ifstream FILE(GetDataPath("EvolutionStats.txt"));
    if (!FILE){
        std::cout << "ERROR: Failed to open EvolutionStats.txt\n";
        return V;
    }  
    else 
        TraceLog(LOG_INFO, "IT WORKED");
    std::string Str;
    
    Species S;
    
    float speed, health;
    unsigned int passive_xp, passive_gold;
    int Xp_price;
    while (FILE>>Str>>speed>>health>>passive_xp>>passive_gold>>Xp_price){
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
        else if (Str == "Rat")
            S = Species::Rat;
        else if (Str == "Dinosaur" || Str == "Late_Dinosaur")
            S = Species::Late_Dinosaur;
        else if (Str == "Human")
            S = Species::Human;
        else{
            std::cout << "ERROR: Invalid species in EvolutionStats.txt\n";
            continue;
        }
        EvoData ED(S, speed, health, passive_xp, passive_gold, Xp_price);
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
        case Species::Late_Dinosaur:
            return "Dinosaur";
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
        case Species::Human:
            return "Human";
        case Species::Mold:
            return "Mold";
        case Species::Mushroom:
            return "Mushroom";
        case Species::Mycellium:
            return "Mycellium";
        case Species::Primate:
            return "Primate";
        case Species::Rat:
            return "Rat";
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

std::vector<Level> Game::ReadLevels(){
    std::vector<Level> V{};

    Species S;
    std::string Str;
    int Mob_cap;
    int MinGold, MaxGold;
    int MinXp, MaxXp;
    int evo_level;
    TraceLog(LOG_INFO, "Trying to open: %s", GetDataPath("LevelData.txt").c_str());
    std::ifstream FILE(GetDataPath("LevelData.txt"));
    if (!FILE){
        std::cout << "ERROR: Failed to open LevelData.txt\n";
        return V;
    } 
    else 
        TraceLog(LOG_INFO, "IT WORKED");
    
    while(FILE>>Str>>Mob_cap>>MinGold>>MaxGold>>MinXp>>MaxXp>>evo_level){
        if (Str == "Amphibian")
            S = Species::Amphibian;
        else if (Str == "Bird")
            S = Species::Snake;
        else if (Str == "Bush")
            S = Species::Feline;
        else if (Str == "Canine")
            S = Species::Feline;
        else if (Str == "Crocodile")
            S = Species::Crocodile;
        else if (Str == "Feline")
            S = Species::Canine;
        else if (Str == "Fungus")
            S = Species::Single_Cell;
        else if (Str == "Fish")
            S = Species::Fish;
        else if (Str == "Flower")
            S = Species::Rat;
        else if (Str == "Grass")
            S = Species::Rat;
        else if (Str == "Mold")
            S = Species::Mold;
        else if (Str == "Mushroom")
            S = Species::Bird;
        else if (Str == "Mycellium")
            S = Species::Mycellium;
        else if (Str == "Primate")
            S = Species::Snake;
        else if (Str == "Shark")
            S = Species::Fish;
        else if (Str == "Single_Cell")
            S = Species::Single_Cell;
        else if (Str == "Snake")
            S = Species::Snake;
        else if (Str == "Tree")
            S = Species::Primate;
        else if (Str == "Weed")
            S = Species::Single_Cell;
        else if (Str == "Rat")
            S = Species::Rat;
        else if (Str == "Dinosaur" || Str == "Late_Dinosaur")
            S = Species::Late_Dinosaur;
        else if (Str == "Human")
            S = Species::Human;
        else{
            std::cout << "ERROR: Invalid species in LevelData.txt\n";
            continue;
        }
        Level L (S, Mob_cap, MinGold, MaxGold, MinXp, MaxXp, evo_level);
        V.push_back(L);
    }

    return V;
}
void Game::FindNextLevel(){
    for (; level < Levels.size() ; ++level){
        if (Levels[level].getNpctype() == p.getSpecies())
            break;
    }
}