#include <raylib.h>
#include <iostream>
#include <string>
#include "raymath.h"
//#include "player.h"
#include "version.h"

using namespace std;

#define G 500
#define PLAYER_JUMP_SPD 370.0f
#define PLAYER_HOR_SPD 200.0f

void init() {
	//init
}


typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;

/*class EnvItem {
public:
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;*/


class Player {
private:
	int vchute = 0;
  string direct = "right";
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
		if (IsKeyDown(KEY_LEFT)) {
      position.x -= PLAYER_HOR_SPD*delta;
      direct = "left";
    }
		if (IsKeyDown(KEY_RIGHT)) {
      position.x += PLAYER_HOR_SPD*delta;
      direct = "right";
    }
		if (IsKeyDown(KEY_SPACE) && canJump)
		{
			speed = -PLAYER_JUMP_SPD;
			canJump = false;
		}

		bool hitObstacle = false;
		for (int i = 0; i < envItemsLength; i++)
		{
			EnvItem *ei = envItems + i;
			Vector2 *p = &(position);
			if (ei->blocking &&
				ei->rect.x <= p->x &&
				ei->rect.x + ei->rect.width >= p->x &&
				ei->rect.y >= p->y &&
				ei->rect.y <= p->y + speed*delta)
			{
				hitObstacle = true;
				speed = 0.0f;
				p->y = ei->rect.y;
				break;
			}
		}

		if (!hitObstacle)
		{
			position.y += speed*delta;
			speed += G*delta;
			canJump = false;
		}
		else canJump = true;
	}

};

int main(void) {

    std::cout << "Project version: "
              << PROJECT_VERSION_MAJOR << "."
              << PROJECT_VERSION_MINOR << "."
              << PROJECT_VERSION_PATCH << std::endl;


  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 1366;
  const int screenHeight = 768;

	string tit = "PacWall v";

	string version = "1";

	string stitle = tit + version;

	char *title = stitle.data();

	cout << title << endl;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, title);
  ToggleFullscreen();

	SetTargetFPS(60);

	Player player((Vector2){ 400, 280 },0,false);

    EnvItem envItems[] = {
      //{{ 0, 0, 1000, 400 }, 0, GRAY },
        {{ 400, 100, 100, 10 }, 1, GRAY },
        {{ 0, 400, 1000, 200 }, 1, GRAY },
        {{ 300, 200, 400, 10 }, 1, GRAY },
        {{ 250, 300, 100, 10 }, 1, GRAY },
        {{ 650, 300, 100, 10 }, 1, GRAY }
    };

	int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);

    Camera2D camera = { 0 };
    camera.target = player.position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

	Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };

	while (!WindowShouldClose()) {


        float deltaTime = GetFrameTime();

        player.UpdatePlayer(envItems, envItemsLength, deltaTime);
        // Camera target follows player
        camera.target = (Vector2){ player.position.x + 20, player.position.y + 20 };

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode2D(camera);

                for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color);

                //DrawText("Congrats! You created your first window!", 190, 200, 20, WHITE);


                player.draw();

                //DrawLine((int)camera.target.x, -screenHeight*10, (int)camera.target.x, screenHeight*10, GREEN);
                //DrawLine(-screenWidth*10, (int)camera.target.y, screenWidth*10, (int)camera.target.y, GREEN);

            EndMode2D();

        EndDrawing();
        //--------------

	}

	CloseWindow();

	return 0;

}
