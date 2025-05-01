#include "App.hpp"
#include "raylib.h"

App::App() : gui(sorter, data_generator)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "vissort");
    SetTargetFPS(144);
}

void App::Run()
{
    while (!WindowShouldClose())
    {
        this->gui.Render();
    }
    CloseWindow();
}