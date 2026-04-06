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
	float mass = 1.0f;
	float size = 1.0f;
	float restitution = 1.0f;
	float gravityScale = 1.0f;
	float damping = 0.0f;
};