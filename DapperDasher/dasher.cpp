#include "raylib.h"

int main()
{
    //Window Fields...
    const int windowWidth = 512;
    const int windowHeight = 380;
    const char* windowName = "Dapper Dash";
    
    InitWindow(windowWidth,windowHeight,windowName);
    SetTargetFPS(60);

    //Player Fields...
    Texture2D playerSprite = LoadTexture("./textures/scarfy.png");
    Rectangle playerRect{0,0,(float)playerSprite.width/6,(float)playerSprite.height};
    Vector2 playerPos {((float)windowWidth/2) - (playerSprite.width/6),((float)windowHeight - playerSprite.height)};
    
    int animationFrame = 0;
    const float animationUpdate = 1.0/12.0;
    float animationTime = 0;

    int velocity = 0;
    const int gravity = 1000;
    const int jumpForce = -600;
    bool grounded;

    //Hazards Fields...
    Texture2D hazardSprite = LoadTexture("./textures/12_nebula_spritesheet.png");
    Rectangle hazardRect {0,0,(float)hazardSprite.width/8,(float)hazardSprite.height/8};
    Vector2 hazardPos{windowWidth,windowHeight-hazardRect.height};
    int hazardVelocity = -600;

    //Update loop...
    while (WindowShouldClose() == false)
    {        
        float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);
        /*----------Game Logic----------*/
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
        
        hazardPos.x += hazardVelocity * deltaTime;
        playerPos.y += velocity * deltaTime;

        if(grounded == true)
        {
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
        }
        
        /*----------Draw Logic----------*/
        DrawTextureRec(hazardSprite,hazardRect,hazardPos,WHITE);
        DrawTextureRec(playerSprite,playerRect,playerPos,WHITE);

        EndDrawing();
    }

    //Unload resources...
    UnloadTexture(playerSprite);
    UnloadTexture(hazardSprite);
    CloseWindow();
}
