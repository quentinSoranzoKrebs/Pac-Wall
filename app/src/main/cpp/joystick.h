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

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <iostream>
#include <raymob.h>


class Joystick {
private:
    // Position et rayon du joystick
    Vector2 joystickDefaultPosition{};
    Vector2 joystickBasePosition{};  // Position de base du joystick
    float joystickRadius{};               // Rayon de base du joystick
    Vector2 joystickCurrentPosition{};  // Position actuelle du contrôleur (cercle interne) 40.0f

    // Variables pour gérer l'état du joystick
    bool isTouchingJoystick{};  // Savoir si l'utilisateur touche le joystick
    float maxDistanceFromBase{};  // Distance maximale que le cercle interne peut parcourir
public:
    Joystick(Vector2 joystickDefaultPosition, float joystickRadius);

    void draw();

    void Update();

};

#endif