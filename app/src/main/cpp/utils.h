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

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include "math.h"
#include "raymob.h"

using namespace std;

// Fonction pour calculer la distance entre deux points
float GetDistance(Vector2 point1, Vector2 point2);
bool isScreenTapped();

#endif