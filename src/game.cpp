#include "game.h"

Game::Game(int screenWidth, int screenHeight, string title)
: screenWidth(screenWidth), screenHeight(screenHeight), title(title.data())
{
    Init();
}

Game::~Game()
{
}

void Game::Run()
{
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
}

void Game::Init()
{
    const int screenWidth = 1150;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(60);

    // set players
    ListPlayer.push_back(Player((Vector2){ 400, 1280 },0,false));
    ListMstr.push_back(Monster((Vector2){ 100, 1280 },(Vector2){ 100, 1200 },(Vector2){ 100, 1280 }));


    envItems.push_back({{ 0, 0, 5000, 1000 }, 0, BLACK });
    envItems.push_back({{ 400, 1100, 100, 10 }, 1, GRAY });
    envItems.push_back({{ 0, 1400, 1000, 200 }, 1, GRAY });
    envItems.push_back({{ 500, 1360, 40, 40 }, 1, BLUE });
    envItems.push_back({{ 300, 1380, 40, 20 }, 1, GRAY });
    envItems.push_back({{ 400, 1360, 40, 20 }, 1, GRAY });
    envItems.push_back({{ 300, 1200, 400, 10 }, 1, GRAY });
    envItems.push_back({{ 250, 1300, 100, 10 }, 1, GRAY });
    envItems.push_back({{ 650, 1300, 100, 10 }, 1, GRAY });


    // set environment
    /*EnvItem envItems[9] = {
        {{ 0, 0, 5000, 1000 }, 0, BLACK },
        {{ 400, 1100, 100, 10 }, 1, GRAY },
        {{ 0, 1400, 1000, 200 }, 1, GRAY },
        {{ 500, 1360, 40, 40 }, 1, BLUE },
        {{ 300, 1380, 40, 20 }, 1, GRAY },
        {{ 400, 1360, 40, 20 }, 1, GRAY },
        {{ 300, 1200, 400, 10 }, 1, GRAY },
        {{ 250, 1300, 100, 10 }, 1, GRAY },
        {{ 650, 1300, 100, 10 }, 1, GRAY }
    };*/

	//int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);

    // init camera
    Camera2D camera = { 0 };
    camera.target = ListPlayer[0].position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 6.0f;
}

void Game::Update()
{
        float deltaTime = GetFrameTime();

        camera.zoom += ((float)GetMouseWheelMove()*0.05f);

        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.25f) camera.zoom = 0.25f;


        //joystik1.Update();

        //Vector2 direction = joystik1.direction();
        //cout << direction.x << direction.y << endl;

        //for (const auto &player : ListPlayer) {
        ListPlayer[0].Update(envItems, envItemsLength, deltaTime, (Vector2){0,0}, false);
        //}
        //for (const auto &mstr : ListMstr) {
        ListMstr[0].Update(envItems, envItemsLength, deltaTime, ListPlayer[0].position);
        //}
        //cout << player.position.x << "  " << player.position.y << endl;

        // Camera target follows player
        UpdateCameraCenterInsideMap(&camera, &ListPlayer[0], envItems, envItemsLength, deltaTime, screenWidth, screenHeight);
}

void Game::Draw()
{
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(BLACK);

        BeginMode2D(camera);

            for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color);

            //DrawText("Congrats! You created your first window!", 190, 200, 20, WHITE);

            ListPlayer[0].Draw();

            ListMstr[0].Draw();

            //DrawLine((int)camera.target.x, -screenHeight*10, (int)camera.target.x, screenHeight*10, GREEN);
            //DrawLine(-screenWidth*10, (int)camera.target.y, screenWidth*10, (int)camera.target.y, GREEN);

        EndMode2D();
                
        //joystik1.draw();
        //JumpButton.draw();

    EndDrawing();
    //--------------
}

void Game::Cleanup()
{
}

void Game::UpdateCameraCenterInsideMap(Camera2D *camera, Player *player, vector<EnvItem> envItems, int envItemsLength, float delta, int width, int height)
{
    camera->target = player->position;
    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem* ei = &envItems[i];
        minX = fminf(ei->rect.x, minX);
        maxX = fmaxf(ei->rect.x + ei->rect.width, maxX);
        minY = fminf(ei->rect.y, minY);
        maxY = fmaxf(ei->rect.y + ei->rect.height, maxY);
    }

    Vector2 max = GetWorldToScreen2D((Vector2){ maxX, maxY }, *camera);
    Vector2 min = GetWorldToScreen2D((Vector2){ minX, minY }, *camera);

    if (max.x < width) camera->offset.x = width - (max.x - width/2);
    if (max.y < height) camera->offset.y = height - (max.y - height/2);
    if (min.x > 0) camera->offset.x = width/2 - min.x;
    if (min.y > 0) camera->offset.y = height/2 - min.y;
    cout << camera->zoom << endl;
}