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
			if (selectedBody)
			{
				if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
				{
					if (IsKeyDown(KEY_LEFT_CONTROL))
					{
						Vector2 position = worldCamera.ScreenToWorld(GetMousePosition());
						Vector2 force = Spring::GetSpringForce(position, selectedBody->position, 1.0f, 3.0f);
						selectedBody->AddForce(force);

						DrawLineV(worldCamera.WorldToScreen(position), worldCamera.WorldToScreen(selectedBody->position), RED);
					}
					else
					{
						connectedBody = world.GetBodyIntersect(worldCamera.ScreenToWorld(GetMousePosition()));
					}
				}
				else
				{
					if (selectedBody && connectedBody)
					{
						float distance = Vector2Distance(selectedBody->position, connectedBody->position);
						world.AddSpring(*selectedBody, *connectedBody, distance, state.SpringStiffnessValue, state.SpringDampingValue);
					}

					selectedBody = nullptr;
					connectedBody = nullptr;
				}
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

		if (selectedBody) DrawCircleLinesV(selectedBody->position, selectedBody->size * 1.1f, RED);
		if (connectedBody) DrawCircleLinesV(connectedBody->position, connectedBody->size * 1.1f, RED);
		DrawCircleLinesV(worldCamera.ScreenToWorld(GetMousePosition()), state.EffectorSizeValue * 0.5f, RED);

		worldCamera.End(); // remove world camera

		// Draw FPS
		std::string fpsText = "FPS:";
		fpsText += std::to_string(GetFPS());
		DrawText(fpsText.c_str(), GetScreenWidth() - 120, 20, 20, WHITE);

		

		GuiPhysics(&state);

		// End Draw
		EndDrawing();
	}

	UnloadTexture(wabbit);

	CloseWindow();
	return 0;
}
