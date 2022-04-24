#include "raylib.h"

int main()
{
    int width{800};
    int height{450};
    const char* windowName = "My New Window";

    InitWindow(width,height,windowName);

    Vector2 circlePos = {50,((float)height/2)};
    float circleRadius{25};

    Rectangle rect{((float)width/2)-25,((float)height/2)-25,50,50};

    int direction{10};

    bool gameOver{false};
    int textSize;
    SetTargetFPS(60);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (gameOver == false)
        {
            if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && circlePos.y > circleRadius) circlePos.y -= 2.0f;
            if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) && circlePos.y < (height - circleRadius)) circlePos.y += 2.0f;
            if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && circlePos.x > circleRadius) circlePos.x -= 2.0f;
            if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && circlePos.x < (width - circleRadius)) circlePos.x += 2.0f;

            rect.y += direction;
            if (rect.y > (height - rect.height) || rect.y < 0)
                direction = -direction;


            DrawCircleV(circlePos,circleRadius,BLUE);

            DrawRectangleRec(rect,RED);

            if(CheckCollisionCircleRec(circlePos,circleRadius,rect) == true)
            {
                gameOver = true;
            }
        }
        else
        {
            textSize = MeasureText("Game Over!",50);
            DrawText("Game Over!", ((int)width/2-(textSize/2)),50,50,RED);
        }
        EndDrawing();
    }
}