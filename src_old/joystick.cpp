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

#include "joystick.h"

Joystick::Joystick(Vector2 joystickDefaultPosition, float joystickRadius):
    joystickDefaultPosition(joystickDefaultPosition),
    joystickBasePosition(joystickDefaultPosition),
    joystickCurrentPosition(joystickDefaultPosition),
    isTouchingJoystick(false),
    maxDistanceFromBase(40.0f),
    joystickRadius(joystickRadius) {
}

void Joystick::draw() {
    // Dessiner la base du joystick
    DrawCircleV(joystickBasePosition, joystickRadius, (Color){130,130,130,120});

    // Dessiner le cercle mobile du joystick (la position du pouce)
    DrawCircleV(joystickCurrentPosition, 30, (Color){150,150,150,120});
}

void Joystick::Update() {
    // Gestion des interactions tactiles
    int touchCount = GetTouchPointCount();

    // Gestion des interactions tactiles/souris
    if (touchCount > 0 && GetTouchPosition(0).x < 500) {
        Vector2 touchPosition = GetTouchPosition(0);

        // Si l'utilisateur touche à l'intérieur du cercle de base
        //if (CheckCollisionPointCircle(touchPosition, joystickBasePosition, joystickRadius)) {
        if (!isTouchingJoystick) {
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
}

Vector2 Joystick::direction() {

    // Calculer le vecteur de direction basé sur le déplacement du joystick
    Vector2 direct = { joystickCurrentPosition.x - joystickBasePosition.x, joystickCurrentPosition.y - joystickBasePosition.y };

    // Calculer la longueur du vecteur direction pour l'utiliser pour le déplacement du joueur
    float magnitude = GetDistance(joystickBasePosition, joystickCurrentPosition);
    if (magnitude > 0) {
        direct.x /= magnitude;
        direct.y /= magnitude;
    }
    return direct;
}