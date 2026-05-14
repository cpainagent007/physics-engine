#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"

#include "body.h"
#include "world.h"
#include "gravitationEffector.h"

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
	bool simulate = true;

	// GRAVITY EFFECTOR
	world.AddEffector(new GravitationEffector(Vector2{ 400, 300 }, 150.0f, 10000.0f));

	while (!WindowShouldClose())
	{
		float dt = fminf(GetFrameTime(), 0.1f);

		if (IsKeyPressed(KEY_S))
		{
			simulate = !simulate;
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsKeyDown(KEY_SPACE) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)))
		{
			Body body;
			world.AddBody(body);
		}

		// Update
		if (simulate) {
			timeAccum += dt;
			while (timeAccum > fixedTimeStep)
			{
				world.Step(fixedTimeStep);
				timeAccum -= fixedTimeStep;
			}
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

		// Draw Is Simulating
		std::string simText = "Simulating:";
		std::string tfText = (simulate) ? "True" : "False";
		simText += tfText;
		DrawText(simText.c_str(), 100, 120, 20, WHITE);

		// End Draw
		EndDrawing();
	}

	UnloadTexture(wabbit);

	CloseWindow();
	return 0;
}
