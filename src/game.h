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

#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <iostream>
#include <string>
#include "envitem.cpp"
#include "perso.h"
#include "monster.h"
#include "raymath.h"
#include "joystick.h"
#include "button.h"
#include "version.h"
#include "utils.h"
#include <vector>

using namespace std;

class Game {
public:
    // Constructeur et destructeur
    Game(int screenWidth, int screenHeight, string title);
    ~Game();
    
    // Méthode principale pour lancer le jeu
    void Run();

private:
    // Variables de jeu
    int screenWidth;
    int screenHeight;
    const char* title;
    vector<Player> ListPlayer;
    vector<Monster> ListMstr;
    vector<EnvItem> envItems;
    int envItemsLength = 9;
    Camera2D camera;
    
    
    // Méthodes internes
    void UpdateCameraCenterInsideMap(Camera2D *camera, Player *player, vector<EnvItem> envItems, int envItemsLength, float delta, int width, int height);
    void Init();
    void Update();
    void Draw();
    void Cleanup();
    
    // Autres éléments du jeu (joueur, ennemis, etc.)
    // Exemple: Vector2 playerPosition;
};
#endif