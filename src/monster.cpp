#include "monster.h"

Monster::Monster(Vector2 position):
  position(position) {
}

void Monster::Draw() {
  DrawRectangleRec((position.x, position.y,40,40),WHITE);
}
