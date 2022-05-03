#include "raylib.h"

struct EntityData
{
    Rectangle rect;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
    int velocity;
};

bool IsGrounded(EntityData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rect.height;
}

void AnimateEntity(EntityData &data, float deltaTime, int maxFrame)
{
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0;

        data.rect.x = data.frame * data.rect.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
}

int main()
{
    // Window Fields...
    const int windowWidth = 512;
    const int windowHeight = 380;
    const char *windowName = "Dapper Dash";

    InitWindow(windowWidth, windowHeight, windowName);
    SetTargetFPS(60);

    // Player Game Logic...
    const int gravity = 1000;
    const int jumpForce = -600;
    bool grounded;

    // Entity Data...
    Texture2D background = LoadTexture("./textures/far-buildings.png");
    Texture2D midground = LoadTexture("./textures/back-buildings.png");
    Texture2D foreground = LoadTexture("./textures/foreground.png");

    Texture2D playerSprite = LoadTexture("./textures/scarfy.png");
    Texture2D hazardSprite = LoadTexture("./textures/12_nebula_spritesheet.png");

    Vector2 backgroundPos{0, 0};
    Vector2 midgroundPos{0, 0};
    Vector2 foregroundPos{0, 0};
    float backgroundScrollSpeed = -20;
    float midgroundScrollSpeed = -40;
    float foregroundScrollSpeed = -80;

    EntityData playerEntity;
    playerEntity.rect.x = 0;
    playerEntity.rect.y = 0;
    playerEntity.rect.width = (float)playerSprite.width / 6;
    playerEntity.rect.height = (float)playerSprite.height;

    playerEntity.pos.x = (float)windowWidth / 2 - playerSprite.width / 6;
    playerEntity.pos.y = (float)windowHeight - playerSprite.height;

    playerEntity.frame = 0;
    playerEntity.updateTime = 1.0 / 12.0;
    playerEntity.runningTime = 0;

    playerEntity.velocity = 0;

    const int hazardAmount = 5;
    EntityData hazards[hazardAmount]{};

    for (int i = 0; i < hazardAmount; i++)
    {
        hazards[i].rect.x = 0;
        hazards[i].rect.y = 0;
        hazards[i].rect.width = (float)hazardSprite.width / 8;
        hazards[i].rect.height = (float)hazardSprite.height / 8;
        hazards[i].pos.x = windowWidth + (i * 300);
        hazards[i].pos.y = windowHeight - hazards[i].rect.height;

        hazards[i].frame = 0;
        hazards[i].updateTime = 1.0 / 12.0;
        hazards[i].runningTime = 0;

        hazards[i].velocity = -200;
    }

    float finishLine = hazards[hazardAmount - 1].pos.x + (playerEntity.rect.width/2);
    bool gameOver = false;
    int textSize;

    // Update loop...
    while (WindowShouldClose() == false)
    {
        float deltaTime = GetFrameTime();
        backgroundPos.x += backgroundScrollSpeed * deltaTime;
        midgroundPos.x += midgroundScrollSpeed * deltaTime;
        foregroundPos.x += foregroundScrollSpeed * deltaTime;

        if (backgroundPos.x <= -background.width * 2)
        {
            backgroundPos.x = 0;
        }
        if (midgroundPos.x <= -midground.width * 2)
        {
            midgroundPos.x = 0;
        }
        if (foregroundPos.x <= -foreground.width * 2)
        {
            foregroundPos.x = 0;
        }

        if (IsGrounded(playerEntity, windowHeight))
        {
            playerEntity.velocity = 0;
            playerEntity.pos.y = windowHeight - playerEntity.rect.height;
            grounded = true;
        }
        else
        {
            playerEntity.velocity += gravity * deltaTime;
            grounded = false;
        }

        if (IsKeyPressed(KEY_SPACE) && grounded == true)
        {
            playerEntity.velocity = jumpForce;
        }

        playerEntity.pos.y += playerEntity.velocity * deltaTime;

        if (grounded == true)
        {
            AnimateEntity(playerEntity, deltaTime, 5);
        }

        for (int i = 0; i < hazardAmount; i++)
        {
            hazards[i].pos.x += hazards[i].velocity * deltaTime;
            AnimateEntity(hazards[i], deltaTime, 8);
        }

        finishLine += hazards[hazardAmount - 1].velocity * deltaTime;

        for (EntityData hazard : hazards)
        {
            float pad = 50;
            Rectangle hazardRect{
                hazard.pos.x + pad,
                hazard.pos.y + pad,
                hazard.rect.width - pad * 2,
                hazard.rect.height - pad * 2};

            Rectangle playerRect{
                playerEntity.pos.x,
                playerEntity.pos.y,
                playerEntity.rect.width,
                playerEntity.rect.height};

            if (CheckCollisionRecs(hazardRect, playerRect))
            {
                gameOver = true;
            }
        }

        BeginDrawing();
        ClearBackground(WHITE);

        DrawTextureEx(background, {backgroundPos.x, backgroundPos.y}, 0.0, 2.0, WHITE);
        DrawTextureEx(background, {background.width * 2 + backgroundPos.x, backgroundPos.y}, 0.0, 2.0, WHITE);

        DrawTextureEx(midground, {midgroundPos.x, midgroundPos.y}, 0.0, 2.0, WHITE);
        DrawTextureEx(midground, {midground.width * 2 + midgroundPos.x, midgroundPos.y}, 0.0, 2.0, WHITE);

        DrawTextureEx(foreground, {foregroundPos.x, foregroundPos.y}, 0.0, 2.0, WHITE);
        DrawTextureEx(foreground, {foreground.width * 2 + foregroundPos.x, foregroundPos.y}, 0.0, 2.0, WHITE);

        if (gameOver == false)
        {
            if (playerEntity.pos.x <= finishLine)
            {
                for (int i = 0; i < hazardAmount; i++)
                {
                    DrawTextureRec(hazardSprite, hazards[i].rect, hazards[i].pos, WHITE);
                }

                DrawTextureRec(playerSprite, playerEntity.rect, playerEntity.pos, WHITE);
            }
            else
            {
                textSize = MeasureText("Your Winner!", 50);
                DrawText("Your Winner!", ((int)windowWidth / 2 - (textSize / 2)), 50, 50, WHITE);
            }
        }
        else
        {
                textSize = MeasureText("Game Over!", 50);
                DrawText("Game Over!", ((int)windowWidth / 2 - (textSize / 2)), 50, 50, WHITE);
        }

        EndDrawing();
    }

    // Unload resources...
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    UnloadTexture(playerSprite);
    UnloadTexture(hazardSprite);
    CloseWindow();
}
