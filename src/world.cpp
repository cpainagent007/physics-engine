#include "world.h"

Vector2 World::gravity = { 0, -9.81f };

void World::Step(float dt)
{
	for (Body& body : bodies) body.AddForce(gravity * body.gravityScale, Body::ForceMode::Acceleration);

	for (auto& effector : effectors) effector->Apply(bodies);

	for (auto& spring : springs) spring->Apply(1.0f);

	for (Body& body : bodies) if (body.bodyType == Body::BodyType::Dynamic) Integrator::SemiImplicitEuler(body, dt);

	for (int i = 0; i < 4; i++) UpdateCollision();

	for (Body& body : bodies) body.acceleration = Vector2{ 0, 0 };
}

void World::Draw() const
{
	for (const auto& effector : effectors) effector->Draw();

	for (auto& spring : springs) spring->Draw();

	for (const auto& body : bodies) body.Draw();
}

void World::AddBody(Body& body, GuiPhysicsState state, WorldCamera& camera)
{
	body.bodyType = (Body::BodyType)state.BodyTypeActive;

	body.position = camera.ScreenToWorld(GetMousePosition());
	float angle = Random::GetRandomFloat() * (2 * PI);
	Vector2 direction;
	direction.x = cosf(angle);
	direction.y = sinf(angle);
	body.AddForce(direction * (Random::GetRandomFloat()), Body::ForceMode::VelocityChange);
	body.size = state.BodySizeValue * 0.5f;
	body.restitution = state.BodyRestitutionValue;
	body.mass = body.size * state.BodyMassValue;
	body.inverseMass = (body.bodyType == Body::BodyType::Static) ? 0 : 1.0f / body.mass;
	body.color = Random::GetRandomColor();

	// GRAVITY SCALE
	body.gravityScale = state.BodyGravityValue;
	body.damping = state.BodyDampingValue;

	bodies.push_back(body);
}

void World::AddEffector(GuiPhysicsState state, WorldCamera& camera)
{
	Vector2 position = camera.ScreenToWorld(GetMousePosition());
	mouseRepel = !IsKeyDown(KEY_SPACE);

	Effector* effector = nullptr;
	switch ((EffectorType)state.EffectorTypeActive)
	{
	case EffectorType::Point:
		effector = new PointEffector(position, state.EffectorSizeValue * 0.5f, state.EffectorForceValue, mouseRepel);
		break;
	case EffectorType::Area:
		effector = new AreaEffector(position, state.EffectorSizeValue * 0.5f, state.EffectorAngleValue, state.EffectorForceValue);
		break;
	case EffectorType::Drag:
		effector = new DragEffector(position, state.EffectorSizeValue * 0.5f, state.EffectorForceValue);
		break;
	case EffectorType::Gravitation:
		effector = new GravitationEffector(position, state.EffectorSizeValue * 0.5f, state.EffectorForceValue);
		break;
	}

	if (effector) effectors.push_back(effector);
}

void World::AddSpring(Body& bodyA, Body& bodyB, float restLength, float stiffness, float damping)
{
	Spring* spring = new Spring(&bodyA, &bodyB, restLength, stiffness, damping);
	springs.push_back(spring);
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
		if (body.position.x + body.size > boundsMax.x)
		{
			body.position.x = boundsMax.x - body.size;
			body.velocity.x *= -body.restitution;
		}
		if (body.position.x - body.size < boundsMin.x)
		{
			body.position.x = boundsMin.x + body.size;
			body.velocity.x *= -body.restitution;
		}
		if (body.position.y + body.size > boundsMax.y)
		{
			body.position.y = boundsMax.y - body.size;
			body.velocity.y *= -body.restitution;
		}
		if (body.position.y - body.size < boundsMin.y)
		{
			body.position.y = boundsMin.y + body.size;
			body.velocity.y *= -body.restitution;
		}
	}
}

Body* World::GetBodyIntersect(const Vector2& position)
{
	for (auto& body : bodies)
	{
		if (CheckCollisionPointCircle(position, body.position, body.size))
		{
			return &body;
		}
	}

	return nullptr;
}
