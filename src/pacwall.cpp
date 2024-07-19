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

	Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };

	while (!WindowShouldClose()) {


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            DrawText("move the ball with arrow keys", 10, 10, 20, DARKGRAY);

            DrawCircleV(ballPosition, 50, MAROON);

        EndDrawing();
        //--------------

	}

	CloseWindow();

	return 0;

}
