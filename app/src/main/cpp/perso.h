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

#ifndef PERSO_H
#define PERSO_H

#include <iostream>
#include <raymob.h>
#include "envitem.cpp"

#define G 500
#define PLAYER_JUMP_SPD 370.0f
#define PLAYER_HOR_SPD 200.0f

using namespace std;

class Player {
private:
	int vchute = 0;
  string direct = "right";
public:
	Vector2 position;
  float speed;
  bool canJump;
	Player(Vector2 position,float speed,bool canJump);

	void draw();

	void UpdatePlayer(EnvItem *envItems, int envItemsLength, float delta,Vector2 win);

};

#endif
