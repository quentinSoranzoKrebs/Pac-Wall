#include "monster.h"

Monster::Monster(Vector2 position):
  position(position) {
}

void Monster::Draw() {
  //DrawRectangleRec((int)position.x, (int)position.y,40,40,WHITE);
	DrawRectangle(position.x, position.y, 40, 40, RED);
}
