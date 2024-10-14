/*
 * Copyright (C) 2024 Quentin Soranzo Krebs
 *
 * This file is part of Pac-Wall.
 *
 * [Nom de ton projet] is free software: you can redistribute it and/or modify
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

#include "raymob.h"
#include <iostream>
#include <string>
#include "envitem.cpp"
#include "perso.h"
#include "monster.h"
#include "raymath.h"
#include "math.h"
#include "joystick.h"
#include "version.h"

using namespace std;


void init() {
	//init
}

// Fonction pour calculer la distance entre deux points
float GetDistance(Vector2 point1, Vector2 point2) {
    return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}

void UpdateCameraCenterInsideMap(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);

int main(void) {

    std::cout << "Project version: "
              << PROJECT_VERSION_MAJOR << "."
              << PROJECT_VERSION_MINOR << "."
              << PROJECT_VERSION_PATCH << std::endl;


  // Initialization
  //--------------------------------------------------------------------------------------
  //const int screenWidth = 1366;
  //const int screenHeight = 768;

  const int screenWidth = 1150;
  const int screenHeight = 600;

	string tit = "PacWall v2";

	string version = "1";

	string stitle = tit + version;

	const char *title = stitle.data();

	cout << title << endl;


  InitWindow(screenWidth, screenHeight, title);
  //SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  //ToggleFullscreen();

	SetTargetFPS(60);

    Joystick joystik1((Vector2){150, 300}, 50.0f);

    // Position et rayon du joystick
    Vector2 joystickDefaultPosition = {150, 300};
    Vector2 joystickBasePosition = {150, 300};  // Position de base du joystick
    float joystickRadius = 50.0f;               // Rayon de base du joystick
    Vector2 joystickCurrentPosition = joystickBasePosition;  // Position actuelle du contrôleur (cercle interne)
    bool clic = false;

    // Variables pour gérer l'état du joystick
    bool isTouchingJoystick = false;  // Savoir si l'utilisateur touche le joystick
    float maxDistanceFromBase = 40.0f;  // Distance maximale que le cercle interne peut parcourir


    Player player((Vector2){ 400, 1280 },0,false);
  Monster mstr((Vector2){ 100, 1280 },(Vector2){ 100, 1200 },(Vector2){ 100, 1280 });

  EnvItem envItems[] = {
      {{ 0, 0, 5000, 1000 }, 0, BLACK },
      {{ 400, 1100, 100, 10 }, 1, GRAY },
      {{ 0, 1400, 1000, 200 }, 1, GRAY },
      {{ 500, 1360, 40, 40 }, 1, BLUE },
      {{ 300, 1380, 40, 20 }, 1, GRAY },
      {{ 400, 1360, 40, 20 }, 1, GRAY },
      {{ 300, 1200, 400, 10 }, 1, GRAY },
      {{ 250, 1300, 100, 10 }, 1, GRAY },
      {{ 650, 1300, 100, 10 }, 1, GRAY }
    };

	int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);

  //Monster

    Camera2D camera = { 0 };
    camera.target = player.position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.3f;

	Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };

	while (!WindowShouldClose()) {


        float deltaTime = GetFrameTime();

        camera.zoom += ((float)GetMouseWheelMove()*0.05f);

        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.25f) camera.zoom = 0.25f;

        // Gestion des interactions tactiles/souris
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 touchPosition = GetMousePosition();

            // Si l'utilisateur touche à l'intérieur du cercle de base
            //if (CheckCollisionPointCircle(touchPosition, joystickBasePosition, joystickRadius)) {
            if (isTouchingJoystick == false) {
                joystickBasePosition = touchPosition;
                isTouchingJoystick = true;
            }

            // Calculer la distance entre la base du joystick et la position du toucher
            float distance = GetDistance(joystickBasePosition, touchPosition);

            // Limiter la distance pour ne pas sortir du cercle
            if (distance <= maxDistanceFromBase) {
                joystickCurrentPosition = touchPosition;  // Déplacer le joystick
            } else {
                // Normaliser la position du joystick pour qu'il reste dans le cercle
                float angle = atan2(touchPosition.y - joystickBasePosition.y, touchPosition.x - joystickBasePosition.x);
                joystickCurrentPosition.x = joystickBasePosition.x + cos(angle) * maxDistanceFromBase;
                joystickCurrentPosition.y = joystickBasePosition.y + sin(angle) * maxDistanceFromBase;
            }
            //}
        } else {
            isTouchingJoystick = false;
            joystickBasePosition = joystickDefaultPosition;
            joystickCurrentPosition = joystickBasePosition;  // Réinitialiser le joystick à la position de base
        }

        // Calculer le vecteur de direction basé sur le déplacement du joystick
        Vector2 direction = { joystickCurrentPosition.x - joystickBasePosition.x, joystickCurrentPosition.y - joystickBasePosition.y };

        // Calculer la longueur du vecteur direction pour l'utiliser pour le déplacement du joueur
        float magnitude = GetDistance(joystickBasePosition, joystickCurrentPosition);
        if (magnitude > 0) {
            direction.x /= magnitude;
            direction.y /= magnitude;
        }



        // Utiliser la direction pour déplacer le joueur, ici juste un cercle de test
        Vector2 playerPosition = {400 + direction.x * 5, 225 + direction.y * 5};

        player.UpdatePlayer(envItems, envItemsLength, deltaTime, (Vector2){ screenWidth, screenHeight});
        mstr.Update(envItems, envItemsLength, deltaTime);
        mstr.detect_perso(player.position);
        //cout << player.position.x << "  " << player.position.y << endl;

        // Camera target follows player
        UpdateCameraCenterInsideMap(&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            // Dessiner la base du joystick
            DrawCircleV(joystickBasePosition, joystickRadius, (Color){130,130,130,120});

            // Dessiner le cercle mobile du joystick (la position du pouce)
            DrawCircleV(joystickCurrentPosition, 30, (Color){150,150,150,120});

            // Dessiner le joueur (un cercle pour cet exemple)
            DrawCircleV(playerPosition, 20, RED);

            BeginMode2D(camera);

                for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color);

                //DrawText("Congrats! You created your first window!", 190, 200, 20, WHITE);


                player.draw();

                mstr.Draw();

                //DrawLine((int)camera.target.x, -screenHeight*10, (int)camera.target.x, screenHeight*10, GREEN);
                //DrawLine(-screenWidth*10, (int)camera.target.y, screenWidth*10, (int)camera.target.y, GREEN);

            EndMode2D();

        EndDrawing();
        //--------------

	}

	CloseWindow();

	return 0;

}

void UpdateCameraCenterInsideMap(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
    camera->target = player->position;
    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
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
