#include <raylib.h>
#include "Game.hpp"
int main() 
{   
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(900, 600, "The Evolutionary Quest for firearms");
    
    SetTargetFPS(60);

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
    
    CloseWindow();
}
