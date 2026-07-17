#pragma once
#include "raylib.h"
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

    

    Textures() : Single_Cell_1(LoadTexture(ASSETS_PATH"Single_Cell_1.png")),
                 Single_Cell_2(LoadTexture(ASSETS_PATH"Single_Cell_2.png")),
                 Single_Cell_1_Death(LoadTexture(ASSETS_PATH"Single_Cell_1_Death.png")),
                 Single_Cell_2_Death(LoadTexture(ASSETS_PATH"Single_Cell_2_Death.png")),
                 Background(LoadTexture(ASSETS_PATH"Background.png")),
                 Left_Ui(LoadTexture(ASSETS_PATH"Left_Edge.png")),
                 Middle_Ui(LoadTexture(ASSETS_PATH"Middle_Piece.png")),
                 Right_Ui(LoadTexture(ASSETS_PATH"Right_Edge.png")),
                 Bullet(LoadTexture(ASSETS_PATH"Bullet.png")),
                 Rock(LoadTexture(ASSETS_PATH"Rock.png")),
                 Sharp_Rock(LoadTexture(ASSETS_PATH"Sharp_Rock.png")),
                 Bow(LoadTexture(ASSETS_PATH"Bow.png")),
                 Crossbow(LoadTexture(ASSETS_PATH"Crossbow.png")),
                 Knife(LoadTexture(ASSETS_PATH"Knife.png")),
                 SlingShot(LoadTexture(ASSETS_PATH"SlingShot.png")),
                 AK_47(LoadTexture(ASSETS_PATH"AK_47.png")),
                 Arrow(LoadTexture(ASSETS_PATH"Arrow.png")),


                 Weed_1(LoadTexture(ASSETS_PATH"Weed_1.png")),
                 Weed_2(LoadTexture(ASSETS_PATH"Weed_2.png")),
                 Fish_1(LoadTexture(ASSETS_PATH"Fish_1.png")),
                 Fish_2(LoadTexture(ASSETS_PATH"Fish_2.png")),
                 Amphibian_1(LoadTexture(ASSETS_PATH"Frog_1.png")),
                 Amphibian_2(LoadTexture(ASSETS_PATH"Frog_2.png")),
                 Fungus_1(LoadTexture(ASSETS_PATH"Fungi_1.png")),
                 Fungus_2(LoadTexture(ASSETS_PATH"Fungi_2.png")),
                 Crocodile_1(LoadTexture(ASSETS_PATH"Crocodile_1.png")),
                 Crocodile_2(LoadTexture(ASSETS_PATH"Crocodile_2.png")),
                 Rat_1(LoadTexture(ASSETS_PATH"Rat_1.png")),
                 Rat_2(LoadTexture(ASSETS_PATH"Rat_2.png")),
                 Mushroom_1(LoadTexture(ASSETS_PATH"Mushroom_1.png")),
                 Mushroom_2(LoadTexture(ASSETS_PATH"Mushroom_2.png")),
                 Mycellium_1(LoadTexture(ASSETS_PATH"Mycellium_1.png")),
                 Mycellium_2(LoadTexture(ASSETS_PATH"Mycellium_2.png")),
                 Bird_1(LoadTexture(ASSETS_PATH"Bird_1.png")),
                 Bird_2(LoadTexture(ASSETS_PATH"Bird_2.png")),
                 Late_Dinosaur_1(LoadTexture(ASSETS_PATH"Late_Dino_1.png")),
                 Late_Dinosaur_2(LoadTexture(ASSETS_PATH"Late_Dino_2.png")),
                 Feline_1(LoadTexture(ASSETS_PATH"Cat_1.png")),
                 Feline_2(LoadTexture(ASSETS_PATH"Cat_2.png")),
                 Canine_1(LoadTexture(ASSETS_PATH"Dog_1.png")),
                 Canine_2(LoadTexture(ASSETS_PATH"Dog_2.png")),
                 Primate_1(LoadTexture(ASSETS_PATH"Monkey_1.png")),
                 Primate_2(LoadTexture(ASSETS_PATH"Monkey_2.png")),
                 Human_1(LoadTexture(ASSETS_PATH"Human_1.png")),
                 Human_2(LoadTexture(ASSETS_PATH"Human_2.png")),
                 Snake_1(LoadTexture(ASSETS_PATH"Snake_1.png")),
                 Snake_2(LoadTexture(ASSETS_PATH"Snake_2.png")),
                 Grass_1(LoadTexture(ASSETS_PATH"Grass_1.png")),
                 Grass_2(LoadTexture(ASSETS_PATH"Grass_2.png")),
                 Flower_1(LoadTexture(ASSETS_PATH"Flower_1.png")),
                 Flower_2(LoadTexture(ASSETS_PATH"Flower_2.png")),
                 Bush_1(LoadTexture(ASSETS_PATH"Bush_1.png")),
                 Bush_2(LoadTexture(ASSETS_PATH"Bush_2.png")),
                 Tree_1(LoadTexture(ASSETS_PATH"Tree_1.png")),
                 Tree_2(LoadTexture(ASSETS_PATH"Tree_2.png")),
                 Mould_1(LoadTexture(ASSETS_PATH"Mould_1.png")),
                 Mould_2(LoadTexture(ASSETS_PATH"Mould_2.png")),
                 Shark_1(LoadTexture(ASSETS_PATH"Shark_1.png")),
                 Shark_2(LoadTexture(ASSETS_PATH"Shark_2.png")),
                 
                 Weed_1_Death(LoadTexture(ASSETS_PATH"Weed_1_Death.png")),
                 Weed_2_Death(LoadTexture(ASSETS_PATH"Weed_2_Death.png")),
                 Fish_1_Death(LoadTexture(ASSETS_PATH"Fish_1_Death.png")),
                 Fish_2_Death(LoadTexture(ASSETS_PATH"Fish_2_Death.png")),
                 Amphibian_1_Death(LoadTexture(ASSETS_PATH"Frog_1_Death.png")),
                 Amphibian_2_Death(LoadTexture(ASSETS_PATH"Frog_2_Death.png")),
                 Fungus_1_Death(LoadTexture(ASSETS_PATH"Fungi_1_Death.png")),
                 Fungus_2_Death(LoadTexture(ASSETS_PATH"Fungi_2_Death.png")),
                 Crocodile_1_Death(LoadTexture(ASSETS_PATH"Crocodile_1_Death.png")),
                 Crocodile_2_Death(LoadTexture(ASSETS_PATH"Crocodile_2_Death.png")),
                 Rat_1_Death(LoadTexture(ASSETS_PATH"Rat_1_Death.png")),
                 Rat_2_Death(LoadTexture(ASSETS_PATH"Rat_2_Death.png")),
                 Mushroom_1_Death(LoadTexture(ASSETS_PATH"Mushroom_1_Death.png")),
                 Mushroom_2_Death(LoadTexture(ASSETS_PATH"Mushroom_2_Death.png")),
                 Mycellium_1_Death(LoadTexture(ASSETS_PATH"Mycellium_1_Death.png")),
                 Mycellium_2_Death(LoadTexture(ASSETS_PATH"Mycellium_2_Death.png")),
                 Bird_1_Death(LoadTexture(ASSETS_PATH"Bird_1_Death.png")),
                 Bird_2_Death(LoadTexture(ASSETS_PATH"Bird_2_Death.png")),
                 Late_Dinosaur_1_Death(LoadTexture(ASSETS_PATH"Late_Dino_1_Death.png")),
                 Late_Dinosaur_2_Death(LoadTexture(ASSETS_PATH"Late_Dino_2_Death.png")),
                 Feline_1_Death(LoadTexture(ASSETS_PATH"Cat_1_Death.png")),
                 Feline_2_Death(LoadTexture(ASSETS_PATH"Cat_2_Death.png")),
                 Canine_1_Death(LoadTexture(ASSETS_PATH"Dog_1_Death.png")),
                 Canine_2_Death(LoadTexture(ASSETS_PATH"Dog_2_Death.png")),
                 Primate_1_Death(LoadTexture(ASSETS_PATH"Monkey_1_Death.png")),
                 Primate_2_Death(LoadTexture(ASSETS_PATH"Monkey_2_Death.png")),
                 Human_1_Death(LoadTexture(ASSETS_PATH"Human_1_Death.png")),
                 Human_2_Death(LoadTexture(ASSETS_PATH"Human_2_Death.png")),
                 Snake_1_Death(LoadTexture(ASSETS_PATH"Snake_1_Death.png")),
                 Snake_2_Death(LoadTexture(ASSETS_PATH"Snake_2_Death.png")),
                 Grass_1_Death(LoadTexture(ASSETS_PATH"Grass_1_Death.png")),
                 Grass_2_Death(LoadTexture(ASSETS_PATH"Grass_2_Death.png")),
                 Flower_1_Death(LoadTexture(ASSETS_PATH"Flower_1_Death.png")),
                 Flower_2_Death(LoadTexture(ASSETS_PATH"Flower_2_Death.png")),
                 Bush_1_Death(LoadTexture(ASSETS_PATH"Bush_1_Death.png")),
                 Bush_2_Death(LoadTexture(ASSETS_PATH"Bush_2_Death.png")),
                 Tree_1_Death(LoadTexture(ASSETS_PATH"Tree_1_Death.png")),
                 Tree_2_Death(LoadTexture(ASSETS_PATH"Tree_2_Death.png")),
                 Mould_1_Death(LoadTexture(ASSETS_PATH"Mould_1_Death.png")),
                 Mould_2_Death(LoadTexture(ASSETS_PATH"Mould_2_Death.png")),
                 Shark_1_Death(LoadTexture(ASSETS_PATH"Shark_1_Death.png")),
                 Shark_2_Death(LoadTexture(ASSETS_PATH"Shark_2_Death.png"))

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
    }
};