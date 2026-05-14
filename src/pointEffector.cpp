#include "pointEffector.h"

void PointEffector::Apply(std::vector<Body>& inBodies)
{
	std::vector<Body*> outBodies;
	CollectBodiesInside(inBodies, outBodies);

	for (auto& body : outBodies)
	{
		Vector2 direction;
		if (repel) direction = body->position - position;
		else direction = position - body->position;

		Vector2 force = Vector2Normalize(direction) * forceMagnitude;
		body->AddForce(force);
	}
}

void PointEffector::Draw()
{
	Effector::Draw();
	if (repel) DrawCircleV(position, size, Fade(PINK, 0.2f));
	else DrawCircleV(position, size, Fade(LIME, 0.2f));
}
