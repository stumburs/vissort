#include <raylib.h>

int main()
{
    InitWindow(1280, 720, "vissort");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(BLACK);
        }
        EndDrawing();
    }
    CloseWindow();
}