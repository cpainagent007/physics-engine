#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"

#include "../body.h"
#include "../world.h"

#include <vector>
#include <string>



int main ()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(800, 600, "Hello Raylib");

	SearchAndSetResourceDir("resources");

	Texture wabbit = LoadTexture("wabbit_alpha.png");

	float targetFPS = 60.0f;

	SetTargetFPS(targetFPS);

	World world;

	float timeAccum = 0.0f;
	float fixedTimeStep = 1.0f / targetFPS;

	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsKeyDown(KEY_SPACE) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)))
		{
			Body body;
			world.AddBody(body);
		}

		// Update
		timeAccum += dt;
		while (timeAccum > fixedTimeStep)
		{
			world.Step(fixedTimeStep);
			timeAccum -= fixedTimeStep;
		}

		// Begin Draw
		BeginDrawing();

		// Clear Background
		ClearBackground(BLACK);

		// Draw World
		world.Draw();

		// Draw FPS
		std::string fpsText = "FPS:";
		fpsText += std::to_string(GetFPS());
		DrawText(fpsText.c_str(), 100, 100, 20, WHITE);

		// End Draw
		EndDrawing();
	}

	UnloadTexture(wabbit);

	CloseWindow();
	return 0;
}
