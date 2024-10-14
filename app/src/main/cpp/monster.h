#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <raymob.h>
#include "raymath.h"
#include "envitem.cpp"
#include <cmath>

using namespace std;

#define G 0
#define MONSTER_JUMP_SPD 370.0f
#define MONSTER_HOR_SPD 200.0f

class Monster {
private:
  int vchute = 0;
  bool attack;
  float distance_perso;
  Vector2 p1;
  Vector2 p2;
  string type;
  Vector2 direct;
public:
  Vector2 position;
  float speed;

  Monster(Vector2 position);
  Monster(Vector2 position, Vector2 p1, Vector2 p2);

  void Draw();
  void Update(EnvItem *envItems, int envItemsLength, float delta);
  void detect_perso(Vector2 player_position);
  void collisions(EnvItem *envItems, int envItemsLength, float delta);


};


#endif
