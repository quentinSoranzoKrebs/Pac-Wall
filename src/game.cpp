/*
 * Copyright (C) 2024 Quentin Soranzo Krebs
 *
 * This file is part of Pac-Wall.
 *
 * Pac-Wall is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Pac-Wall is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Pac-Wall. If not, see <http://www.gnu.org/licenses/>.
 */

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


    load_map((string)"../data/map.json");

    /*envItems.push_back({{ 0, 0, 5000, 1000 }, 0, BLACK });
    envItems.push_back({{ 400, 1100, 100, 20 }, 1, GRAY });
    envItems.push_back({{ 0, 1400, 5000, 20 }, 1, GRAY });
    envItems.push_back({{ 500, 1360, 40, 40 }, 1, BLUE });
    envItems.push_back({{ 300, 1380, 40, 20 }, 1, GRAY });
    envItems.push_back({{ 400, 1360, 40, 20 }, 1, GRAY });
    envItems.push_back({{ 300, 1200, 400, 20 }, 1, GRAY });
    envItems.push_back({{ 250, 1300, 100, 20 }, 1, GRAY });
    envItems.push_back({{ 650, 1300, 100, 20 }, 1, GRAY });*/

	envItemsLength = envItems.size();

    // init camera
    //Camera2D camera = { 0 };
    camera.target = ListPlayer[0].position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.1f;
}

void Game::Update()
{
        float deltaTime = GetFrameTime();

        // camera.zoom += ((float)GetMouseWheelMove()*0.05f);

        // if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        // else if (camera.zoom < 0.25f) camera.zoom = 0.25f;



        //camera.zoom = 1.1f;
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

            for (int i = 0; i < envItemsLength; i++) 
            {   
                //DrawRectangleRec(envItems[i].rect, RED);
                if (envItems[i].solid)
                {
                    DrawRectangleRec(envItems[i].rect, envItems[i].color);

                } else if (!envItems[i].solid) 
                {
                    Rectangle rect = { envItems[i].rect.x + 7, envItems[i].rect.y + 7, envItems[i].rect.width - 14, envItems[i].rect.height - 14 };
                    DrawRectangleRoundedLines(rect, 1, 60, 7, envItems[i].color);;
                }
            }

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

void Game::load_map(string map)
{
    // Ouvrir le fichier JSON
    std::ifstream input_file(map);
    if (!input_file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << map <<  ".json" << std::endl;
    }

    // Lire le contenu du fichier JSON
    nlohmann::json j;
    input_file >> j;

    // Fermer le fichier
    input_file.close();

    // Accéder aux données JSON
    /*std::cout << "name: " << j["map"]["name"] << std::endl;
    std::cout << "description: " << j["map"]["description"] << std::endl;
    std::cout << "dimension width: " << j["map"]["dimensions"]["width"] << std::endl;
    std::cout << "list: ";*/
    

    // Récupérer les données de j["map"]["terrain"][0][0]
    int x = 0;
    int y = 0;
    int width = j["map"]["dimensions"]["width"];
    int height = j["map"]["dimensions"]["height"];

    // Créer un Rectangle avec ces données
    Rectangle rect = { (float)x, (float)y, (float)width, (float)height };
    std::cout << x << "," << y << "," << width << "," << height << std::endl;

    // Récupérer la couleur de l'item
    std::vector<unsigned char> background_color = j["map"]["settings"]["background_color"];
    Color color = (Color){background_color[0],background_color[1],background_color[2],background_color[3]};

    // Ajouter le fond de la map
    envItems.push_back({{0,0,1420,5000},0,color,true});

    for (const auto& elem : j["map"]["terrain"]) {
        //std::cout << elem << " ";

        // Récupérer les données de j["map"]["terrain"][0][0]
        int x = elem[0]["x"];
        int y = elem[0]["y"];
        int width = elem[0]["width"];
        int height = elem[0]["height"];

        // Récupérer la couleur de l'item
        Color color = (Color){elem[2][0],elem[2][1],elem[2][2],elem[2][3]};

        // Créer un Rectangle avec ces données
        Rectangle rect = { (float)x, (float)y, (float)width, (float)height };

        //créer l'item
        envItems.push_back({rect,elem[1],color});
    }
    std::cout << std::endl;
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
}