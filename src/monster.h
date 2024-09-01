#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <raylib.h>
#include "envitem.cpp"

#define G 500
#define MONSTER_JUMP_SPD 370.0f
#define MONSTER_HOR_SPD 200.0f

class Monster {
private:
  int vchute = 0;
public:
  Vector2 position;
  float speed;

  Monster(Vector2 position);
  void Draw();
  void Update(EnvItem *envItems, int envItemsLength, float delta);

};


#endif
