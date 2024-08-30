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
#include <raylib.h>
#include "envitem.cpp"

#define G 500
#define PLAYER_JUMP_SPD 370.0f
#define PLAYER_HOR_SPD 200.0f

using namespace std;

class Player {
private:
	int vchute = 0;
  string direct = "right";
  bool rcondit = false;
public:
	Vector2 position;
  float speed;
  bool canJump;
	Player(Vector2 position,float speed,bool canJump) : position(position),speed(speed),canJump(canJump) {}

	void draw() {
		Rectangle playerRect = { position.x - 20, position.y - 40, 40.0f, 40.0f };
    if (direct=="right") {
      DrawCircleSector((Vector2){position.x, position.y - 20},20.0f,25.0f,360-25,50,YELLOW);
    } else {
      DrawCircleSector((Vector2){position.x, position.y - 20},20.0f,-135,135,50,YELLOW);
    }
    DrawCircle(position.x, position.y - 30, 3, BLACK);
    DrawCircle(position.x, position.y, 1, RED);
	}


	void UpdatePlayer(EnvItem *envItems, int envItemsLength, float delta) {

		bool hitObstacle = false;
    bool hitObstacleHorizontal = false;
		for (int i = 0; i < envItemsLength; i++)
		{
			EnvItem *ei = envItems + i;
			Vector2 *p = &(position);
			if (ei->blocking &&
				ei->rect.x <= p->x + 20 &&
				ei->rect.x + ei->rect.width >= p->x - 20 &&
				ei->rect.y >= p->y &&
				ei->rect.y <= p->y + speed*delta)
			{
				hitObstacle = true;
				speed = 0.0f;
				p->y = ei->rect.y;
        ei->color = RED;
				break;
			}
      else
      {
        ei->color = ei->origin_color;
      }
		}

		if (!hitObstacle)
		{
			position.y += speed*delta;
			speed += G*delta;
			canJump = false;
		}
		else canJump = true;


    // Gestion des collisions horizontales
    Vector2 oldPosition = position;
    if (IsKeyDown(KEY_RIGHT)) position.x += PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_LEFT)) position.x -= PLAYER_HOR_SPD * delta;

    for (int i = 0; i < envItemsLength; i++) {
        EnvItem *ei = &envItems[i];
        if (ei->blocking) {
            if (ei->rect.x <= position.x + 20 &&
                ei->rect.x + ei->rect.width >= position.x - 20 &&
                ei->rect.y < position.y &&
                ei->rect.y + ei->rect.height >= position.y-40) {

                hitObstacleHorizontal = true;
                position = oldPosition;  // Revenir à l'ancienne position pour éviter l'intersection
                ei->color = GREEN;
        				break;
        		}
            else
            {
                ei->color = ei->origin_color;
            }

        }
    }
  	if (IsKeyDown(KEY_SPACE) && canJump) {
  		speed = -PLAYER_JUMP_SPD;
			canJump = false;
  	}
	}

};

#endif
