#include "raylib.h"

int main()
{
    //Fields...
    // Window Fields...
    const int windowWidth = 512;
    const int windowHeight = 380;
    const char* windowName = "Classy Clash";

    InitWindow(windowWidth, windowHeight, windowName);
    SetTargetFPS(60);

    while (WindowShouldClose == false)
    {
        //Input Logic...
        
        //Game Logic...

        //Draw logic...
        BeginDrawing();
        ClearBackground(WHITE);

        EndDrawing();
    }
    //Unload textures etc...
    CloseWindow();
}