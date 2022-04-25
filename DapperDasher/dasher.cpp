#include "raylib.h"

int main()
{
#pragma region Window Fields
    const int windowWidth = 512;
    const int windowHeight = 380;
    const char* windowName = "Dapper Dash";
    
    InitWindow(windowWidth,windowHeight,windowName);
    SetTargetFPS(60);
#pragma endregion
/*================================================================================================================*/
#pragma region Player Fields
    Texture2D playerSprite = LoadTexture("./textures/scarfy.png");
    Vector2 playerSpriteSize {128,128};
    Vector2 playerPos {((float)windowWidth/2) - (playerSpriteSize.x/2),((float)windowHeight - playerSpriteSize.y)};
    Rectangle playerRect{0,0,(float)playerSprite.width/6,(float)playerSprite.height};
    
    int animationFrame = 0;
    const float animationUpdate = 1.0/12.0;
    float animationTime = 0;

    int velocity = 0;
    const int gravity = 1000;
    const int jumpForce = -600;

    bool grounded;
#pragma endregion
/*================================================================================================================*/
#pragma region Hazard Fields
    
#pragma endregion
/*================================================================================================================*/
    //Update loop...
    while (WindowShouldClose() == false)
    {        
        float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);

        if (playerPos.y >= windowHeight - playerRect.height)
        {
            velocity = 0;
            playerPos.y = windowHeight - playerRect.height;
            grounded = true;
        }
        else
        {
            velocity += gravity * deltaTime;
            grounded = false;
        }
        
        if (IsKeyPressed(KEY_SPACE) && grounded == true)
        {
            velocity = jumpForce;
        }
        
        playerPos.y += velocity * deltaTime;

        DrawTextureRec(playerSprite,playerRect,playerPos,WHITE);

        animationTime += deltaTime;

        if (animationTime >= animationUpdate)
        {
            animationTime = 0;

            playerRect.x = animationFrame * playerRect.width;
            animationFrame++;

            if (animationFrame > 5)
            {
                animationFrame = 0;
            }
        }

        EndDrawing();
    }

    CloseWindow();
}
