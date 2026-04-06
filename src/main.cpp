#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"

#include "../body.h"
#include "../world.h"

#include <vector>

World world;

int main ()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(800, 600, "Hello Raylib");

	SearchAndSetResourceDir("resources");

	Texture wabbit = LoadTexture("wabbit_alpha.png");

	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsKeyDown(KEY_SPACE) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)))
		{
			Body body;
			world.AddBody(body);
		}

		// Update
		world.Step(dt);

		// Draw
		BeginDrawing();

		world.Draw();

		// End Draw
		ClearBackground(BLACK);

		EndDrawing();
	}

	UnloadTexture(wabbit);

	CloseWindow();
	return 0;
}
