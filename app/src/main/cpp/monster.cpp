#include "monster.h"

// constructeur pour monstres basic
Monster::Monster(Vector2 position):
  position(position) {
    type = "static";
}

// constructeur pour monstres qui se déplacent
Monster::Monster(Vector2 position , Vector2 p1, Vector2 p2):
  position(position),
  p1(p1),
  p2(p2) {
    type = "round";
    direct = p1;
}

void Monster::Draw() {
	DrawCircleSector((Vector2){position.x, position.y-20},20.0f,-180,0,50,BLUE);
	DrawCircle(position.x, position.y, 1, RED);
	DrawRectangle(position.x-20, position.y-20, 40, 20, BLUE);

}

void Monster::detect_perso(Vector2 player_position) {
  float distance_perso = Vector2Distance(player_position,position);
  if (distance_perso < 250) {
    cout << distance_perso << endl;
	direct = player_position;
  }
}

void Monster::collisions(EnvItem *envItems, int envItemsLength, float delta) {

  	//collisitons

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
      /*position.y += speed*delta;
      speed += G*delta;
  	 //canJump = false;*/
    }


    // Gestion des collisions horizontales
    Vector2 oldPosition = position;

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
}

void Monster::Update(EnvItem *envItems, int envItemsLength, float delta) {

	//déplacements
  collisions(envItems, envItemsLength, delta);
  Vector2 distance = (Vector2){direct.x - position.x, direct.y - position.y};
  float norm = sqrtf(distance.x * distance.x + distance.y * distance.y);
  Vector2 direction = (Vector2){distance.x / norm, distance.y / norm};
  Vector2 bullet_vector = (Vector2){direction.x * sqrtf(2), direction.y * sqrtf(2)};
  cout << bullet_vector.x << bullet_vector.y << endl;
  
  position.x += bullet_vector.x;
  position.y += bullet_vector.y;

}
