#include "world.h"

void World::Step(float dt)
{
	for (Body& body : bodies) body.acceleration = Vector2{ 0, 0 };
	for (Body& body : bodies) body.AddForce(gravity * body.mass * 100.0f);

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		mousePosition = GetMousePosition();
		mouseRepel = !IsKeyDown(KEY_SPACE);
		mouseActive = true;

		for (Body& body : bodies)
		{
			Vector2 direction;
			if (mouseRepel) direction = body.position - mousePosition;
			else direction = mousePosition - body.position;

			if (Vector2Length(direction) <= 100.0f)
			{
				Vector2 force = Vector2Normalize(direction) * 50000.0f;
				body.AddForce(force);
			}
		}
	}
	else
	{
		mouseActive = false;
	}

	for (Body& body : bodies)
	{
		SemiImplicitEuler(body, dt);
		body.Step(dt);
	}
}

void World::Draw() const
{
	for (const Body& body : bodies)
	{
		body.Draw();
	}

	if (mouseActive)
	{
		DrawCircleLinesV(mousePosition, 100, WHITE);
	}
}

void World::AddBody(Body& body)
{
	body.position = GetMousePosition();
	float angle = Random::GetRandomFloat() * PI;
	Vector2 direction;
	direction.x = cosf(angle);
	direction.y = sinf(angle);
	body.velocity = direction * (50.0f + (Random::GetRandomFloat() * 100));
	body.acceleration = Vector2{ 0, 0 };
	body.size = 5.0f + (Random::GetRandomFloat() * 20.0f);
	body.restitution = 0.5f + (Random::GetRandomFloat() * 0.5f);
	body.mass = body.size * 0.1f;
	body.color = Random::GetRandomColor();
	bodies.push_back(body);
}

void World::ExplicitEuler(Body& body, float dt)
{
	body.position += body.velocity * dt;
	body.velocity += body.acceleration * dt;
}

void World::SemiImplicitEuler(Body& body, float dt)
{
	body.velocity += body.acceleration * dt;
	body.position += body.velocity * dt;
}