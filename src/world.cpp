#include "world.h"

Vector2 World::gravity = { 0, 9.81f };

void World::Step(float dt)
{
	for (Body& body : bodies) body.acceleration = Vector2{ 0, 0 };
	for (Body& body : bodies) body.AddForce(gravity * body.gravityScale * 100.0f, Body::ForceMode::Acceleration);

	for (auto& effector : effectors) effector->Apply(bodies);

	for (Body& body : bodies) if (body.bodyType == Body::BodyType::Dynamic) Integrator::SemiImplicitEuler(body, dt);

	for (int i = 0; i < 4; i++) UpdateCollision();
}

void World::Draw() const
{
	for (const auto& effector : effectors) effector->Draw();

	for (const Body& body : bodies) body.Draw();
}

void World::AddBody(Body& body, GuiPhysicsState state)
{
	body.bodyType = (Body::BodyType)state.BodyTypeActive;

	body.position = GetMousePosition();
	float angle = Random::GetRandomFloat() * (2 * PI);
	Vector2 direction;
	direction.x = cosf(angle);
	direction.y = sinf(angle);
	body.AddForce(direction * (50.0f + (Random::GetRandomFloat() * 100)), Body::ForceMode::VelocityChange);
	body.size = state.BodySizeValue;
	body.restitution = state.BodyRestitutionValue;
	body.mass = body.size * state.BodyMassValue;
	body.inverseMass = (body.bodyType == Body::BodyType::Static) ? 0 : 1.0f / body.mass;
	body.color = Random::GetRandomColor();

	// GRAVITY SCALE
	body.gravityScale = state.BodyGravityValue;
	body.damping = state.BodyDampingValue;

	bodies.push_back(body);
}

void World::AddEffector(GuiPhysicsState state)
{
	Vector2 position = GetMousePosition();
	mouseRepel = !IsKeyDown(KEY_SPACE);

	Effector* effector = nullptr;
	switch ((EffectorType)state.EffectorTypeActive)
	{
	case EffectorType::Point:
		effector = new PointEffector(position, 100.0f, 500.0f, mouseRepel);
		break;
	case EffectorType::Area:
		effector = new AreaEffector(position, 100.0f, 0.0f, 10000.0f);
		break;
	case EffectorType::Drag:
		effector = new DragEffector(position, 100.0f, 20.0f);
		break;
	case EffectorType::Gravitation:
		effector = new GravitationEffector(position, 100.0f, 10000.0f);
		break;
	}

	if (effector) effectors.push_back(effector);
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
