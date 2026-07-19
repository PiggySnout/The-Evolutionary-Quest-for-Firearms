#pragma once
#include "path_funcs.hpp"
#include <string>
struct Textures{
    Texture2D Single_Cell_1;
    Texture2D Single_Cell_2;
    Texture2D Single_Cell_1_Death;
    Texture2D Single_Cell_2_Death;
    Texture2D Background;
    Texture2D Left_Ui;
    Texture2D Middle_Ui;
    Texture2D Right_Ui;
    Texture2D Bullet;
    Texture2D Rock;
    Texture2D Sharp_Rock;
    Texture2D Bow;
    Texture2D Crossbow;
    Texture2D Knife;
    Texture2D SlingShot;
    Texture2D AK_47;
    Texture2D Arrow;

    Texture2D Weed_1;
    Texture2D Fish_1;
    Texture2D Amphibian_1;
    Texture2D Fungus_1;


    Texture2D Crocodile_1;
    Texture2D Rat_1;
    Texture2D Mushroom_1;
    Texture2D Mycellium_1;

    Texture2D Bird_1;
    Texture2D Late_Dinosaur_1;
    Texture2D Feline_1;
    Texture2D Canine_1;
    Texture2D Primate_1;

    Texture2D Human_1;

    Texture2D Snake_1;

    Texture2D Grass_1;
    Texture2D Flower_1;
    Texture2D Bush_1;

    Texture2D Tree_1;

    Texture2D Mould_1;
    
    Texture2D Shark_1;


    Texture2D Weed_2;
    Texture2D Fish_2;
    Texture2D Amphibian_2;
    Texture2D Fungus_2;

    Texture2D Crocodile_2;
    Texture2D Rat_2;
    Texture2D Mushroom_2;
    Texture2D Mycellium_2;

    Texture2D Bird_2;
    Texture2D Late_Dinosaur_2;
    Texture2D Feline_2;
    Texture2D Canine_2;
    Texture2D Primate_2;

    Texture2D Human_2;

    Texture2D Snake_2;

    Texture2D Grass_2;
    Texture2D Flower_2;
    Texture2D Bush_2;

    Texture2D Tree_2;

    Texture2D Mould_2;
    
    Texture2D Shark_2;


    //deaths now!!!


    Texture2D Weed_1_Death;
    Texture2D Fish_1_Death;
    Texture2D Amphibian_1_Death;
    Texture2D Fungus_1_Death;

    Texture2D Crocodile_1_Death;
    Texture2D Rat_1_Death;
    Texture2D Mushroom_1_Death;
    Texture2D Mycellium_1_Death;

    Texture2D Bird_1_Death;
    Texture2D Late_Dinosaur_1_Death;
    Texture2D Feline_1_Death;
    Texture2D Canine_1_Death;
    Texture2D Primate_1_Death;

    Texture2D Human_1_Death;

    Texture2D Snake_1_Death;

    Texture2D Grass_1_Death;
    Texture2D Flower_1_Death;
    Texture2D Bush_1_Death;

    Texture2D Tree_1_Death;

    Texture2D Mould_1_Death;
    
    Texture2D Shark_1_Death;


    Texture2D Weed_2_Death;
    Texture2D Fish_2_Death;
    Texture2D Amphibian_2_Death;
    Texture2D Fungus_2_Death;

    Texture2D Crocodile_2_Death;
    Texture2D Rat_2_Death;
    Texture2D Mushroom_2_Death;
    Texture2D Mycellium_2_Death;

    Texture2D Bird_2_Death;
    Texture2D Late_Dinosaur_2_Death;
    Texture2D Feline_2_Death;
    Texture2D Canine_2_Death;
    Texture2D Primate_2_Death;

    Texture2D Human_2_Death;

    Texture2D Snake_2_Death;

    Texture2D Grass_2_Death;
    Texture2D Flower_2_Death;
    Texture2D Bush_2_Death;

    Texture2D Tree_2_Death;

    Texture2D Mould_2_Death;
    
    Texture2D Shark_2_Death;

