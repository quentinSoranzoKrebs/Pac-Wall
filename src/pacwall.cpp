#include <raylib.h>
#include <iostream>
#include <string>
#include "raymath.h"
//#include "player.h"
#include "version.h"

using namespace std;

#define G 400
#define PLAYER_JUMP_SPD 350.0f
#define PLAYER_HOR_SPD 200.0f

void init() {
	//init
}


typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;


class Player {
private:
	int vchute = 0;

public:
	Vector2 position;
  float speed;
  bool canJump;
	Player(Vector2 position,float speed,bool canJump) : position(position),speed(speed),canJump(canJump) {}

	void draw() {
		Rectangle playerRect = { position.x - 20, position.y - 40, 40.0f, 40.0f };
		//DrawRectangleRec(playerRect, YELLOW);
    DrawCircle(position.x, position.y - 20, 20, YELLOW);
    DrawCircle(position.x + 10, position.y - 28, 3, BLACK);
	}


	void UpdatePlayer(EnvItem *envItems, int envItemsLength, float delta) {
		if (IsKeyDown(KEY_LEFT)) position.x -= PLAYER_HOR_SPD*delta;
		if (IsKeyDown(KEY_RIGHT)) position.x += PLAYER_HOR_SPD*delta;
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
    const int screenWidth = 800;
    const int screenHeight = 450;

	string tit = "PacWall v";

	string version = "1";

	string stitle = tit + version;

	char *title = stitle.data();

	cout << title << endl;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, title);

	SetTargetFPS(60);

	Player player((Vector2){ 400, 280 },0,false);

    EnvItem envItems[] = {
        //{{ 0, 0, 1000, 400 }, 0, GRAY },
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

				DrawText("Congrats! You created your first window!", 190, 200, 20, WHITE);

				//DrawRectangle(0, screenHeight*0.8, screenWidth, 100, BLUE);

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
