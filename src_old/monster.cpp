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
    //cout << distance_perso << endl;
	direct = player_position;
  }
}

void Monster::Update(EnvItem *envItems, int envItemsLength, float delta, Vector2 player_position) {

	//déplacements
  detect_perso(player_position);
  // collisions(envItems, envItemsLength, delta);
  Vector2 distance = (Vector2){direct.x - position.x, direct.y - position.y};
  float norm = sqrtf(distance.x * distance.x + distance.y * distance.y);
  Vector2 direction = (Vector2){distance.x / norm, distance.y / norm};
  Vector2 bullet_vector = (Vector2){direction.x * sqrtf(2), direction.y * sqrtf(2)};
  //cout << bullet_vector.x << bullet_vector.y << endl;
  
  position.x += bullet_vector.x;
  position.y += bullet_vector.y;

}
