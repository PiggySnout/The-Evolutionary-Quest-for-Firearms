#include "MainMenu.hpp"
#include <algorithm>
MainMenu::MainMenu() :

hovered_1(false),
hovered_2(false),
Rect({0,0,0,0}),
Rect2({0,0,0,0})

{
    
}

void MainMenu::Draw(){
    Rect = {
        GetScreenWidth() / 2.0f - GetScreenWidth() / 4.0f,
        GetScreenHeight() / 2.0f - 60.0f,
        GetScreenWidth()/2.0f,
        60
    };
    Rect2 = {
        GetScreenWidth() / 2.0f - GetScreenWidth() / 4.0f,
        GetScreenHeight() / 2.0f + 60.0f,
        GetScreenWidth()/2.0f,
        60
    };

    DrawRectangleRec(Rect, hovered_1 ? DARKBLUE : BLUE);
    DrawRectangleRec(Rect2, hovered_2 ? DARKBLUE : BLUE);

    DrawText("Play", Rect.x + Rect.width/2 - 60, Rect.y + Rect.height/2 - 25, 50, WHITE);
    DrawText("Quit", Rect2.x + Rect2.width/2 - 60, Rect2.y + Rect2.height/2 - 25, 50, WHITE);


    float scale = std::min(GetScreenWidth() / 900.0f, GetScreenHeight() / 600.0f);
    int fontSize = static_cast<int>(70 * scale);

    int x1 = (GetScreenWidth() - MeasureText("The Evolutionary", fontSize)) / 2;
    int x2 = (GetScreenWidth() - MeasureText("Quest for Firearms", fontSize)) / 2;

    DrawText("The Evolutionary", x1, static_cast<int>(30 * scale), fontSize, WHITE);
    DrawText("Quest for Firearms", x2, static_cast<int>(100 * scale), fontSize, WHITE);
}

int MainMenu::Input(){
    Vector2 Pos = GetMousePosition();

    hovered_1 = CheckCollisionPointRec(Pos, Rect);
    hovered_2 = CheckCollisionPointRec(Pos, Rect2);

    if (hovered_1 || hovered_2)
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    else 
        SetMouseCursor(MOUSE_CURSOR_ARROW);


    if (hovered_1 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return 1;
    
    if (hovered_2 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        return 2;
    return 0;
}