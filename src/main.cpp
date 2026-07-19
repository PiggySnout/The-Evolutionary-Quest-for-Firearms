#include <raylib.h>
#include "Game.hpp"
#include "MainMenu.hpp"



int WinMain() 
{   
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 600, "The Evolutionary Quest for firearms");
    
    SetTargetFPS(60);
    

    MainMenu M;
    int inputReturn = 0;
    while (inputReturn == 0 && !WindowShouldClose()){
        BeginDrawing();
        ClearBackground(DARKGREEN);
        M.Draw();
        inputReturn = M.Input();
        EndDrawing();
    }

    SetMouseCursor(MOUSE_CURSOR_ARROW);
    if (inputReturn == 1){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Loading...", GetScreenWidth() / 2 - 100, GetScreenHeight()/2 - 15, 30, WHITE);
        EndDrawing();

        InitAudioDevice();
        SetExitKey(KEY_NULL);
    }
    Game g;
    

    while (!WindowShouldClose() && inputReturn == 1)
    {   
        BeginDrawing();
            g.Draw_all();
            if (g.Logic()){
                EndDrawing();
                break;
            }
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
}
