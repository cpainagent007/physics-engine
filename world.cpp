#include "world.h"

void World::Step(float dt)
{
	for (Body& body : bodies) body.acceleration = gravity * body.gravityScale * 100.0f;

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		mousePosition = GetMousePosition();
		mouseRepel = !IsKeyDown(KEY_SPACE);
		mouseActive = true;

		AddEffector(new PointEffector(mousePosition, 100.0f, 500.0f, mouseRepel));
	}
	else
	{
		mouseActive = false;
	}

	for (auto& effector : effectors)
	{
		effector->Apply(bodies);
	}

	for (Body& body : bodies)
	{
		Integrator::SemiImplicitEuler(body, dt);
		body.Step(dt);
	}
}

void World::Draw() const
{
	for (const Body& body : bodies)
	{
		body.Draw();
	}

	for (const auto& effector : effectors)
	{
		effector->Draw();
	}

	if (mouseActive)
	{
		DrawCircleLinesV(mousePosition, 100, WHITE);
	}
}

void World::AddBody(Body& body)
{
	body.position = GetMousePosition();
	float angle = Random::GetRandomFloat() * (2 * PI);
	Vector2 direction;
	direction.x = cosf(angle);
	direction.y = sinf(angle);
	body.velocity = direction * (50.0f + (Random::GetRandomFloat() * 100));
	body.acceleration = Vector2{ 0, 0 };
	body.size = 5.0f + (Random::GetRandomFloat() * 20.0f);
	body.restitution = 0.5f + (Random::GetRandomFloat() * 0.5f);
	body.mass = body.size * 0.1f;
	body.color = Random::GetRandomColor();
	body.gravityScale = 1.0f;
	body.damping = 0.5f;

	bodies.push_back(body);
}

void World::AddEffector(Effector* effector)
{
	effectors.push_back(effector);
}
