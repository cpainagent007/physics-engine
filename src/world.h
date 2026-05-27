#pragma once
#include "body.h"
#include "raylib.h"
#include "raymath.h"
#include "random.h"
#include "integrator.h"
#include "effector.h"
#include "pointEffector.h"
#include "gravitationEffector.h"
#include "areaEffector.h"
#include "dragEffector.h"
#include "spring.h"
#include "collision.h"
#include "worldCamera.h"

#include "raygui.h"
#include "gui_physics.h"

#include <vector>

class World
{
public:
	World() :
		mouseActive(false), mouseRepel(true), mousePosition{ 0, 0 }
	{
		//bodies.reserve(10000);
	}

	void Step(float dt);
	void Draw() const;
	void AddBody(Body& body, GuiPhysicsState state, WorldCamera& camera);
	void AddEffector(GuiPhysicsState state, WorldCamera& camera);
	void UpdateCollision();
	static void SetGravity(Vector2 newGravity) { gravity = newGravity; }
	Body* GetBodyIntersect(const Vector2& position);
	void SetBounds(Vector2 min, Vector2 max) { boundsMin = min; boundsMax = max; }

	std::vector<Body> bodies;
	std::vector<Effector*> effectors;
	std::vector<Contact> contacts;

	static Vector2 gravity;
	bool mouseActive;
	bool mouseRepel;
	Vector2 mousePosition;
	Vector2 boundsMin{ -10.0f, -5.0f };
	Vector2 boundsMax{ 10.0f, 5.0f };
};