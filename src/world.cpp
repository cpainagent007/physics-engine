#include "world.h"

void World::Step(float dt)
{
	for (Body& body : bodies) body.acceleration = Vector2{ 0, 0 };
	for (Body& body : bodies) body.AddForce(gravity * body.gravityScale * 100.0f, Body::ForceMode::Acceleration);

	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		mousePosition = GetMousePosition();
		mouseRepel = !IsKeyDown(KEY_SPACE);

		if (IsKeyDown(KEY_P)) AddEffector(new PointEffector(mousePosition, 100.0f, 500.0f, mouseRepel));
		if (IsKeyDown(KEY_A)) AddEffector(new AreaEffector(mousePosition, 100.0f, 0.0f, 10000.0f));
		if (IsKeyDown(KEY_D)) AddEffector(new DragEffector(mousePosition, 100.0f, 20.0f));
		if (IsKeyDown(KEY_G)) AddEffector(new GravitationEffector(mousePosition, 100.0f, 10000.0f));
	}

	for (auto& effector : effectors) effector->Apply(bodies);

	for (Body& body : bodies) if (body.bodyType == Body::BodyType::Dynamic) Integrator::SemiImplicitEuler(body, dt);

	for (int i = 0; i < 4; i++) UpdateCollision();
}

void World::Draw() const
{
	for (const auto& effector : effectors) effector->Draw();

	for (const Body& body : bodies) body.Draw();
}

void World::AddBody(Body& body)
{
	body.bodyType = (IsKeyDown(KEY_LEFT_SHIFT)) ? Body::BodyType::Static : Body::BodyType::Dynamic;

	body.position = GetMousePosition();
	float angle = Random::GetRandomFloat() * (2 * PI);
	Vector2 direction;
	direction.x = cosf(angle);
	direction.y = sinf(angle);
	body.AddForce(direction * (50.0f + (Random::GetRandomFloat() * 100)), Body::ForceMode::VelocityChange);
	body.size = 5.0f + (Random::GetRandomFloat() * 20.0f);
	body.restitution = 0.5f + (Random::GetRandomFloat() * 0.5f);
	body.mass = body.size;
	body.inverseMass = (body.bodyType == Body::BodyType::Static) ? 0 : 1.0f / body.mass;
	body.color = Random::GetRandomColor();

	// GRAVITY SCALE
	body.gravityScale = 0.0f;
	body.damping = 0.5f;

	bodies.push_back(body);
}

void World::AddEffector(Effector* effector)
{
	effectors.push_back(effector);
}

void World::UpdateCollision()
{
	contacts.clear();
	CreateContacts(bodies, contacts);
	SeparateContacts(contacts);
	ResolveContacts(contacts);

	// collision
	for (auto& body : bodies)
	{
		if (body.position.x + body.size > GetScreenWidth())
		{
			body.position.x = GetScreenWidth() - body.size;
			body.velocity.x *= -body.restitution;
		}
		if (body.position.x - body.size < 0)
		{
			body.position.x = body.size;
			body.velocity.x *= -body.restitution;
		}
		if (body.position.y + body.size > GetScreenHeight())
		{
			body.position.y = GetScreenHeight() - body.size;
			body.velocity.y *= -body.restitution;
		}
		if (body.position.y - body.size < 0)
		{
			body.position.y = body.size;
			body.velocity.y *= -body.restitution;
		}
	}
}
