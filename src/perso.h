#ifndef PERSO_H
#define PERSO_H

#include <iostream>
#include <raylib.h>

using namespace std;

class Player {
private:
	int vchute;
  string direct;
public:
	Vector2 position;
  float speed;
  bool canJump;

	void draw();


	void UpdatePlayer(EnvItem *envItems, int envItemsLength, float delta);

};

#endif
