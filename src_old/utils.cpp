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

#include "utils.h"

// Fonction pour calculer la distance entre deux points
float GetDistance(Vector2 point1, Vector2 point2) {
    return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}

// Fonction qui vérifie si l'utilisateur a tapé sur l'écran
bool isScreenTapped() {
    int touchCount = GetTouchPointCount();  // Nombre de doigts actuellement sur l'écran
    cout << touchCount << endl;

    // S'il y a au moins un doigt sur l'écran
    if (touchCount > 0) {
        // Parcourt chaque point de contact (chaque doigt)
        for (int i = 0; i < touchCount; i++) {
            Vector2 touchPosition = GetTouchPosition(i);  // Position du doigt i

            // Si la position est valide, alors un doigt est bien sur l'écran
            if (touchPosition.x != -1 && touchPosition.y != -1) {
                return true;  // Un tap ou un contact supplémentaire est détecté
            }
        }
    }

    return false;  // Aucun nouveau contact détecté
}