    Sound Click;
    Sound ak_sound;
    Sound Game_Over;
    Sound Gold;
    Sound Evolve;
    Sound Swoosh;
    Sound Rock_s;
    Sound Knife_s;
    Sound Damage;
    Sound Ping;

    

    Textures() : Single_Cell_1(LoadTexture(GetAssetsPath("Single_Cell_1.png").c_str())),
                 Single_Cell_2(LoadTexture(GetAssetsPath("Single_Cell_2.png").c_str())),
                 Single_Cell_1_Death(LoadTexture(GetAssetsPath("Single_Cell_1_Death.png").c_str())),
                 Single_Cell_2_Death(LoadTexture(GetAssetsPath("Single_Cell_2_Death.png").c_str())),
                 Background(LoadTexture(GetAssetsPath("Background.png").c_str())),
                 Left_Ui(LoadTexture(GetAssetsPath("Left_Edge.png").c_str())),
                 Middle_Ui(LoadTexture(GetAssetsPath("Middle_Piece.png").c_str())),
                 Right_Ui(LoadTexture(GetAssetsPath("Right_Edge.png").c_str())),
                 Bullet(LoadTexture(GetAssetsPath("Bullet.png").c_str())),
                 Rock(LoadTexture(GetAssetsPath("Rock.png").c_str())),
                 Sharp_Rock(LoadTexture(GetAssetsPath("Sharp_Rock.png").c_str())),
                 Bow(LoadTexture(GetAssetsPath("Bow.png").c_str())),
                 Crossbow(LoadTexture(GetAssetsPath("Crossbow.png").c_str())),
                 Knife(LoadTexture(GetAssetsPath("Knife.png").c_str())),
                 SlingShot(LoadTexture(GetAssetsPath("SlingShot.png").c_str())),
                 AK_47(LoadTexture(GetAssetsPath("AK_47.png").c_str())),
                 Arrow(LoadTexture(GetAssetsPath("Arrow.png").c_str())),


                 Weed_1(LoadTexture(GetAssetsPath("Weed_1.png").c_str())),
                 Weed_2(LoadTexture(GetAssetsPath("Weed_2.png").c_str())),
                 Fish_1(LoadTexture(GetAssetsPath("Fish_1.png").c_str())),
                 Fish_2(LoadTexture(GetAssetsPath("Fish_2.png").c_str())),
                 Amphibian_1(LoadTexture(GetAssetsPath("Frog_1.png").c_str())),
                 Amphibian_2(LoadTexture(GetAssetsPath("Frog_2.png").c_str())),
                 Fungus_1(LoadTexture(GetAssetsPath("Fungi_1.png").c_str())),
                 Fungus_2(LoadTexture(GetAssetsPath("Fungi_2.png").c_str())),
                 Crocodile_1(LoadTexture(GetAssetsPath("Crocodile_1.png").c_str())),
                 Crocodile_2(LoadTexture(GetAssetsPath("Crocodile_2.png").c_str())),
                 Rat_1(LoadTexture(GetAssetsPath("Rat_1.png").c_str())),
                 Rat_2(LoadTexture(GetAssetsPath("Rat_2.png").c_str())),
                 Mushroom_1(LoadTexture(GetAssetsPath("Mushroom_1.png").c_str())),
                 Mushroom_2(LoadTexture(GetAssetsPath("Mushroom_2.png").c_str())),
                 Mycellium_1(LoadTexture(GetAssetsPath("Mycellium_1.png").c_str())),
                 Mycellium_2(LoadTexture(GetAssetsPath("Mycellium_2.png").c_str())),
                 Bird_1(LoadTexture(GetAssetsPath("Bird_1.png").c_str())),
                 Bird_2(LoadTexture(GetAssetsPath("Bird_2.png").c_str())),
                 Late_Dinosaur_1(LoadTexture(GetAssetsPath("Late_Dino_1.png").c_str())),
                 Late_Dinosaur_2(LoadTexture(GetAssetsPath("Late_Dino_2.png").c_str())),
                 Feline_1(LoadTexture(GetAssetsPath("Cat_1.png").c_str())),
                 Feline_2(LoadTexture(GetAssetsPath("Cat_2.png").c_str())),
                 Canine_1(LoadTexture(GetAssetsPath("Dog_1.png").c_str())),
                 Canine_2(LoadTexture(GetAssetsPath("Dog_2.png").c_str())),
                 Primate_1(LoadTexture(GetAssetsPath("Monkey_1.png").c_str())),
                 Primate_2(LoadTexture(GetAssetsPath("Monkey_2.png").c_str())),
                 Human_1(LoadTexture(GetAssetsPath("Human_1.png").c_str())),
                 Human_2(LoadTexture(GetAssetsPath("Human_2.png").c_str())),
                 Snake_1(LoadTexture(GetAssetsPath("Snake_1.png").c_str())),
                 Snake_2(LoadTexture(GetAssetsPath("Snake_2.png").c_str())),
                 Grass_1(LoadTexture(GetAssetsPath("Grass_1.png").c_str())),
                 Grass_2(LoadTexture(GetAssetsPath("Grass_2.png").c_str())),
                 Flower_1(LoadTexture(GetAssetsPath("Flower_1.png").c_str())),
                 Flower_2(LoadTexture(GetAssetsPath("Flower_2.png").c_str())),
                 Bush_1(LoadTexture(GetAssetsPath("Bush_1.png").c_str())),
                 Bush_2(LoadTexture(GetAssetsPath("Bush_2.png").c_str())),
                 Tree_1(LoadTexture(GetAssetsPath("Tree_1.png").c_str())),
                 Tree_2(LoadTexture(GetAssetsPath("Tree_2.png").c_str())),
                 Mould_1(LoadTexture(GetAssetsPath("Mould_1.png").c_str())),
                 Mould_2(LoadTexture(GetAssetsPath("Mould_2.png").c_str())),
                 Shark_1(LoadTexture(GetAssetsPath("Shark_1.png").c_str())),
                 Shark_2(LoadTexture(GetAssetsPath("Shark_2.png").c_str())),
                 
