#pragma once
#include "raylib.h"
#include "raymath.h"

class Body
{
public:
	enum class BodyType
	{
		Static,
		Kinematic,
		Dynamic
	};

	enum class ForceMode
	{
		Force,
		Impulse,
		Acceleration,
		VelocityChange
	};

public:
	void AddForce(const Vector2 force, ForceMode forceMode = ForceMode::Force);
	void Step(const float dt);
	void Draw() const;

	BodyType bodyType = BodyType::Dynamic;
	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };
	Vector2 acceleration{ 0, 0 };
	Color color;
	float mass = 1.0f;
	float inverseMass = 1.0f;
	float size = 1.0f;
	float restitution = 1.0f;
	float gravityScale = 1.0f;
	float damping = 0.0f;
};