#include <raylib.h>
#include <iostream>
#include <string>
#include "raymath.h"

using namespace std;


void init() {
	//init
}

int main(void) {

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
	
	Rectangle player = { 400, 280, 40, 40 };

    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.x + 20.0f, player.y + 20.0f };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

	Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };

	while (!WindowShouldClose()) {


        // Player movement
        if (IsKeyDown(KEY_RIGHT)) player.x += 5;
        else if (IsKeyDown(KEY_LEFT)) player.x -= 5;

        // Camera target follows player
        camera.target = (Vector2){ player.x + 20, player.y + 20 };

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode2D(camera);

				DrawText("Congrats! You created your first window!", 190, 200, 20, WHITE);
				
				DrawRectangle(0, screenHeight*0.8, screenWidth, 100, BLUE);

                DrawRectangleRec(player, RED);

                DrawLine((int)camera.target.x, -screenHeight*10, (int)camera.target.x, screenHeight*10, GREEN);
                DrawLine(-screenWidth*10, (int)camera.target.y, screenWidth*10, (int)camera.target.y, GREEN);

            EndMode2D();

        EndDrawing();
        //--------------

	}

	CloseWindow();

	return 0;

}