                 Weed_1_Death(LoadTexture(GetAssetsPath("Weed_1_Death.png").c_str())),
                 Weed_2_Death(LoadTexture(GetAssetsPath("Weed_2_Death.png").c_str())),
                 Fish_1_Death(LoadTexture(GetAssetsPath("Fish_1_Death.png").c_str())),
                 Fish_2_Death(LoadTexture(GetAssetsPath("Fish_2_Death.png").c_str())),
                 Amphibian_1_Death(LoadTexture(GetAssetsPath("Frog_1_Death.png").c_str())),
                 Amphibian_2_Death(LoadTexture(GetAssetsPath("Frog_2_Death.png").c_str())),
                 Fungus_1_Death(LoadTexture(GetAssetsPath("Fungi_1_Death.png").c_str())),
                 Fungus_2_Death(LoadTexture(GetAssetsPath("Fungi_2_Death.png").c_str())),
                 Crocodile_1_Death(LoadTexture(GetAssetsPath("Crocodile_1_Death.png").c_str())),
                 Crocodile_2_Death(LoadTexture(GetAssetsPath("Crocodile_2_Death.png").c_str())),
                 Rat_1_Death(LoadTexture(GetAssetsPath("Rat_1_Death.png").c_str())),
                 Rat_2_Death(LoadTexture(GetAssetsPath("Rat_2_Death.png").c_str())),
                 Mushroom_1_Death(LoadTexture(GetAssetsPath("Mushroom_1_Death.png").c_str())),
                 Mushroom_2_Death(LoadTexture(GetAssetsPath("Mushroom_2_Death.png").c_str())),
                 Mycellium_1_Death(LoadTexture(GetAssetsPath("Mycellium_1_Death.png").c_str())),
                 Mycellium_2_Death(LoadTexture(GetAssetsPath("Mycellium_2_Death.png").c_str())),
                 Bird_1_Death(LoadTexture(GetAssetsPath("Bird_1_Death.png").c_str())),
                 Bird_2_Death(LoadTexture(GetAssetsPath("Bird_2_Death.png").c_str())),
                 Late_Dinosaur_1_Death(LoadTexture(GetAssetsPath("Late_Dino_1_Death.png").c_str())),
                 Late_Dinosaur_2_Death(LoadTexture(GetAssetsPath("Late_Dino_2_Death.png").c_str())),
                 Feline_1_Death(LoadTexture(GetAssetsPath("Cat_1_Death.png").c_str())),
                 Feline_2_Death(LoadTexture(GetAssetsPath("Cat_2_Death.png").c_str())),
                 Canine_1_Death(LoadTexture(GetAssetsPath("Dog_1_Death.png").c_str())),
                 Canine_2_Death(LoadTexture(GetAssetsPath("Dog_2_Death.png").c_str())),
                 Primate_1_Death(LoadTexture(GetAssetsPath("Monkey_1_Death.png").c_str())),
                 Primate_2_Death(LoadTexture(GetAssetsPath("Monkey_2_Death.png").c_str())),
                 Human_1_Death(LoadTexture(GetAssetsPath("Human_1_Death.png").c_str())),
                 Human_2_Death(LoadTexture(GetAssetsPath("Human_2_Death.png").c_str())),
                 Snake_1_Death(LoadTexture(GetAssetsPath("Snake_1_Death.png").c_str())),
                 Snake_2_Death(LoadTexture(GetAssetsPath("Snake_2_Death.png").c_str())),
                 Grass_1_Death(LoadTexture(GetAssetsPath("Grass_1_Death.png").c_str())),
                 Grass_2_Death(LoadTexture(GetAssetsPath("Grass_2_Death.png").c_str())),
                 Flower_1_Death(LoadTexture(GetAssetsPath("Flower_1_Death.png").c_str())),
                 Flower_2_Death(LoadTexture(GetAssetsPath("Flower_2_Death.png").c_str())),
                 Bush_1_Death(LoadTexture(GetAssetsPath("Bush_1_Death.png").c_str())),
                 Bush_2_Death(LoadTexture(GetAssetsPath("Bush_2_Death.png").c_str())),
                 Tree_1_Death(LoadTexture(GetAssetsPath("Tree_1_Death.png").c_str())),
                 Tree_2_Death(LoadTexture(GetAssetsPath("Tree_2_Death.png").c_str())),
                 Mould_1_Death(LoadTexture(GetAssetsPath("Mould_1_Death.png").c_str())),
                 Mould_2_Death(LoadTexture(GetAssetsPath("Mould_2_Death.png").c_str())),
                 Shark_1_Death(LoadTexture(GetAssetsPath("Shark_1_Death.png").c_str())),
                 Shark_2_Death(LoadTexture(GetAssetsPath("Shark_2_Death.png").c_str())),



