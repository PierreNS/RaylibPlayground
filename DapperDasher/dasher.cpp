#include "raylib.h"

int main()
{
    int windowWidth = 512;
    int windowHeight = 380;
    const char* windowName = "Dapper Dash";

    Vector2 rectSize {50,80};
    Vector2 rectPos {((float)windowWidth/2)-(rectSize.x/2),(float)windowHeight-rectSize.y};
    Rectangle rect{rectPos.x,rectPos.y,rectSize.x,rectSize.y};
    
    int velocity = 0;
    int gravity = 1;
    int jumpForce = -22;

    InitWindow(windowWidth,windowHeight,windowName);

    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {        
        BeginDrawing();
        ClearBackground(WHITE);

        //Game logic here...
        if (rect.y >= windowHeight - rect.height)
        {
            velocity = 0;
            rect.y = windowHeight - rect.height;
        }
        else
        {
            velocity += gravity;
        }
        
        if (IsKeyPressed(KEY_SPACE))
        {
            velocity = jumpForce;
        }
        
        rect.y += velocity;

        DrawRectangleRec(rect,BLUE);

        EndDrawing();
    }

    CloseWindow();
}
