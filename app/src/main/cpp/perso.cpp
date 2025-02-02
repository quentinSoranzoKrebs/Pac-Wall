#include "perso.h"

Player::Player(Vector2 position,float speed,bool canJump):
  position(position),
  speed(speed),
  canJump(canJump) {
}

void Player::draw() {
  Rectangle playerRect = { position.x - 20, position.y - 40, 40.0f, 40.0f };
  if (direct=="right") {
    DrawCircleSector((Vector2){position.x, position.y - 20},20.0f,25.0f,360-25,50,YELLOW);
  } else {
    DrawCircleSector((Vector2){position.x, position.y - 20},20.0f,-135,135,50,YELLOW);
  }
  DrawCircle(position.x, position.y - 30, 3, BLACK);
  DrawCircle(position.x, position.y, 1, RED);
}

void Player::UpdatePlayer(EnvItem *envItems, int envItemsLength, float delta, Vector2 direction, bool jumpclic) {

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


  // Gestion des collisions horizontales avec clavier
  Vector2 oldPosition = position;
  if (IsKeyDown(KEY_RIGHT)) position.x += PLAYER_HOR_SPD * delta;
  if (IsKeyDown(KEY_LEFT)) position.x -= PLAYER_HOR_SPD * delta;
  if (direction.x > 0 || direction.x < 0) position.x += PLAYER_HOR_SPD * direction.x * delta;

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
  if (IsKeyDown(KEY_SPACE) && canJump || jumpclic && canJump) {
    speed = -PLAYER_JUMP_SPD;
    canJump = false;
  }
}
