#include "body.h"

void Body::AddForce(const Vector2 force)
{
	acceleration += force / mass;
}

void Body::Step(const float dt)
{
	if (position.x + size > GetScreenWidth())
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
	}
}

void Body::Draw() const
{
	DrawCircleV(position, size, color);
}