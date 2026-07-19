#pragma once
#include <raylib.h>
#include "Button.hpp"
class MainMenu{
    public:

    MainMenu();

    void Draw();

    int Input(); //0 -> nothing, 1 -> Play, 2 -> Quit

    private:

    bool hovered_1, hovered_2;

    Rectangle Rect;
    Rectangle Rect2;
};