                 Click(LoadSound(GetSoundPath("click.wav").c_str())),
                 ak_sound(LoadSound(GetSoundPath("ak_47.wav").c_str())),
                 Game_Over(LoadSound(GetSoundPath("Game_Over.mp3").c_str())),
                 Gold(LoadSound(GetSoundPath("Get_Gold.wav").c_str())),
                 Evolve(LoadSound(GetSoundPath("Evolve.wav").c_str())),
                 Swoosh(LoadSound(GetSoundPath("BowShot.wav").c_str())),
                 Rock_s(LoadSound(GetSoundPath("Rock.wav").c_str())),
                 Knife_s(LoadSound(GetSoundPath("Knife.wav").c_str())),
                 Damage(LoadSound(GetSoundPath("Damage.wav").c_str())),
                 Ping(LoadSound(GetSoundPath("Ping.wav").c_str()))

    {
    }

    ~Textures(){
        UnloadTexture(Single_Cell_1);
        UnloadTexture(Single_Cell_2);
        UnloadTexture(Single_Cell_1_Death);
        UnloadTexture(Single_Cell_2_Death);
        UnloadTexture(Background);
        UnloadTexture(Left_Ui);
        UnloadTexture(Middle_Ui);
        UnloadTexture(Right_Ui);
        UnloadTexture(Bullet);
        UnloadTexture(Rock);
        UnloadTexture(Sharp_Rock);
        UnloadTexture(Bow);
        UnloadTexture(Crossbow);
        UnloadTexture(Knife);
        UnloadTexture(SlingShot);
        UnloadTexture(Weed_1);
        UnloadTexture(Weed_2);
        UnloadTexture(Fish_1);
        UnloadTexture(Fish_2);
        UnloadTexture(Amphibian_1);
        UnloadTexture(Amphibian_2);
        UnloadTexture(Fungus_1);
        UnloadTexture(Fungus_2);
        UnloadTexture(Crocodile_1);
        UnloadTexture(Crocodile_2);
        UnloadTexture(Rat_1);
        UnloadTexture(Rat_2);
        UnloadTexture(Mushroom_1);
        UnloadTexture(Mushroom_2);
        UnloadTexture(Mycellium_1);
        UnloadTexture(Mycellium_2);
        UnloadTexture(Bird_1);
        UnloadTexture(Bird_2);
        UnloadTexture(Late_Dinosaur_1);
        UnloadTexture(Late_Dinosaur_2);
        UnloadTexture(Feline_1);
        UnloadTexture(Feline_2);
        UnloadTexture(Canine_1);
        UnloadTexture(Canine_2);
        UnloadTexture(Primate_1);
        UnloadTexture(Primate_2);
        UnloadTexture(Human_1);
        UnloadTexture(Human_2);
        UnloadTexture(Snake_1);
        UnloadTexture(Snake_2);
        UnloadTexture(Grass_1);
        UnloadTexture(Grass_2);
        UnloadTexture(Flower_1);
        UnloadTexture(Flower_2);
        UnloadTexture(Bush_1);
        UnloadTexture(Bush_2);
        UnloadTexture(Tree_1);
        UnloadTexture(Tree_2);
        UnloadTexture(Mould_1);
        UnloadTexture(Mould_2);
        UnloadTexture(Shark_1);
        UnloadTexture(Shark_2);


        UnloadTexture(Weed_1_Death);
        UnloadTexture(Weed_2_Death);
        UnloadTexture(Fish_1_Death);
        UnloadTexture(Fish_2_Death);
        UnloadTexture(Amphibian_1_Death);
        UnloadTexture(Amphibian_2_Death);
        UnloadTexture(Fungus_1_Death);
        UnloadTexture(Fungus_2_Death);
        UnloadTexture(Crocodile_1_Death);
        UnloadTexture(Crocodile_2_Death);
        UnloadTexture(Rat_1_Death);
        UnloadTexture(Rat_2_Death);
        UnloadTexture(Mushroom_1_Death);
        UnloadTexture(Mushroom_2_Death);
        UnloadTexture(Mycellium_1_Death);
        UnloadTexture(Mycellium_2_Death);
        UnloadTexture(Bird_1_Death);
        UnloadTexture(Bird_2_Death);
        UnloadTexture(Late_Dinosaur_1_Death);
        UnloadTexture(Late_Dinosaur_2_Death);
        UnloadTexture(Feline_1_Death);
        UnloadTexture(Feline_2_Death);
        UnloadTexture(Canine_1_Death);
        UnloadTexture(Canine_2_Death);
        UnloadTexture(Primate_1_Death);
        UnloadTexture(Primate_2_Death);
        UnloadTexture(Human_1_Death);
        UnloadTexture(Human_2_Death);
        UnloadTexture(Snake_1_Death);
        UnloadTexture(Snake_2_Death);
        UnloadTexture(Grass_1_Death);
        UnloadTexture(Grass_2_Death);
        UnloadTexture(Flower_1_Death);
        UnloadTexture(Flower_2_Death);
        UnloadTexture(Bush_1_Death);
        UnloadTexture(Bush_2_Death);
        UnloadTexture(Tree_1_Death);
        UnloadTexture(Tree_2_Death);
        UnloadTexture(Mould_1_Death);
        UnloadTexture(Mould_2_Death);
        UnloadTexture(Shark_1_Death);
        UnloadTexture(Shark_2_Death);
        



        UnloadSound(Click);
        UnloadSound(ak_sound);
        UnloadSound(Game_Over);
        UnloadSound(Gold);
        UnloadSound(Evolve);
        UnloadSound(Swoosh);
        UnloadSound(Rock_s);
        UnloadSound(Knife_s);
        UnloadSound(Damage);
        UnloadSound(Ping);
    }
};