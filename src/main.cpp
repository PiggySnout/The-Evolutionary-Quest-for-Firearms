#include <raylib.h>
#include "Game.hpp"



int main() 
{   
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 600, "The Evolutionary Quest for firearms");
    InitAudioDevice();
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    
    Game g;
    
    while (!WindowShouldClose())
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
