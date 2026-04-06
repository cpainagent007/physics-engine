#pragma once
#include "raylib.h"
#include "raymath.h"

class Body
{
public:
	void AddForce(const Vector2 force);
	void Step(const float dt);
	void Draw() const;

	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	Color color;
	float mass;
	float size;
	float restitution;
};