#include "raylib.h"
#include "resource_dir.h"
#include "raymath.h"

#include "body.h"
#include "world.h"
#include "gravitationEffector.h"
#include "worldCamera.h"

#include <vector>
#include <string>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define GUI_PHYSICS_IMPLEMENTATION
#pragma warning ( push )
#pragma warning ( disable : 4576)
#include "gui_physics.h"
#pragma warning ( pop )

GuiPhysicsState state;

int main ()
{
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(1300, 800, "Hello Raylib");

	state = InitGuiPhysics();
	GuiLoadStyle("raygui/styles/lavanda/style_lavanda.rgs");

	SearchAndSetResourceDir("resources");

	Texture wabbit = LoadTexture("wabbit_alpha.png");

	Body* selectedBody = nullptr;
	Body* connectedBody = nullptr;

	float targetFPS = state.FPSValue;

	SetTargetFPS(targetFPS);

	World world;
	WorldCamera worldCamera(Vector2{ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f }, 5);
	world.SetBounds(worldCamera.ScreenToWorld({ 0, (float)GetScreenHeight() }), worldCamera.ScreenToWorld({ (float)GetScreenWidth(), 0 }));

	float timeAccum = 0.0f;
	bool simulate = true;

	while (!WindowShouldClose())
	{
		float dt = fminf(GetFrameTime(), 0.1f);
		float fixedTimeStep = 1.0f / targetFPS;

		if (IsKeyPressed(KEY_S)) state.SimulateActive = !state.SimulateActive;
		if (IsKeyPressed(KEY_TAB)) state.PhysicsPanelActive = !state.PhysicsPanelActive;

		World::SetGravity(Vector2{ 0.0f, state.GravityValue });

		Rectangle guiRect = Rectangle{ state.anchor02.x, state.anchor02.y, 304, 664 };
		bool mouseOverGUI = state.PhysicsPanelActive && CheckCollisionPointRec(GetMousePosition(), guiRect);

		if (!mouseOverGUI) {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsKeyDown(KEY_SPACE) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)))
			{
				Body body;
				world.AddBody(body, state, worldCamera);
			}
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				world.AddEffector(state, worldCamera);
			}
			if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE))
			{
				selectedBody = world.GetBodyIntersect(worldCamera.ScreenToWorld(GetMousePosition()));
			}
			if (selectedBody && IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
			{
				Vector2 position = worldCamera.ScreenToWorld(GetMousePosition());
				Vector2 force = Spring::GetSpringForce(position, selectedBody->position, 1.0f, 3.0f);
				selectedBody->AddForce(force);

				DrawLineV(position, selectedBody->position, RED);
			}
		}
		

		// Update
		if (state.SimulateActive) {
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
		worldCamera.Begin(); // set world camera
		world.Draw(); // draw using world camera transform
		worldCamera.End(); // remove world camera

		// Draw FPS
		std::string fpsText = "FPS:";
		fpsText += std::to_string(GetFPS());
		DrawText(fpsText.c_str(), GetScreenWidth() - 120, 20, 20, WHITE);

		if (selectedBody)
		{
			DrawCircleLinesV(worldCamera.ScreenToWorld(selectedBody->position), selectedBody->size * 1.1f, RED);
		}

		/*

		// Draw Is Simulating
		std::string simText = "Simulating:";
		std::string tfText = (simulate) ? "True" : "False";
		simText += tfText;
		DrawText(simText.c_str(), 20, 40, 20, WHITE);

		//Draw Instructions
		std::string spawnText = "Left Click = Spawn Body";
		DrawText(spawnText.c_str(), 20, 420, 20, WHITE);

		std::string spawnStationaryText = "Left Click + Shift = Spawn Stationary Body";
		DrawText(spawnStationaryText.c_str(), 20, 440, 20, WHITE);

		std::string spawnManyText = "Left Click + Space = Spawn Multiple Bodies";
		DrawText(spawnManyText.c_str(), 20, 460, 20, WHITE);

		std::string simulateText = "S = Toggle Simulating";
		DrawText(simulateText.c_str(), 20, 480, 20, WHITE);

		std::string pointEffectorRepelText = "Right Click + P = Point Effector Repel";
		DrawText(pointEffectorRepelText.c_str(), 20, 500, 20, PINK);

		std::string pointEffectorAttractText = "Right Click + P + Space = Point Effector Attract";
		DrawText(pointEffectorAttractText.c_str(), 20, 520, 20, LIME);

		std::string gravitationEffectorText = "Right Click + G = Gravitation Effector";
		DrawText(gravitationEffectorText.c_str(), 20, 540, 20, YELLOW);

		std::string areaEffectorText = "Right Click + A = Area Effector";
		DrawText(areaEffectorText.c_str(), 20, 560, 20, BLUE);

		std::string dragEffectorText = "Right Click + D = Drag Effector";
		DrawText(dragEffectorText.c_str(), 20, 580, 20, PURPLE);

		*/

		GuiPhysics(&state);

		// End Draw
		EndDrawing();
	}

	UnloadTexture(wabbit);

	CloseWindow();
	return 0;
}
