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
    Color origin_color = color;
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
  bool rcondit = false;
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


    // Gestion des collisions horizontales
    Vector2 oldPosition = position;
    if (IsKeyDown(KEY_RIGHT)) position.x += PLAYER_HOR_SPD * delta;
    if (IsKeyDown(KEY_LEFT)) position.x -= PLAYER_HOR_SPD * delta;

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
  	if (IsKeyDown(KEY_SPACE) && canJump) {
  		speed = -PLAYER_JUMP_SPD;
			canJump = false;
  	}
	}

};


void UpdateCameraCenterInsideMap(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height);

int main(void) {

    std::cout << "Project version: "
              << PROJECT_VERSION_MAJOR << "."
              << PROJECT_VERSION_MINOR << "."
              << PROJECT_VERSION_PATCH << std::endl;


  // Initialization
  //--------------------------------------------------------------------------------------
  //const int screenWidth = 1366;
  //const int screenHeight = 768;

  const int screenWidth = 1150;
  const int screenHeight = 600;

	string tit = "PacWall v";

	string version = "1";

	string stitle = tit + version;

	char *title = stitle.data();

	cout << title << endl;

	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, title);
  //ToggleFullscreen();

	SetTargetFPS(60);

	Player player((Vector2){ 400, 1280 },0,false);

    EnvItem envItems[] = {
        {{ 0, 0, 5000, 1000 }, 0, BLACK },
        {{ 400, 1100, 100, 10 }, 1, GRAY },
        {{ 0, 1400, 1000, 200 }, 1, GRAY },
        {{ 500, 1360, 40, 40 }, 1, BLUE },
        {{ 300, 1380, 40, 20 }, 1, GRAY },
        {{ 400, 1360, 40, 20 }, 1, GRAY },
        {{ 300, 1200, 400, 10 }, 1, GRAY },
        {{ 250, 1300, 100, 10 }, 1, GRAY },
        {{ 650, 1300, 100, 10 }, 1, GRAY }
    };

	int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);

    Camera2D camera = { 0 };
    camera.target = player.position;
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.3f;

	Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };

	while (!WindowShouldClose()) {


        float deltaTime = GetFrameTime();

        camera.zoom += ((float)GetMouseWheelMove()*0.05f);

        if (camera.zoom > 3.0f) camera.zoom = 3.0f;
        else if (camera.zoom < 0.25f) camera.zoom = 0.25f;

        player.UpdatePlayer(envItems, envItemsLength, deltaTime);

        // Camera target follows player
        UpdateCameraCenterInsideMap(&camera, &player, envItems, envItemsLength, deltaTime, screenWidth, screenHeight);


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

void UpdateCameraCenterInsideMap(Camera2D *camera, Player *player, EnvItem *envItems, int envItemsLength, float delta, int width, int height)
{
    camera->target = player->position;
    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        minX = fminf(ei->rect.x, minX);
        maxX = fmaxf(ei->rect.x + ei->rect.width, maxX);
        minY = fminf(ei->rect.y, minY);
        maxY = fmaxf(ei->rect.y + ei->rect.height, maxY);
    }

    Vector2 max = GetWorldToScreen2D((Vector2){ maxX, maxY }, *camera);
    Vector2 min = GetWorldToScreen2D((Vector2){ minX, minY }, *camera);

    if (max.x < width) camera->offset.x = width - (max.x - width/2);
    if (max.y < height) camera->offset.y = height - (max.y - height/2);
    if (min.x > 0) camera->offset.x = width/2 - min.x;
    if (min.y > 0) camera->offset.y = height/2 - min.y;
}
