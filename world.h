#pragma once
#include "body.h"
#include "raylib.h"
#include "raymath.h"
#include "random.h"
#include <vector>

class World
{
public:
	World() : gravity{ 0, 9.81f }, mouseActive(false), mouseRepel(true), mousePosition{ 0, 0 }
	{
		bodies.reserve(1000);
	}

	void Step(float dt);
	void Draw() const;
	void AddBody(Body& body);
	void ExplicitEuler(Body& body, float dt);
	void SemiImplicitEuler(Body& body, float dt);

	std::vector<Body> bodies;
	Vector2 gravity;
	bool mouseActive;
	bool mouseRepel;
	Vector2 mousePosition;
};