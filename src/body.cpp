#include "body.h"

void Body::AddForce(const Vector2 force, ForceMode forceMode)
{
	if (bodyType != BodyType::Dynamic) return;

	switch (forceMode)
	{
	case Body::ForceMode::Force:
		acceleration += force * inverseMass;
		break;
	case Body::ForceMode::Impulse:
		velocity += force * inverseMass;
		break;
	case Body::ForceMode::Acceleration:
		acceleration += force;
		break;
	case Body::ForceMode::VelocityChange:
		velocity += force;
		break;
	default:
		break;
	}
}

void Body::Step(const float dt)
{
	// Moved to world.cpp
	/*if (position.x + size > GetScreenWidth())
	{
		position.x = GetScreenWidth() - size;
		velocity.x *= -restitution;
	}
	if (position.x - size < 0)
	{
		position.x = size;
		velocity.x *= -restitution;
	}
	if (position.y + size > GetScreenHeight())
	{
		position.y = GetScreenHeight() - size;
		velocity.y *= -restitution;
	}
	if (position.y - size < 0)
	{
		position.y = size;
		velocity.y *= -restitution;
	}*/
}

void Body::Draw() const
{
	DrawCircleV(position, size, color);
	DrawCircleLinesV(position, size, WHITE);
}